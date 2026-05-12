#include <gtest/gtest.h>
#include <experiment/player/first_state_player.hpp>
#include <experiment/experiment.hpp>
#include <stdexcept>

#include "../common.hpp"

namespace experiment
{

class FirstStatePlayerTest : public testing::Test {
protected:
	inline static const size_t MOVES = 4;
	inline static const MockState first_move = 0;
	MockGame<MOVES> game_multi;
	MockGame<1> game_single;
	MockGame<0> game_none;
	FirstStatePlayer<MockGame<MOVES>> multi_moves_player {};
	FirstStatePlayer<MockGame<1>> single_move_player {};
	FirstStatePlayer<MockGame<0>> no_moves_player {};
};

TEST_F(FirstStatePlayerTest, noMovesPickThrows) {
	EXPECT_THROW(no_moves_player.choose_next_move(game_none), std::out_of_range);
}
TEST_F(FirstStatePlayerTest, SingleMovePicksFirst) {
	EXPECT_EQ(single_move_player.choose_next_move(game_single), first_move);
}
TEST_F(FirstStatePlayerTest, MultiMovePicksFirst) {
	EXPECT_EQ(multi_moves_player.choose_next_move(game_multi), first_move);
}



} // namespace experiment
