# simpleunocpp
A simple UNO game to train C++ programming.

```mermaid
---
title: UNO CPP
---
classDiagram

	class Mediator {
		<<Singleton>>
		+registerListener()
		+fireEvent()
	}

    class GameManager {
        +start()        
        -run()
        -load()
    }

    GameManager *-- Window
    GameManager *-- StateManager

    class Window {
        +isOpen() bool
        +clear()
	+setCursorPosition()
	+setConsoleColor()
    }

    class StateManager {
        +draw(Window)
	+setState()
	+handleInput()
    }
	
    StateManager o-- State

    class State {
        <<Interface>>
        +draw(Window)
	+handleInput()
    }

    State <|-- MenuState
    State <|-- PlayerSelectState
    State <|-- PlayerNamesState
    State <|-- GameState
    State <|-- GameOverState
	
    class GameState {
    }

    GameState *-- PlayerManager
    GameState *-- CardsLoader

    class CardsLoader {
        +load()
    }

    class Card {
    }

    class Player {
        +string name
    }

    Player o-- Card

    class PlayerManager {
        +addPlayer(Player)
    }

    class CardBehavior {
        <<Interface>>
    }

    class NormalCardBehavior {
    }

    class SkipTurnCardBehavior {
    }

    class DrawMoreCardBehavior {
        -int amount
    }

    class ReverseTurnCardBehavior {
    }

    class SwapHandCardBehavior {
    }

    class DrawDiscardedCardBehavior {
        -int amount
    }

    Card *-- CardBehavior

    CardBehavior <|-- NormalCardBehavior
    CardBehavior <|-- SkipTurnCardBehavior
    CardBehavior <|-- DrawMoreCardBehavior
    CardBehavior <|-- ReverseTurnCardBehavior
    CardBehavior <|-- SwapHandCardBehavior
    CardBehavior <|-- DrawDiscardedCardBehavior

    PlayerManager o-- Player

```
