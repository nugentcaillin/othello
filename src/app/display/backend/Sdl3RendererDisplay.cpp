#include <othello/app/display/backend/Sdl3RendererDisplay.hpp>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <othello/app/display/backend/DisplayBackend.hpp>
#include <othello/app/display/backend/SdlError.hpp>
#include <othello_config.hpp>


SDL3RendererBackend::SDL3RendererBackend()
{
    common_SDL_init<SDL3RendererBackend>(*this);
    
    renderer_ = SDL_CreateRenderer(window_, NULL);
    check_sdl_error(renderer_, "SDL_Create_Renderer");
    SDL_SetRenderVSync(renderer_, 1);

    common_imgui_init<SDL3RendererBackend>(*this);

    ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer3_Init(renderer_);
}

SDL3RendererBackend::~SDL3RendererBackend()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void SDL3RendererBackend::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT) done_ = true;
    }
}

void SDL3RendererBackend::renderPreFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
}
void SDL3RendererBackend::renderPostFrame()
{
    ImGui::Render();
    SDL_SetRenderScale(renderer_, io_->DisplayFramebufferScale.x, io_->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColorFloat(renderer_, 1.0f, 1.0f, 1.0f, 1.0f);
    SDL_RenderClear(renderer_);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer_);
    SDL_RenderPresent(renderer_);
}


bool SDL3RendererBackend::isDone() { return done_; }
SDL_Window* SDL3RendererBackend::getWindow() { return window_; }
void SDL3RendererBackend::setWindow(SDL_Window* window) { window_ = window; }
ImGuiIO* SDL3RendererBackend::getIO() { return io_; }
void SDL3RendererBackend::setIO(ImGuiIO* io) { io_ = io; }