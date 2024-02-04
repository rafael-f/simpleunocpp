#pragma once
#include "Window.h"
#include "Colors.h"

class ColorPickItem
{
public:
	explicit ColorPickItem(const Colors& color);

	int draw(const Window& window, const int& row, const int& column) const;

	void setSelected(const bool& selected);

	bool getSelected() const;

	Colors getSelectedColor() const;

private:
	bool _isSelected = false;

	Colors _color;
};
