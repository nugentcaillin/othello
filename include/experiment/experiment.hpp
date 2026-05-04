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
<typename GameState>
struct Game {
public:
	using State = GameState;
	virtual std::vector<State> get_legal_states() = 0;
	virtual std::vector<State> get_played_states() = 0;
	virtual bool play_state(State next_legal_state) = 0;
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
public:
	// evaluate a game state using current approximation
	virtual double get_value(State& state) = 0;
	virtual ~Hypothesis() {}
};

template
<typename Game>
class Generator {
public:
	using State = typename Game::State;
	// generate a starting state using hypothesis
	virtual Game get_initial(Hypothesis<State>& hypothesis) = 0;
	virtual ~Generator() {}
};

template
<typename Game>
class Performer {
	using State = typename Game::State;
	// play a complete game from an initial state
	virtual void play_game(Hypothesis<State>& hypothesis, Game& game);
	virtual ~Performer() {}
};

template
<typename Game>
class Critic {
	using State = typename Game::State;
	// estimate vtrain using current hypothesis's evaluation of next state where it is player's turn
	virtual std::vector<TrainingExample<State>> get_training_examples(Game& finished_game, Hypothesis<State>& hypothesis) = 0;	
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
<typename Game>
class Experiment {
private:
	using State = typename Game::State;
	Hypothesis<State> hypothesis_;
	Generator<Game> generator_;
	Performer<Game> performer_;
	Critic<Game> critic_;
	Generalizer<State> generalizer_;
public:
	Experiment();
	// perform one loop of generate -> perform -> critique -> update
	void perform();
};

} // namespace experiment
#endif // EXPERIMENT_H
