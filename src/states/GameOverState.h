#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics.hpp>

#include "ui/Button.h"
#include "core/GameData.h"
#include "core/State.h"
#include "core/StateManager.h"
#include "core/HighScoreManager.h"
#include "data/HighScore.h"
#include "data/GameOverStateConfig.h"

class GameOverState : public State
{
private:
    GameData &gameData;
    StateManager &stateManager;
    sf::RenderWindow &window;
    sf::View gameOverView;

    GameOverStateConfig stateConfig;

    HighScoreManager highScoreManager;

    sf::RectangleShape background;
    sf::Text gameOverText;
    sf::Text waveText;
    sf::Text finalScoreText;
    float buttonSpacing;
    std::vector<Button> buttons;
    int selectedButtonIndex = 0;

    bool isAskingForPlayerName;
    bool playerHasHighScore;
    std::string playerName;
    int playerScore;

private:
    void updateMenuItemPositions();

    void displayHighScores(const std::vector<HighScore> &scores, sf::RenderWindow &window);
    bool checkIfHighScore();
    int calculateFinalScore();

public:
    GameOverState(GameData &data, StateManager &manager, sf::RenderWindow &window,
                  GameOverStateConfig config = GameOverStateConfig::defaultValues());
    ~GameOverState();

    void handleEvent(const sf::Event &event) override;
    void update(sf::Time deltaTime) override;
    void render() override;
};

#endif // GAMEOVERSTATE_H
