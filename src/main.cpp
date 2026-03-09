#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlgpu3.h>
#include <string>
#include <SDL3/SDL.h>




int main()
{
    // SDL Window stuff
    bool done;
    SDL_Init(SDL_INIT_VIDEO);

    const std::string WINDOW_TITLE = "";
    const int WINDOW_WIDTH { 1080 };
    const int WINDOW_HEIGHT { 720 };
    const SDL_WindowFlags WINDOW_FLAGS {}; 
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);

    if (window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT) done = true;
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}