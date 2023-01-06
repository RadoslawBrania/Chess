#include <iostream>
#include "player.h"
#include "board.h"
#include "game.h"
#include <string>

#define X_MIN 'a'
#define X_MAX 'h'
#define Y_MIN '1'
#define Y_MAX '8'

Player::Player(string name, bool isWhite, King& myKing, set<Piece*>& myPieces) :
_name(name), _isWhite(isWhite), _myPieces(myPieces), _myKing(myKing)
{
}

Player::~Player()
{
}

bool Player::makeMove()
{
    string badInput; 
    string fromSquare =  "  ";
    string toSquare = "  ";
    int fromX;
    int fromY;
    int toX;
    int toY;
    

    if(inCheck())
    {
        cout << _name << " jest w szachu!" << endl;
    }
    

    cout << _name << " wprowadz ruch (np. a2 a4): ";
    cin >> fromSquare >> toSquare;
    

    while(fromSquare.length() != 2 ||
          toSquare.length() != 2 ||
          tolower(fromSquare.at(0)) < X_MIN ||
          tolower(fromSquare.at(0)) > X_MAX ||
          tolower(toSquare.at(0)) < X_MIN ||
          tolower(toSquare.at(0)) > X_MAX ||
          tolower(fromSquare.at(1)) < Y_MIN ||
          tolower(fromSquare.at(1)) > Y_MAX ||
          tolower(toSquare.at(1)) < Y_MIN ||
          tolower(toSquare.at(1)) > Y_MAX ||
          !(Board::getBoard()->squareAt(tolower(fromSquare.at(0)) - X_MIN, 
                                      tolower(fromSquare.at(1)) - Y_MIN)->occupied())
          )
    {
        cerr << "Niepoprawny ruch, sprobuj jeszcze raz" << endl;
        cin.clear();
        getline(cin, badInput); 
        cout << _name << " wprowadz ruch (np. a2 a4): ";
        cin >> fromSquare >> toSquare;
    }
    
    fromX = tolower(fromSquare.at(0)) - X_MIN;
    fromY = tolower(fromSquare.at(1)) - Y_MIN;
    toX = tolower(toSquare.at(0)) - X_MIN;
    toY = tolower(toSquare.at(1)) - Y_MIN;
    
    return Board::getBoard()->squareAt(fromX, fromY)->occupiedBy()->moveTo(*this, 
                                                                  *(Board::getBoard()->squareAt(toX, toY)));
}

bool Player::inCheck()
{
    bool check = false;
    

    for (set<Piece*>::iterator itr = Game::opponentOf(*this)->myPieces()->begin(); 
         itr != Game::opponentOf(*this)->myPieces()->end(); ++itr)
    {

        if (((Piece*)*itr)->location() && 
            ((Piece*)*itr)->canMoveTo(*(myKing()->location())))
        {
            check = true;
        }
    }
    
    return check;
}

void Player::capture(Piece* aPiece)
{
    aPiece->setLocation(NULL);
    
    _capturedPieces.insert(aPiece);
}

string Player::getName() const
{
    return _name;
}

bool Player::isWhite() const
{
    return _isWhite;
}

int Player::score() const
{
    int score = 0;
    
    for (set<Piece*>::iterator itr = _capturedPieces.begin(); itr != _capturedPieces.end(); ++itr)
    {
        score += ((Piece*)*itr)->value();
    }
    
    return score;
}

set<Piece*>* Player::myPieces() const
{
    return &_myPieces;
}

King* Player::myKing() const
{
    return &_myKing;
}