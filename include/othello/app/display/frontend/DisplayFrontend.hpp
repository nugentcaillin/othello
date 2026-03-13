#ifndef OTHELLO_DISPLAY_FRONTEND_H
#define OTHELLO_DISPLAY_FRONTEND_H

#include <cstddef>
#include <concepts>
#include <cstdint>

typedef uint64_t board_t;

template<typename T>
concept DisplayFrontend = requires(T frontend, size_t num_boards, size_t index, board_t board) 
{
    { T(num_boards) };
    { frontend.render() };
    { frontend.set_board(index, board) };
    { frontend.set_board_count(num_boards) };
};

#endif // OTHELLO_DISPLAY_FRONTEND_H