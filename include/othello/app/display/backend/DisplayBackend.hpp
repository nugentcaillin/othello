#ifndef OTHELLO_DISPLAY_BACKEND_H
#define OTHELLO_DISPLAY_BACKEND_H

#include <concepts>
#include <stdexcept>



template<typename T>
concept ImGuiDisplayBackend = requires(T display)
{
    { display.renderPreFrame() };
    { display.renderPostFrame() };
    { display.processEvents() };
    { display.isDone() } -> std::same_as<bool>;
};






#endif // OTHELLO_DISPLAY_BACKEND_H