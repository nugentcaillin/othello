#include <othello/app/display/backend/SDLGPU3Backend.hpp>
#include <othello/app/display/backend/DisplayBackend.hpp>
#include <othello/app/display/backend/SdlError.hpp>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>
#include <iostream>

SDLGPU3Backend::SDLGPU3Backend()
: window_ {nullptr}
, done_ { false }
, io_ {nullptr}
, gpu_device_ {nullptr}
{
    common_SDL_init<SDLGPU3Backend>(*this);

    setGpuDevice(SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV 
        , true 
        , nullptr
    ));
    check_sdl_error(getGpuDevice(), "SDL_CreateGPUDevice");

    check_sdl_error(
        SDL_ClaimWindowForGPUDevice(getGpuDevice(), getWindow())
        , "SDL_ClaimWindowForGPUDevice"
    );

    SDL_SetGPUSwapchainParameters(getGpuDevice(), getWindow(), SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);


    common_imgui_init<SDLGPU3Backend>(*this);

    ImGui_ImplSDL3_InitForSDLGPU(getWindow());
    ImGui_ImplSDLGPU3_InitInfo init {};
    init.Device = getGpuDevice();
    init.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(getGpuDevice(), getWindow()); 
    init.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
    ImGui_ImplSDLGPU3_Init(&init);
}
SDLGPU3Backend::~SDLGPU3Backend()
{
	std::cout << "sdl backend destructor called\n";
    SDL_WaitForGPUIdle(getGpuDevice());
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_ReleaseWindowFromGPUDevice(getGpuDevice(), getWindow());
    SDL_DestroyGPUDevice(getGpuDevice());
    setGpuDevice(nullptr);
    SDL_DestroyWindow(getWindow());
    setWindow(nullptr);
    SDL_Quit();
}
void SDLGPU3Backend::renderPreFrame()
{
        ImGui_ImplSDLGPU3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
}
void SDLGPU3Backend::renderPostFrame()
{
    ImDrawData* draw_data = ImGui::GetDrawData();
    SDL_GPUCommandBuffer* cmdbuf = SDL_AcquireGPUCommandBuffer(getGpuDevice());
    SDL_GPUTexture* texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(cmdbuf, getWindow(), &texture, nullptr, nullptr);
    bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
    if (texture != nullptr && !is_minimized)
    {
        ImGui_ImplSDLGPU3_PrepareDrawData(draw_data, cmdbuf);
        SDL_GPUColorTargetInfo info {};
        info.texture = texture;
        info.clear_color = SDL_FColor { 1.0f, 1.0f, 1.0f, 1.0f };
        info.load_op = SDL_GPU_LOADOP_CLEAR;
        info.store_op = SDL_GPU_STOREOP_STORE;
        info.mip_level = 0;
        info.layer_or_depth_plane = 0;
        info.cycle = false;
        SDL_GPURenderPass* render = SDL_BeginGPURenderPass(cmdbuf, &info, 1, nullptr);
        ImGui_ImplSDLGPU3_RenderDrawData(draw_data, cmdbuf, render, nullptr);
        SDL_EndGPURenderPass(render);
    }
    SDL_SubmitGPUCommandBuffer(cmdbuf);
}
void SDLGPU3Backend::processEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            done_ = true;
            std::cout << "quit\n";
        }
    }
}
bool SDLGPU3Backend::isDone() { return done_; }
void SDLGPU3Backend::setWindow(SDL_Window* window) { window_ = window; }
SDL_Window* SDLGPU3Backend::getWindow() { return window_; }
ImGuiIO* SDLGPU3Backend::getIO() { return io_; }
void SDLGPU3Backend::setIO(ImGuiIO* io) { io_ = io; }
SDL_GPUDevice* SDLGPU3Backend::getGpuDevice() { return gpu_device_; }
void SDLGPU3Backend::setGpuDevice(SDL_GPUDevice* device) { gpu_device_ = device; }

