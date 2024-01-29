#pragma once

class KeyCodes
{
public:
	static const int ENTER_KEY = 13;
	static const int ESCAPE_KEY = 27;
	static const int ARROW_1 = 0;
	static const int ARROW_2 = 224;
	static const int LEFT_ARROW = 75;
	static const int RIGHT_ARROW = 77;
	static const int BACKSPACE = 8;

	static const char TOP_LEFT_CORNER = static_cast<char>(218);
	static const char TOP_RIGHT_CORNER = static_cast<char>(191);
	static const char BOTTOM_LEFT_CORNER = static_cast<char>(192);
	static const char BOTTOM_RIGHT_CORNER = static_cast<char>(217);

	static const char HORIZONTAL_LINE = static_cast<char>(196);
	static const char VERTICAL_LINE = static_cast<char>(179);

	static const char LEFT_DOUBLE_ARROW = static_cast<char>(174);
	static const char RIGHT_DOUBLE_ARROW = static_cast<char>(175);

	static const char SKIP_TURN = static_cast<char>(232);

	static const char SWAP_LEFT = static_cast<char>(220);
	static const char SWAP_RIGHT = static_cast<char>(223);
};
