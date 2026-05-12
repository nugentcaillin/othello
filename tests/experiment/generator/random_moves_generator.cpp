#include <gtest/gtest.h>
#include <experiment/generator/random_moves_generator.hpp>
#include <experiment/experiment.hpp>

#include "../common.hpp"

namespace experiment
{

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
