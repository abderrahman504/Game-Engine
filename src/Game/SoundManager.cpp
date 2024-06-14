#include "SoundManager.h"



Mix_Music* SoundManager::music = nullptr;
bool SoundManager::initialized = false;
int SoundManager::playDuration = -1;  // Default to play indefinitely
int SoundManager::volume = MIX_MAX_VOLUME / 2;  // Default volume to half
std::mutex SoundManager::mtx;

bool SoundManager::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    initialized = true;
    return true;
}

void SoundManager::loadAndPlay(const char* filename) {
    if (!initialized) {
        std::cerr << "SoundManager is not initialized!" << std::endl;
        return;
    }

    std::thread soundThread(playSoundThread, filename);
    soundThread.detach();  // Detach the thread to let it run independently
}

void SoundManager::playSoundThread(const char* filename) {
    std::lock_guard<std::mutex> lock(mtx);

    music = Mix_LoadMUS(filename);
    if (music == nullptr) {
        std::cerr << "Failed to load music file! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_PlayMusic(music, 0);  // Play music once

    // If playDuration is set and positive, wait for the duration and then stop
    if (playDuration > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(playDuration));
    } else {
        // If playDuration is not set or negative, wait until the music finishes
        while (Mix_PlayingMusic() != 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    Mix_FreeMusic(music);
    music = nullptr;
}

void SoundManager::setVolume(int newVolume) {
    if (newVolume < 0) newVolume = 0;
    if (newVolume > MIX_MAX_VOLUME) newVolume = MIX_MAX_VOLUME;
    volume = newVolume;
    Mix_VolumeMusic(volume);
}

void SoundManager::setPlayDuration(int duration) {
    playDuration = duration;
}

void SoundManager::cleanup() {
    if (initialized) {
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        initialized = false;
    }
}


