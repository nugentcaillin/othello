#ifndef OTHELLO_SDL3_RENDER_BACKEND_H
#define OTHELLO_SDL3_RENDER_BACKEND_H

#include <imgui.h>
#include <SDL3/SDL.h>
#include <othello/app/display/backend/DisplayBackend.hpp>




class SDL3RendererBackend {
public:
    SDL3RendererBackend();
    ~SDL3RendererBackend();
    void renderPreFrame();
    void renderPostFrame();
    void processEvents();
    bool isDone();
    void setWindow(SDL_Window* window);
    SDL_Window* getWindow();
    ImGuiIO* getIO();
    void setIO(ImGuiIO* io);

private:
    SDL_Renderer* renderer_;
    SDL_Window* window_;
    bool done_;
    ImGuiIO* io_;
};


static_assert(ImGuiDisplayBackend<SDL3RendererBackend>);
#endif // OTHELLO_SDL3_RENDER_BACKEND_H