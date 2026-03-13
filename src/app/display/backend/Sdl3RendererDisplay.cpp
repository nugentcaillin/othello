#include <othello/app/display/backend/Sdl3RendererDisplay.hpp>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <othello/app/display/backend/SdlError.hpp>
#include <othello_config.hpp>


SDL3RendererBackend::SDL3RendererBackend()
{
    // setup SDL
    bool sdl_init_success { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) };
    check_sdl_error(sdl_init_success, "SDL_Init");


    // create SDL window
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    std::string title {"Othello v " + std::to_string(Othello_VERSION_MAJOR) + "." + std::to_string(Othello_VERSION_MINOR)};
    int width {(int)(800 * main_scale)};
    int height {(int)(600 * main_scale)};
    window_ = SDL_CreateWindow(
        title.c_str()
        , width
        , height
        , SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );
    check_sdl_error(window_, "SDL_CreateWindow");
    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window_);


    // create SDL renderer
    renderer_ = SDL_CreateRenderer(window_, NULL);
    check_sdl_error(renderer_, "SDL_Create_Renderer");
    SDL_SetRenderVSync(renderer_, 1);
    // ImGui Initialization
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io_ = &ImGui::GetIO();
    io_->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io_->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // ImGui Backends
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
bool SDL3RendererBackend::isDone()
{
    return done_;
}