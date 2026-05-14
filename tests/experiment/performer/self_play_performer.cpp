#include <gtest/gtest.h>
#include <experiment/performer/self_play_performer.hpp>
#include <experiment/player/first_state_player.hpp> // using this player for mock
#include <experiment/experiment.hpp>

#include "../common.hpp"

namespace experiment
{

class SelfPlayPerformerTest : public testing::Test {
protected:
	inline static const size_t MAX_ITER = 5;
	inline static const size_t SHORT_MAX_MOVES = MAX_ITER - 1;
	inline static const size_t LONG_MAX_MOVES = MAX_ITER + 1;
	using LongMock = MockGame<LONG_MAX_MOVES>;
	using ShortMock = MockGame<SHORT_MAX_MOVES>;
	using LongPlayer = FirstStatePlayer<LongMock>;
	using ShortPlayer = FirstStatePlayer<ShortMock>;
	using MaxIterPerformer = SelfPlayPerformer<LongMock, LongPlayer, MAX_ITER>;
	using MaxMovesPerformer = SelfPlayPerformer<ShortMock, ShortPlayer, MAX_ITER>;
	using ExhaustivePerformer = SelfPlayPerformer<LongMock, LongPlayer, 0>;
	using LongMockHypothesis = MockHypothesis<LongMock::State>;
	using ShortMockHypothesis = MockHypothesis<ShortMock::State>;
	LongMock long_mock;
	ShortMock short_mock;
	MaxIterPerformer max_iter_performer;
	MaxMovesPerformer max_moves_performer;
	LongMockHypothesis long_hypo {};
	ShortMockHypothesis short_hypo {};
	ExhaustivePerformer exhaustive_performer;

	void SetUp() override {
		long_mock = LongMock();
		short_mock = ShortMock();
		max_iter_performer = MaxIterPerformer();
		max_moves_performer = MaxMovesPerformer();
		exhaustive_performer = ExhaustivePerformer();
	}
};

TEST_F(SelfPlayPerformerTest, stopsAtMaxIter) {
	max_iter_performer.play_game(long_hypo, long_mock);
	EXPECT_EQ(long_mock.get_played_states().size(), MAX_ITER);
}

TEST_F(SelfPlayPerformerTest, stopsIfNoMovesRemaining) {
	max_moves_performer.play_game(short_hypo, short_mock);
	EXPECT_EQ(short_mock.get_played_states().size(), SHORT_MAX_MOVES);
}

TEST_F(SelfPlayPerformerTest, zeroMaxMovesExhaustsMoves) {
	exhaustive_performer.play_game(long_hypo, long_mock);
	EXPECT_EQ(long_mock.get_played_states().size(), LONG_MAX_MOVES);
}

} // namespace experiment
