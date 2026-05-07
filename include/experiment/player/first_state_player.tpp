#include "first_state_player.hpp"

namespace experiment
{

State FirstStatePlayer<Game>::chose_next_move(Game& game) {
	return game.get_legal_states().front();
}

}
