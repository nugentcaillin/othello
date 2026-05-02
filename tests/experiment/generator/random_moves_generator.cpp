#include <gtest/gtest.h>
#include <experiment/generator/random_moves_generator.hpp>
#include <experiment/experiment.hpp>
#include <vector>

namespace experiment
{

/* Mock game for generator - 
 * have template parameter for number of possible states,
 * possible states are n - number of states made
 * */
using MockState = size_t;

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

class RandomMovesGeneratorTest : public testing::Test {
protected:
	inline static const size_t SELECTED_MOVES = 4;
	inline static const size_t LESS_SELECTED = SELECTED_MOVES - 1;
	RandomMovesGenerator<MockGame<SELECTED_MOVES>, SELECTED_MOVES> enough;
	RandomMovesGenerator<MockGame<LESS_SELECTED>, SELECTED_MOVES> not_enough;
	MockHypothesis<MockState> hypo {};
};

TEST_F(RandomMovesGeneratorTest, GameHasInitialStateAfterGeneration) {
	auto game = enough.get_initial(hypo);
	EXPECT_GT(game.get_played_states().size(), 0);
}
TEST_F(RandomMovesGeneratorTest, GeneratesSpecifiedNumIfPossible) {
	auto game = enough.get_initial(hypo);
	EXPECT_EQ(game.get_played_states().size(), SELECTED_MOVES);
}
TEST_F(RandomMovesGeneratorTest, GeneratesMaxPossibleIfSpecifiedImpossible) {
	auto game = not_enough.get_initial(hypo);
	EXPECT_EQ(game.get_played_states().size(), LESS_SELECTED);
}

} // namespace experiment
