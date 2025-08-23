#include <memory>
#include <format>

#include "constants/Constants.h"
#include "components/SettingsManager.h"
#include "utils/InputUtils.h"
#include "utils/GameUtils.h"
#include "utils/DataUtils.h"
#include "GameState.h"
#include "MenuState.h"
#include "GameOverState.h"

GameOverState::GameOverState(GameData &data, StateManager &manager, sf::RenderWindow &win,
                             GameOverStateConfig config)
    : gameData(data), stateManager(manager), window(win),
      stateConfig(config),
      isAskingForPlayerName(false),
      playerHasHighScore(false),
      playerName(""),
      playerScore(0)
{
    buttonSpacing = 20.f;
    sf::Vector2f viewSize = gameOverView.getSize();
    sf::Vector2f center(gameOverView.getCenter());
    window.setView(gameOverView);

    // Configure background
    background.setSize(sf::Vector2f(viewSize.x - 20.0f, viewSize.y - 20.0f));
    background.setFillColor(sf::Color(0, 0, 0, 150));

    // Configure text
    gameOverText.setFont(gameData.gameFont);
    gameOverText.setString(stateConfig.titleText);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(stateConfig.titleTextColour);

    finalScoreText.setFont(gameData.gameFont);
    finalScoreText.setString(GameUtils::formatScoreText(calculateFinalScore()));
    finalScoreText.setCharacterSize(48);
    finalScoreText.setFillColor(sf::Color::Yellow);

    // Add buttons
    float buttonRowY = center.y + viewSize.y / 2.f - Constants::BUTTON_HEIGHT - buttonSpacing;

    buttons.emplace_back("New", gameData.gameFont, "New Game", sf::Vector2f(center.x - viewSize.x / 2.f + buttonSpacing, buttonRowY),
                         [this]()
                         {
                             gameData.reset();
                             stateManager.replaceStates(std::make_unique<GameState>(gameData, stateManager, window));
                         });
    buttons.emplace_back("Menu", gameData.gameFont, "Main Menu", sf::Vector2f(center.x - viewSize.x / 2.f + (buttonSpacing * 2.0f) + Constants::BUTTON_WIDTH, buttonRowY),
                         [this]()
                         {
                             gameData.reset();
                             stateManager.replaceStates(std::make_unique<MenuState>(gameData, stateManager, window));
                         });
    buttons.emplace_back("Exit", gameData.gameFont, "Exit", sf::Vector2f(center.x + viewSize.x / 2.f - Constants::BUTTON_WIDTH - buttonSpacing, buttonRowY),
                         [this]()
                         { window.close(); });

    // Handle high scoring!
    highScoreManager.loadFromFile("highscores.txt");
    isAskingForPlayerName = playerHasHighScore = checkIfHighScore();

    // To ensure positioning is updated relative to window resizing
    updateMenuItemPositions();
}

GameOverState::~GameOverState()
{
    // Destructor
}

// Publics

void GameOverState::handleEvent(const sf::Event &event)
{
    if (isAskingForPlayerName)
    {
        if (event.type == sf::Event::TextEntered &&
            (event.text.unicode != '\r' &&
             event.text.unicode != '\n'))
        {
            if (event.text.unicode == '\b' &&
                !playerName.empty())
            {
                playerName.pop_back();
            }
            else if (event.text.unicode < 128 &&
                     playerName.size() < 15)
            {
                char inputChar = static_cast<char>(event.text.unicode);

                if (DataUtils::isValidInputChar(inputChar))
                {
                    playerName += inputChar;
                }
            }
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Enter)
        {
            playerName = DataUtils::trim(playerName);

            if (!playerName.empty())
            {
                playerScore = calculateFinalScore();
                highScoreManager.addScore(playerName, playerScore);
                highScoreManager.saveToFile("highscores.txt");
                isAskingForPlayerName = false;
            }
            else
            {
                playerName = "";
            }
        }
    }
    else
    {
        InputUtils::handleButtonEvent(event, buttons, window, selectedButtonIndex);
    }

    if (event.type == sf::Event::Resized)
    {
        updateMenuItemPositions();
    }
}

void GameOverState::update(sf::Time deltaTime)
{
    (void)deltaTime;

    gameData.audioManager.cleanupSounds();

    if (gameData.audioManager.getSoundStatus(AudioId::AMBIENT) == sf::Sound::Status::Playing)
    {
        gameData.audioManager.stopSound(AudioId::AMBIENT);
    }
}

void GameOverState::render()
{
    window.setView(gameOverView);
    window.draw(background);
    window.draw(gameOverText);
    window.draw(finalScoreText);

    if (isAskingForPlayerName)
    {
        sf::Vector2f viewCenter = gameOverView.getCenter();

        sf::Text prompt("Enter your name: ", gameData.gameFont, 48);
        prompt.setPosition(viewCenter.x - (prompt.getGlobalBounds().width / 2.0f),
                           viewCenter.y - prompt.getGlobalBounds().height);
        prompt.setFillColor(sf::Color::Yellow);

        sf::Text input(playerName, gameData.gameFont, 48);
        input.setPosition(viewCenter.x - (prompt.getGlobalBounds().width / 2.0f),
                          viewCenter.y);
        input.setFillColor(sf::Color::White);

        window.draw(prompt);
        window.draw(input);
    }
    else
    {
        displayHighScores(highScoreManager.getHighScores(), window);

        for (const auto &button : buttons)
        {
            button.render(window);
        }
    }
}

