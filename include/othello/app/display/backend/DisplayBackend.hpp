#ifndef OTHELLO_DISPLAY_BACKEND_H
#define OTHELLO_DISPLAY_BACKEND_H

#include <concepts>
#include <stdexcept>
#include <SDL3/SDL.h>
#include <othello_config.hpp>
#include <othello/app/display/backend/SdlError.hpp>
#include <imgui.h>



template<typename T>
concept ImGuiDisplayBackend = requires(T display, SDL_Window* window, ImGuiIO* io)
{
    { display.renderPreFrame() };
    { display.renderPostFrame() };
    { display.processEvents() };
    { display.isDone() } -> std::same_as<bool>;
    { display.setWindow(window) };
    { display.getWindow() } -> std::same_as<SDL_Window*>;
    { display.getIO() } -> std::same_as<ImGuiIO*>;
    { display.setIO(io) } -> std::same_as<void>;
};


template<ImGuiDisplayBackend T>
void common_imgui_init(T& backend)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    backend.setIO(&ImGui::GetIO());
    backend.getIO()->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    backend.getIO()->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}


template<ImGuiDisplayBackend T>
void common_SDL_init(T& backend)
{
    bool sdl_init_success { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) };
    check_sdl_error(sdl_init_success, "SDL_Init");


    // create SDL window
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    std::string title {"Othello v " + std::to_string(Othello_VERSION_MAJOR) + "." + std::to_string(Othello_VERSION_MINOR)};
    int width {(int)(800 * main_scale)};
    int height {(int)(600 * main_scale)};
    backend.setWindow(SDL_CreateWindow(
        title.c_str()
        , width
        , height
        , SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY
    ));
    check_sdl_error(backend.getWindow(), "SDL_CreateWindow");
    SDL_SetWindowPosition(backend.getWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(backend.getWindow());
}


#endif // OTHELLO_DISPLAY_BACKEND_H