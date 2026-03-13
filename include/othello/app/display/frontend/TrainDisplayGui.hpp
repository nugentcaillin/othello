#ifndef OTHELLO_DISPLAY_TRAIN_DISPLAY_GUI_H
#define OTHELLO_DISPLAY_TRAIN_DISPLAY_GUI_H

#include <cstddef>
#include <othello/app/display/frontend/DisplayFrontend.hpp>
#include <imgui.h>

typedef uint64_t board_t;

class TrainDisplayGui {
public:
    TrainDisplayGui(size_t num_boards);
    ~TrainDisplayGui();
    void render();
    void set_board(size_t index, board_t board);
    void set_board_count(size_t num_boards);
private:
    const size_t MAX_BOARDS_ { 5 };
    size_t num_boards_;
};


static_assert(DisplayFrontend<TrainDisplayGui>);

#endif // OTHELLO_DISPLAY_TRAIN_DISPLAY_GUI_H