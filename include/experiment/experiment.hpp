/*
 * Declaration of Experiment class, and associated pure
 * virtual classes
 * */

#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>

namespace experiment
{

template
<typename State>
struct Game {
public:
	virtual std::vector<State> get_legal_moves() = 0;
	virtual bool play_move(State next_legal_move) = 0;
	virtual bool is_winning(State& state, int player) = 0;
	virtual ~Game() {}
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
	virtual ~Hypothesis() {}
};


template
<typename State>
class Generator {
public:
	// generate a starting state using hypothesis
	virtual Game<State> get_initial(Hypothesis<State>& hypothesis) = 0;
	virtual ~Generator() {}
};

template
<typename State>
class Performer {
	// play a complete game from an initial state
	virtual void play_game(Hypothesis<State>& hypothesis, Game<State>& initial_state);
	virtual ~Performer() {}
};

template
<typename State>
class Critic {
	// estimate vtrain using current hypothesis's evaluation of next state where it is player's turn
	virtual std::vector<TrainingExample<State>> get_training_examples(Game<State>& finished_game, Hypothesis<State>& hypothesis) = 0;	
	virtual ~Critic() {}
};

template
<typename State>
class Generalizer {
	// get new hypothesis using training examples
	virtual Hypothesis<State> update_approximation(std::vector<TrainingExample<State>>& training_examples, Hypothesis<State>& curr_hypothesis) = 0;
	virtual ~Generalizer() {}
};

template
<typename State>
class Experiment {
private:
	Hypothesis<State> hypothesis_;
	Generator<State> generator_;
	Performer<State> performer_;
	Critic<State> critic_;
	Generalizer<State> generalizer_;
public:
	Experiment();
	// perform one loop of generate -> perform -> critique -> update
	void perform();
};

} // namespace experiment
#endif // EXPERIMENT_H
