#include <string>
#include "piece.h"
#include "player.h"

Piece::Piece(bool isWhite) : _isWhite(isWhite), _square(NULL)
{
    if(isWhite)
        _color = "B";
    else
        _color = "C";
}

Piece::~Piece()
{
}

bool Piece::moveTo(Player& byPlayer, Square& toSquare)
{
    bool validMove = false;
    Piece* toCapture = NULL;
    Square* fromSquare = _square;
    
    if(_isWhite == byPlayer.isWhite())
    {
        if(canMoveTo(toSquare))
        {
            if(toSquare.occupied())
            {
                toCapture = toSquare.occupiedBy();
                
                if(toCapture->isWhite() != byPlayer.isWhite())
                {
                    validMove = true;
                }
            }
            else 
            {
                validMove = true;
            }

            if(validMove)
            {

                if(toCapture)
                {
                    toCapture->setLocation(NULL);
                } 
                

                _square->setOccupier(NULL);

                _square = &toSquare;

                _square->setOccupier(this);

                if(byPlayer.inCheck())
                {

                    validMove = false;
                    

                    _square = fromSquare;
                    

                    _square->setOccupier(this);
                    

                    toSquare.setOccupier(toCapture);
                    

                    if(toCapture)
                    {
                        toCapture->setLocation(&toSquare);
                    }
                }
                else 
                {

                    if(toCapture)
                    {
                        byPlayer.capture(toCapture);
                    } 
                }
            }
        }
    }
    
    return validMove;
}

void Piece::setLocation(Square* location)
{
    _square = location;
}

bool Piece::isWhite() const
{
    return _isWhite;
}

string Piece::color() const
{
    return _color;
}

bool Piece::isOnSquare() const
{
    return _square;
}

Square* Piece::location() const
{
    return _square;
}

