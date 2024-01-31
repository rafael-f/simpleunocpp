#pragma once
#include <string>
#include <memory>
#include "Mediator.h" // Used by all card behaviors

// Card Behavior interface, to be implemented by each card type.
class CardBehavior
{
public:
	virtual void execute() = 0;

	virtual ~CardBehavior() = default;

	virtual std::string& getSymbolToDraw() = 0;

	virtual bool checkCanBePlayed(std::shared_ptr<CardBehavior> other) = 0;

	virtual std::string getNameToDraw() = 0;
};
