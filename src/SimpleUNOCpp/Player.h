#pragma once
#include <string>

// A player.
class Player
{
public:
	void setName(const std::string& name);

	std::string getName() const;

private:
	std::string _name;
};
