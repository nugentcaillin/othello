#ifndef OTHELLO_APP_DISPLAY_H
#define OTHELLO_APP_DISPLAY_H

#include <othello/app/display/backend/DisplayBackend.hpp>
#include <othello/app/display/frontend/DisplayFrontend.hpp>
#include <iostream>

template<ImGuiDisplayBackend backend, DisplayFrontend frontend>
class Display 
{
public:
    Display()
    : backend_ {}
    , frontend_(1u)
    {}
    void run() {
        while (!backend_.isDone())
        {
            std::cout << "loop start\n";
            backend_.processEvents();
            std::cout << "preframe\n";
            backend_.renderPreFrame();
            std::cout<< "imgui render\n";
            frontend_.render();
            std::cout << "postframe\n";
            backend_.renderPostFrame();
        }
    }
private:
    backend backend_;
    frontend frontend_;
};

#endif // OTHELLO_APP_DISPLAY_H