#include <iostream>
#include "game.h"
#include "board.h"


int main(int argc, char* const argv[])
{
    Player* currentPlayer = NULL;


    Game::initialize();
    Board::getBoard()->display(cout);


    while (true)
    {
        currentPlayer = Game::getNextPlayer();
        while (!currentPlayer->makeMove())
        {
            cerr << "Nie mozna wykonac takiego ruchu" << endl;
        }
        Board::getBoard()->display(cout);
    }

    return 0;
}
