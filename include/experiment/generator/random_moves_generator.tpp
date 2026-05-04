#include <random>

#include "../experiment.hpp"
#include "random_moves_generator.hpp"


namespace experiment
{

template
<typename Game, size_t N>
Game RandomMovesGenerator<Game, N>::get_initial(Hypothesis<State>& hypothesis) {
	Game initial {};

	// if available moves remaining and not picked enough already, pick random one
	for (size_t i = 0; i < N; ++i) {
		std::vector<State> possible_states = initial.get_legal_states();
		if (possible_states.size() == 0) break;
		
		std::uniform_int_distribution<size_t> dist(0, possible_states.size() - 1);
		size_t idx = dist(gen_);
		initial.play_state(possible_states.at(idx));
	}
	return initial;
}

template
<typename Game, size_t N>
RandomMovesGenerator<Game, N>::RandomMovesGenerator() 
: gen_ { std::random_device()() } 
{}


} // namespace experiment
