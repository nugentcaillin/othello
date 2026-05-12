#ifndef EXPERIMENT_FIRST_STATE_PLAYER_H
#define EXPERIMENT_FIRST_STATE_PLAYER_H

#include "../experiment.hpp"

namespace experiment
{

template
<typename Game>
class FirstStatePlayer : public Player<Game> {
public:
	using typename Player<Game>::State;
	/**
	 * @brief select the first move available in list
	 * @pre game has a next move available
	 * @param game the game to pick next move
	 * @returns the first available state of game
	 */
	State choose_next_move(Game& game) override;
};

}
#include "first_state_player.tpp"
#endif // EXPERIMENT_FIRST_STATE_PLAYER_H
