#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <vector>

/**
 * @brief collection of interfaces for conducting unsupervised learning and
 * derived classes
 *
 * Provides an Experiment type, along with definitions for interfaces
 * that are needed by it, along with some general templates
 * 
 */
namespace experiment
{


/**
 * @brief Interface that defines a game
 * 
 * Defines the type of game to be used for the unsupervised learning and
 * forwards that state to be used by other classes
 *
 * @tparam GameState the type of state to use
 */
template
<typename GameState>
struct Game {
public:
	using State = GameState;
	/**
	 * @brief get a list of possible next moves at current state of game
	 * @returns a list of legal moves to play next
	 */
	virtual std::vector<State> get_legal_states() = 0;
	/**
	 * @brief get a list in order of each played state in game
	 * @returns a list of all states played in chronological order
	 */
	virtual std::vector<State> get_played_states() = 0;
	/**
	 * @brief play a legal state
	 * @pre state is legal
	 * @param next_legal_state the state to play
	 */
	virtual bool play_state(State next_legal_state) = 0;
	/**
	 * @brief check if a player has won
	 * @param state the game state to check
	 * @param player the turn order of player to check
	 */
	virtual bool is_winning(State& state, int player) = 0;
	virtual ~Game() {}
};

/**
 * @brief a training example to be used by generalizer
 *
 * contains the training state, along with the actual
 * reward for that state
 *
 * @tparam State the type of gamestate used by game
 */
template
<typename State>
struct TrainingExample {
	/** @brief the state chosen by the model */
	State state;
	/** @brief the actual reward of this state */
	double v_train;
};

/**
 * @brief a hypothesis to be used to predict reward
 *
 * assigns a reward value to current state using its features
 * @tparam State the type of gamestate used by the game
 */
template
<typename State>
class Hypothesis {
public:
	/**
	 * @brief evaluate a game state
	 *
	 * evaluate the reward of current game state
	 * using current approximation of reward
	 *
	 * @return the predicted reward of current state
	 */
	virtual double get_value(State& state) = 0;
	virtual ~Hypothesis() {}
};

/**
 * @brief generate an initial state
 *
 * uses the current hypothesis to generate a new
 * starting state
 *
 * @tparam Game the type of game to generate a starting
 * state for
 */
template
<typename Game>
class Generator {
public:
	using State = typename Game::State;
	/**
	 * @brief use current hypothesis to generate a starting state of game
	 * @param hypothesis the current hypothesis
	 * @returns a new game with initial state
	 */
	virtual Game get_initial(Hypothesis<State>& hypothesis) = 0;
	virtual ~Generator() {}
};

/**
 * @brief play a game
 *
 * Play one game from initial state to finish state in its entirety
 *
 * @tparam Game the type of game to play
 */
template
<typename Game>
class Performer {
	using State = typename Game::State;
	/**
	 * @brief play a game out fully
	 * @param hypothesis the current approximation of reward 
	 * @param game the game to play out
	 */
	virtual void play_game(Hypothesis<State>& hypothesis, Game& game);
	virtual ~Performer() {}
};

/**
 * @brief Convert a played game into training examples
 * @tparam Game the type of game
 */
template
<typename Game>
class Critic {
	using State = typename Game::State;
	/**
	 * @brief get a series of training examples from a finished game
	 * @param finished_game the finished game
	 * @param hypothesis the current hypothesis
	 */
	virtual std::vector<TrainingExample<State>> get_training_examples(Game& finished_game, Hypothesis<State>& hypothesis) = 0;	
	virtual ~Critic() {}
};

/**
 * @brief update hypothesis to fit training examples
 *
 * uses a series of completed training examples to get next 
 * hypothesis
 * @tparam State the type of game state used
 */
template
<typename State>
class Generalizer {
	/**
	 * @brief get a new hypothesis that better follows training examples
	 * @param training_examples the training examples
	 * @param curr_hypothesis the current hypothesis
	 */
	virtual Hypothesis<State> update_approximation(std::vector<TrainingExample<State>>& training_examples, Hypothesis<State>& curr_hypothesis) = 0;
	virtual ~Generalizer() {}
};

/**
 * @brief conduct an unsupervised learning experiment
 * 
 * Repetitively play a game and update hypothesis to
 * get better approximation of reward function
 *
 * @tparam Game the type of game to be played
 */
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
	/**
	 * @brief perform one training loop
	 * 
	 * perform one loop of generate, play, evaluate, generalize
	 */
	void perform();
};

} // namespace experiment


#endif // EXPERIMENT_H
