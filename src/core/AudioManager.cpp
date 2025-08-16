#include "AudioManager.h"

AudioManager::AudioManager()
{
    initializeVolumeDefaults();
}

AudioManager::~AudioManager()
{
    // Destructor
}

// Publics

void AudioManager::loadSound(AudioId uniqueId, const std::string &filename)
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename))
    {
        throw std::runtime_error("Failed to load sound: " + filename);
    }

    soundBuffers[uniqueId] = buffer;

    sf::Sound sound;
    sound.setBuffer(soundBuffers[uniqueId]);
    sound.setVolume(volumeMap[uniqueId]);

    sounds[uniqueId] = sound;
}

sf::Sound &AudioManager::getSound(AudioId uniqueId)
{
    return sounds.at(uniqueId);
}

sf::Sound::Status AudioManager::getSoundStatus(AudioId uniqueId) const
{
    const sf::Sound &sound = sounds.at(uniqueId);
    return sound.getStatus();
}

void AudioManager::playSound(AudioId uniqueId, bool loop)
{
    if (sounds.find(uniqueId) != sounds.end())
    {
        sounds[uniqueId].play();
        sounds[uniqueId].setLoop(loop);
    }
}

void AudioManager::playPooledSound(AudioId uniqueId)
{
    if (soundPool.empty())
    {
        initialiseSoundPool();
    }

    for (auto &sound : soundPool)
    {
        if (sound->getStatus() == sf::Sound::Status::Stopped)
        {
            sound->setBuffer(soundBuffers.at(uniqueId));
            sound->play();
            return;
        }
    }

    // No available sounds—add a new one to the pool
    auto newSound = std::make_unique<sf::Sound>();
    newSound->setBuffer(soundBuffers.at(uniqueId));
    newSound->play();
    soundPool.emplace_back(std::move(newSound));
}

void AudioManager::stopSound(AudioId uniqueId)
{
    if (sounds.find(uniqueId) != sounds.end())
    {
        sounds[uniqueId].stop();
    }
}

void AudioManager::cleanupSounds()
{
    if (soundPool.size() > minimumPoolSize)
    {
        soundPool.erase(
            std::remove_if(soundPool.begin(), soundPool.end(),
                           [](const std::unique_ptr<sf::Sound> &sound)
                           {
                               return !sound ||
                                      sound->getStatus() == sf::Sound::Status::Stopped;
                           }),
            soundPool.end());
    }

    while (soundPool.size() < minimumPoolSize)
    {
        soundPool.emplace_back(std::make_unique<sf::Sound>());
    }
}

// Privates

void AudioManager::initializeVolumeDefaults()
{
    volumeMap[AudioId::AMBIENT] = 50.0f;

    volumeMap[AudioId::ARROW_FIRED] = 75.0f;
    volumeMap[AudioId::ARROW_HIT] = 75.0f;
    volumeMap[AudioId::MAGIC_FIRED] = 75.0f;
    volumeMap[AudioId::MAGIC_HIT] = 75.0f;
    volumeMap[AudioId::MELEE_BASH] = 75.0f;

    volumeMap[AudioId::ENEMY_DEATH] = 80.0f;
    volumeMap[AudioId::SOLDIER_DEATH] = 80.0f;
    volumeMap[AudioId::PLAYER_DAMAGED] = 80.0f;

    volumeMap[AudioId::VICTORY] = 100.0f;
}

void AudioManager::initialiseSoundPool()
{
    soundPool.resize(minimumPoolSize);
    for (auto &sound : soundPool)
    {
        sound = std::make_unique<sf::Sound>();
    }
}