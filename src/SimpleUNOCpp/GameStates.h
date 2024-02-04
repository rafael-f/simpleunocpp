#pragma once

// TODO remove and use separate game states
enum class GameStates
{
	NORMAL,
	DISPLAY_NEW_CARDS,
	FORCED_DRAW,
	FORCED_DRAW_DISCARD,
	FORCED_SKIP,
	SELECT_PLAYER,
	SELECT_COLOR,
	FORCED_DRAW_WILD,
	FORCED_DRAW_PUNISH
};
