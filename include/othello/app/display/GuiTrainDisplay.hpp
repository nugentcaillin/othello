#ifndef OTHELLO_APP_GUI_TRAIN_DISPLAY_H
#define OTHELLO_APP_GUI_TRAIN_DISPLAY_H

#include <imgui.h>
#include <SDL3/SDL.h>

struct board_t;

class GuiTrainDisplay {
public:
    GuiTrainDisplay(size_t num_boards);
    ~GuiTrainDisplay();
    void render();
    void set_board(size_t index, board_t board);
    void set_board_num(size_t num_boards);
    bool is_done() { return done_; };
private:
    const size_t MAX_BOARDS_ { 5 };
    bool done_;
    SDL_Renderer* renderer_;
    ImGuiIO* io_;
    SDL_Window* window_;
};

#endif // OTHELLO_APP_GUI_TRAIN_DISPLAY_H