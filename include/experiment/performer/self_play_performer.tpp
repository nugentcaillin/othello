#include "self_play_performer.hpp"
#include "../experiment.hpp"

namespace experiment
{

template
<typename Game, typename Player, size_t MAX_ITER>	
void SelfPlayPerformer<Game, Player, MAX_ITER>::play_game(
		Hypothesis<State>& hypothesis, 
		Game& game) {
	while (should_play()) {
		State next = player_.choose_next_move(game);
		game.play_state(next);
	}
}

template
<typename Game, typename Player, size_t MAX_ITER>	
SelfPlayPerformer<Game, Player, MAX_ITER>::SelfPlayPerformer(Player player)
: player_ { player }
{}

template
<typename Game, typename Player, size_t MAX_ITER>
bool SelfPlayPerformer<Game, Player, MAX_ITER>::should_play(Game& game) {
	return game.get_played_states.size() < MAX_ITER && 
		   game.get_legal_states().size() > 0;
}

// partially specialized class template to allow for below
// SelfPlayPerformer::should_play partial specialization
template
<typename Game, typename Player>
class SelfPlayPerformer<Game, Player, 0> : public Performer<Game> {
private:
	Player player_;
	bool should_play(Game& game);
public:
	using typename Performer<Game>::State;
	
	void play_game(Hypothesis<State>& hypothesis, Game& game) override;
	SelfPlayPerformer(Player player);
	SelfPlayPerformer() = delete;
};

template
<typename Game, typename Player>
bool SelfPlayPerformer<Game, Player, 0>::should_play(Game& game) {
	return game.get_legal_states().size() > 0;
}


} // namespace experiment


