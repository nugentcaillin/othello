#ifndef OTHELLO_APP_DISPLAY_H
#define OTHELLO_APP_DISPLAY_H

#include <othello/app/display/backend/DisplayBackend.hpp>
#include <othello/app/display/frontend/DisplayFrontend.hpp>

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
            backend_.processEvents();
            backend_.renderPreFrame();
            frontend_.render();
            backend_.renderPostFrame();
        }
    }
private:
    backend backend_;
    frontend frontend_;
};

#endif // OTHELLO_APP_DISPLAY_H