// Privates

void GameOverState::updateMenuItemPositions()
{
    sf::Vector2f viewCenter = gameOverView.getCenter();
    sf::Vector2f viewSize = gameOverView.getSize();
    sf::Vector2f backgroundSize = background.getSize();

    background.setPosition(
        viewCenter.x - backgroundSize.x / 2.f,
        viewCenter.y - backgroundSize.y / 2.f);

    float topEdge = viewCenter.y - viewSize.y / 2.0f;

    gameOverText.setPosition(
        viewCenter.x - (gameOverText.getGlobalBounds().width / 2.0f),
        topEdge + buttonSpacing);

    finalScoreText.setPosition(
        viewCenter.x - (finalScoreText.getGlobalBounds().width / 2.0f),
        topEdge + gameOverText.getGlobalBounds().height + (buttonSpacing * 2.0f));

    float buttonRowY = viewCenter.y + viewSize.y / 2.f - Constants::BUTTON_HEIGHT - buttonSpacing;
    buttons[0].setPosition(sf::Vector2f(viewCenter.x - viewSize.x / 2.f + buttonSpacing, buttonRowY));
    buttons[1].setPosition(sf::Vector2f(viewCenter.x - viewSize.x / 2.f + (buttonSpacing * 2.0f) + Constants::BUTTON_WIDTH, buttonRowY));
    buttons[2].setPosition(sf::Vector2f(viewCenter.x + viewSize.x / 2.f - Constants::BUTTON_WIDTH - buttonSpacing, buttonRowY));
}

void GameOverState::displayHighScores(const std::vector<HighScore> &scores, sf::RenderWindow &renderWindow)
{
    (void)renderWindow;
    sf::Vector2f viewCenter = gameOverView.getCenter();
    sf::Vector2f viewSize = gameOverView.getSize();

    for (int i = 0; i < static_cast<int>(scores.size()); ++i)
    {
        const HighScore &entry = scores[i];

        // TODO Optionally put the timestamp on the score board
        // std::tm timeinfo = {};
        // localtime_s(&timeinfo, &entry.timestamp);
        // std::ostringstream timeStream;
        // timeStream << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
        // std::string formattedTime = timeStream.str();

        // Combine name, score, and timestamp into a display string
        std::string entryName = entry.name;
        std::string entryScore = GameUtils::formatScoreText(entry.score);
        int nameLength = static_cast<int>(entryName.length());
        int scoreLength = static_cast<int>(entryScore.length());
        // int timeLength = static_cast<int>(formattedTime.length());

        std::string separator(25 - nameLength - scoreLength, '.');
        std::string displayString = entryName + separator + entryScore;

        bool isCurrentUserScore = playerHasHighScore &&
                                  entry.name == playerName &&
                                  entry.score == playerScore;

        std::string prepend = isCurrentUserScore ? "> " : "  ";
        displayString = prepend + displayString;

        sf::Text text(displayString, gameData.gameFont, 36);
        text.setPosition(viewCenter.x - text.getGlobalBounds().width / 2.0f,
                         viewCenter.y - viewSize.y / 2.0f + gameOverText.getGlobalBounds().height + waveText.getGlobalBounds().height + finalScoreText.getGlobalBounds().height + (buttonSpacing * 5.0f) + i * 50.0f);
        text.setFillColor(isCurrentUserScore ? sf::Color::White : sf::Color::Yellow);
        window.draw(text);
    }
}

bool GameOverState::checkIfHighScore()
{
    auto &highscores = highScoreManager.getHighScores();
    if (highscores.size() < highScoreManager.maxHighScores)
    {
        return true;
    }

    int finalScore = calculateFinalScore();
    bool isOnLeaderBoard = false;

    for (const auto &score : highscores)
    {
        if (finalScore > score.score)
        {
            isOnLeaderBoard = true;
            break;
        }
    }

    return isOnLeaderBoard;
}

int GameOverState::calculateFinalScore()
{
    Difficulty difficulty = SettingsManager::getInstance().getDifficulty();
    int difficultyIndex = static_cast<int>(difficulty);

    int displayedScore = gameData.getPlayerScore();
    int playerGold = gameData.getPlayerGold();
    int playerLives = gameData.getPlayerLives();

    // Calculate for lives based on difficulty
    float startingLives = 9.0f * static_cast<float>(std::pow(2.0 / 3.0, difficultyIndex));
    float livesWeight = 100.0f * (9.0f / startingLives); // Easy=100, Normal=150, Hard=225
    float livesScore = (static_cast<float>(playerLives) / startingLives) * livesWeight;

    // Difficulty bump: Easy=1.0, Normal≈1.25, Hard≈1.56
    float difficultyBonus = static_cast<float>(std::pow(1.25f, difficultyIndex));

    float rawScore = static_cast<float>(displayedScore + playerGold) + livesScore;
    return static_cast<int>(rawScore * difficultyBonus);
}
