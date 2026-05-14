#ifndef EXPERIMENT_SELF_PLAY_PERFORMER_H
#define EXPERIMENT_SELF_PLAY_PERFORMER_H

#include "../experiment.hpp"

namespace experiment
{

/**
 * @brief use a single player to play against itself every single turn
 *
 * @tparam Game the type of game to be played
 * @tparam Player the type of player to be used
 * @tparam max turns to play (0 for no maximum)
 */
template
<typename Game, typename Player, size_t MAX_ITER>
class SelfPlayPerformer : public Performer<Game> {
private:
	Player player_;
	bool should_play(Game& game);
public:
	using typename Performer<Game>::State;
	
	void play_game(Hypothesis<State>& hypothesis, Game& game) override;
	SelfPlayPerformer(Player player);
	SelfPlayPerformer();
};


} // namespace experiment

#include "self_play_performer.tpp"

#endif // EXPERIMENT_SELF_PLAY_PERFORMER_H
