/**
 * @brief contains items used by tests for experiment
 */
#include <experiment/experiment.hpp>
#include <vector>


namespace experiment
{


using MockState = size_t;

/**
 * @brief mock game for testing interfaces
 * 
 * Generates N possible states, decreasing by one after each move
 *
 * @tparam N the number of states the game can generate
 */
template
<size_t N>
class MockGame : public Game<MockState> {
private:
	std::vector<MockState> played_states_;
public:
	std::vector<MockState> get_legal_states() override;
	std::vector<MockState> get_played_states() override;
	bool play_state(MockState next_legal_state) override;
	bool is_winning(MockState& state, int player) override;
};

template
<size_t N>
std::vector<MockState> MockGame<N>::get_legal_states() {
	std::vector<MockState> states {};
	for (size_t i = 0; i < N - played_states_.size(); ++i) {
		states.push_back(i);
	}
	return states;
}

template
<size_t N>
std::vector<MockState> MockGame<N>::get_played_states() {
	return played_states_;
}

template
<size_t N>
bool MockGame<N>::play_state(MockState next_legal_state) {
	played_states_.push_back(next_legal_state);
	return true;
}


template
<size_t N>
bool MockGame<N>::is_winning(MockState& state, int player) {
	return true;
}

template
<typename State>
class MockHypothesis : public Hypothesis<State> {
public:
	double get_value(State& state) {
		return 0;
	}
};



} // namespace experiment
