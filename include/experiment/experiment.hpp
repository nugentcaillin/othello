/*
 * Declaration of Experiment class, and associated pure
 * virtual classes
 * /

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>



template
<typename State>
struct Game {
	std::vector<State> get_legal_moves() = 0;
	static bool is_winning(State& state, int player) = 0;
};

template

<typename State>
struct TrainingExample {
	State state;
	double v_train;
};

template
<typename State>
class Hypothesis {
	// evaluate a game state using current approximation
	virtual double get_value(State& state) = 0;
};


template
<typename Game>
class Generator {
	// generate a starting state using hypothesis
	Game get_initial(Hypothesis& hypothesis) = 0;
};

template
<typename Game>
class Performer {
	// play a complete game from an initial state
	void play_game(Hypothesis& hypothesis, Game& initial_state);
};

template
<typename Game>
class Critic {
	// estimate vtrain using current hypothesis's evaluation of next state where it is player's turn
	std::vector<TrainingExample> get_training_examples(Game& finished_game, Hypothesis& hypothesis) = 0;	
};

class Generalizer {
	// get new hypothesis using training examples
	Hypothesis update_approximation(std::vector<TrainingExample>& training_examples, Hypothesis& curr_hypothesis) = 0;
};


class Experiment {
private:
	Hypothesis hypothesis_;
	Generator generator_;
	Performer performer_;
	Critic critic_;
	Generalizer generalizer_;
public:
	Experiment()
	// perform one loop of generate -> perform -> critique -> update
	void perform();
};

#endif // EXPERIMENT_H
