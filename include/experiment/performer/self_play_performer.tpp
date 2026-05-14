#include "self_play_performer.hpp"
#include "../experiment.hpp"

namespace experiment
{

template
<typename Game, typename Player, size_t MAX_ITER>	
void SelfPlayPerformer<Game, Player, MAX_ITER>::play_game(
		Hypothesis<State>& hypothesis, 
		Game& game) {
	while (should_play(game)) {
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
SelfPlayPerformer<Game, Player, MAX_ITER>::SelfPlayPerformer()
: player_ {}
{}

template
<typename Game, typename Player, size_t MAX_ITER>
bool SelfPlayPerformer<Game, Player, MAX_ITER>::should_play(Game& game) {
	return game.get_played_states().size() < MAX_ITER && 
		   game.get_legal_states().size() > 0;
}


// partial specialization for case with unlimited moves - need to
// duplicate class since function partial specializations aren't allowed 

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
	SelfPlayPerformer();
};

template
<typename Game, typename Player>
bool SelfPlayPerformer<Game, Player, 0>::should_play(Game& game) {
	return game.get_legal_states().size() > 0;
}


template
<typename Game, typename Player>	
SelfPlayPerformer<Game, Player, 0>::SelfPlayPerformer(Player player)
: player_ { player }
{}

template
<typename Game, typename Player>	
SelfPlayPerformer<Game, Player, 0>::SelfPlayPerformer()
: player_ {}
{}

template
<typename Game, typename Player>	
void SelfPlayPerformer<Game, Player, 0>::play_game(
		Hypothesis<State>& hypothesis, 
		Game& game) {
	while (should_play(game)) {
		State next = player_.choose_next_move(game);
		game.play_state(next);
	}
}


} // namespace experiment


