/**
 * Provides declaration for random move generator,
 * a generator that ignores given hypothesis and selects
 * N random moves from possible moves, or max available,
 * whichever is lesser
 * */
#ifndef EXPERIMENT_RANDOM_MOVES_GENERATOR_H
#define EXPERIMENT_RANDOM_MOVES_GENERATOR_H

#include <random>

#include "../experiment.hpp"

namespace experiment
{


template
<typename Game, size_t N>
class RandomMovesGenerator : public Generator<Game> {
private:
	std::mt19937 gen_;
public:
	using typename Generator<Game>::State;
	// get a game that is the result of playing up to N random moves
	Game get_initial(Hypothesis<State>& hypothesis) override;
	RandomMovesGenerator();
};





} // namespace experiment
#include "random_moves_generator.tpp"
#endif // EXPERIMENT_RANDOM_MOVES_GENERATOR_H
