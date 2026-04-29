#ifndef OTHELLO_DISPLAY_SDLGPU3_BACKEND_H
#define OTHELLO_DISPLAY_SDLGPU3_BACKEND_H

#include <SDL3/SDL.h>
#include <imgui.h>
#include <othello/app/display/backend/DisplayBackend.hpp>

class SDLGPU3Backend {
public:
    SDLGPU3Backend();
    ~SDLGPU3Backend();
    void renderPreFrame();
    void renderPostFrame();
    void processEvents();
    bool isDone();
    void setWindow(SDL_Window* window);
    SDL_Window* getWindow();
    ImGuiIO* getIO();
    void setIO(ImGuiIO* io);
    SDL_GPUDevice* getGpuDevice();
    void setGpuDevice(SDL_GPUDevice* device);

private:
    SDL_Window* window_;
    bool done_;
    ImGuiIO* io_;
    SDL_GPUDevice* gpu_device_;
};

static_assert(ImGuiDisplayBackend<SDLGPU3Backend>);

#endif // OTHELLO_DISPLAY_SDLGPU3_BACKEND_H