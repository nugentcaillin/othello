#ifndef OTHELLO_BACKEND_SDL_ERROR_H
#define OTHELLO_BACKEND_SDL_ERROR_H

#include <stdexcept>
#include <string>
#include <SDL3/SDL.h>

// exit prematurely if sdl call returns value that casts to flase (0)
void check_sdl_error(bool success, std::string sdl_func) {
    if (!success)
    {
        throw std::runtime_error("Error in " + sdl_func + "(): " + std::string(SDL_GetError()));
    }
}


#endif 