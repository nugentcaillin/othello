#include "first_state_player.hpp"
#include <stdexcept>

namespace experiment
{
template
<typename Game>
FirstStatePlayer<Game>::State FirstStatePlayer<Game>::choose_next_move(Game& game) {
	if (game.get_legal_states().empty()) throw std::out_of_range("Game has no states");
	return game.get_legal_states().front();
}

}
