#include <othello/app/display/frontend/TrainDisplayGui.hpp>
#include <imgui.h>

TrainDisplayGui::TrainDisplayGui(size_t num_boards)
: num_boards_ { num_boards }
{
}

TrainDisplayGui::~TrainDisplayGui()
{
}

void TrainDisplayGui::render()
{
    ImGui::NewFrame();
    {
        static unsigned int count {};
        ImGui::Begin("Test Window");
    
        ImGui::Text("Hello, World!");
        if (ImGui::Button("Click me!")) ++count;
        ImGui::Text("Counter: %d", count);
        
        ImGui::End();
    }
    ImGui::Render();
}

void TrainDisplayGui::set_board(size_t index, board_t board)
{
}

void TrainDisplayGui::set_board_count(size_t num_boards)
{
}
