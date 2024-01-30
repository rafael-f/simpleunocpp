#pragma once
#include <string>
#include <memory>

// Card Behavior interface, to be implemented by each card type.
class CardBehavior
{
public:
	virtual void execute() = 0;

	virtual ~CardBehavior() = default;

	virtual std::string& getStringToDraw() = 0;

	virtual bool checkCanBePlayed(std::shared_ptr<CardBehavior> other) = 0;
};
