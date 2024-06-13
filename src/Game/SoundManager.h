//
// Created by AhmedSamir on 12/06/2024.
//

#ifndef GAME_ENGINE_SOUNDMANAGER_H
#define GAME_ENGINE_SOUNDMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <csignal>
#include <thread>
#include <mutex>
#include <condition_variable>

class SoundManager {
public:
    static bool initialize();
    static void loadAndPlay(const char* filename);
    static void cleanup();
    static void setVolume(int volume);
    static void setPlayDuration(int duration);

private:
    static Mix_Music* music;
    static bool initialized;
    static int playDuration;
    static int volume;
    static std::mutex mtx;

    static void playSound(const char* filename);
    static void playSoundThread(const char* filename);
};



#endif //GAME_ENGINE_SOUNDMANAGER_H