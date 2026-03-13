#include <othello/app/display/Display.hpp>
#include <othello/app/display/frontend/TrainDisplayGui.hpp>
#include <othello/app/display/backend/Sdl3RendererDisplay.hpp>


int main()
{
    // create display
    Display<SDL3RendererBackend, TrainDisplayGui> display {};

    // create training threads

    // start display
    display.run();
    return 0;
}
