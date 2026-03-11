#include <othello/app/display/GuiTrainDisplay.hpp>


int main()
{
    GuiTrainDisplay display(1);
    while (!display.is_done()) display.render();
}
