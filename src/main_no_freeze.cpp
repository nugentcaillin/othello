#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlgpu3.h>
#include <string>
#include <SDL3/SDL.h>
#include <iostream>
#include <othello_config.hpp>

// exit prematurely if sdl call returns value that casts to flase (0)
void check_sdl_error(bool success, std::string sdl_func)
{
    if (!success)
    {
        throw std::runtime_error("Error in " + sdl_func + "(): " + std::string(SDL_GetError()));
    }
}

int main()
{
    // setup SDL
    bool sdl_init_success { SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) };
    check_sdl_error(sdl_init_success, "SDL_Init");


    // create SDL window
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    std::string title {"Othello v " + std::to_string(Othello_VERSION_MAJOR) + "." + std::to_string(Othello_VERSION_MINOR)};
    int width {(int)(800 * main_scale)};
    int height {(int)(600 * main_scale)};
    SDL_Window* window = SDL_CreateWindow(
        title.c_str()
        , width
        , height
        , SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );
    check_sdl_error(window, "SDL_CreateWindow");
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(window);


    // create GPU device
    SDL_GPUDevice* device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_METALLIB
        , true
        , NULL
    );
    check_sdl_error(device, "SDL_CreateGPUDevice");

    // claim window
    check_sdl_error(
        SDL_ClaimWindowForGPUDevice(device, window)
        , "SDL_ClaimWindowForGPUDevice"
    );

    // ImGui Initialization
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // ImGui Backends


    // main loop


    bool done = false;
    unsigned int event_counter {};
    unsigned int loop_counter {};
    while (!done)
    {
        std::cout << "loop (" << loop_counter++ << ")\n";
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            std::cout << "event (" << event_counter++ << ")\n";
            if (event.type == SDL_EVENT_QUIT) done = true;
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) std::cout << "md\n";
        }
        std::cout << "done polling events, starting render\n";

        // ImGui frame

        

        // render


        SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(device);
        SDL_GPUTexture* swapchain_texture;
        SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, NULL, NULL);

        if (swapchain_texture != NULL)
        {
            SDL_GPUColorTargetInfo colour_target_info {};
            colour_target_info.texture = swapchain_texture;
            colour_target_info.clear_color = (SDL_FColor){ 0.3f, 0.6f, 0.5f, 1.0f };
            colour_target_info.load_op = SDL_GPU_LOADOP_CLEAR;
            colour_target_info.store_op = SDL_GPU_STOREOP_STORE;
            colour_target_info.mip_level = 0;
            colour_target_info.layer_or_depth_plane = 0;
            colour_target_info.cycle = false;

            std::cout << "starting pass\n";

            SDL_GPURenderPass* render_pass = SDL_BeginGPURenderPass(
                command_buffer
                , &colour_target_info
                , 1
                , NULL
            );
            std::cout << "ending pass\n";
            SDL_EndGPURenderPass(render_pass);
            std::cout << "render pass null: " << (render_pass == NULL) << "\n";
        }
        std::cout << "submitting command buffer\n";
        bool ok = SDL_SubmitGPUCommandBuffer(command_buffer);
        check_sdl_error(ok, "SDL_SubmitGPUCommandBuffer");
        std::cout << "done with render\n";
    }

    // cleanup
    SDL_WaitForGPUIdle(device);


    SDL_ReleaseWindowFromGPUDevice(device, window);
    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}
