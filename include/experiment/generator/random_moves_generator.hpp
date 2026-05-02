/**
 * Provides declaration for random move generator,
 * a generator that ignores given hypothesis and selects
 * N random moves from possible moves, or max available,
 * whichever is lesser
 * */
#ifndef EXPERIMENT_RANDOM_MOVES_GENERATOR_H
#define EXPERIMENT_RANDOM_MOVES_GENERATOR_H

#include "../experiment.hpp"

namespace experiment
{


template
<typename Game, size_t N>
class RandomMovesGenerator : public Generator<Game> {
public:
	// get a game that is the result of playing up to N random moves
	Game get_initial(Hypothesis<typename Game::State>& hypothesis) override {
		return {};
	}
	RandomMovesGenerator() {

	}
};


} // namespace experiment
#endif // EXPERIMENT_RANDOM_MOVES_GENERATOR_H
