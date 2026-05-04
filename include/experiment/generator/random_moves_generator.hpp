#ifndef EXPERIMENT_RANDOM_MOVES_GENERATOR_H
#define EXPERIMENT_RANDOM_MOVES_GENERATOR_H

#include <random>

#include "../experiment.hpp"

namespace experiment
{

/**
 * @brief Perform random moves to get initial state
 *
 * attempts to perform N random moves if possible
 *
 * @tparam Game the type of game to generate initial state for
 * @tparam N the number of random moves to attempt to make
 */
template
<typename Game, size_t N>
class RandomMovesGenerator : public Generator<Game> {
private:
	std::mt19937 gen_;
public:
	using typename Generator<Game>::State;
	/**
	 * @brief attempt to play N random moves on blank game
	 *
	 * generate blank game, then play up to N random moves or
	 * maximum possible, whichever is lesser
	 * 
	 * @param hypothesis the current approximation of reward for a state
	 * @returns a game with initial state selected through random moves
	 */
	Game get_initial(Hypothesis<State>& hypothesis) override;
	RandomMovesGenerator();
};





} // namespace experiment
#include "random_moves_generator.tpp"
#endif // EXPERIMENT_RANDOM_MOVES_GENERATOR_H
