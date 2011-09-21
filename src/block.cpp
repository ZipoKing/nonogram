/* 
 * File:   block.cpp
 * Author: pawel
 * 
 * Created on 5 kwiecie� 2010, 22:38
 */

#include "block.h"
#include "global.h"
#include "board.h"
#include "application.h"

// Inicjalizacja zmiennych statycznych
unsigned long Block::idCounter = 0L;
const int Block::STATE_INTERESTING = 0x00;
const int Block::STATE_NOT_INTERESTING = 0x01;
const int Block::STATE_FILLED_BY_ME = 0x02;

/**
 * Konstruktor
 */
Block::Block(unsigned width, int lineIndex, unsigned lineWidth) :
    width(width), lineIndex(lineIndex), lineWidth(lineWidth)
{
    id = Block::idCounter++;
    //log("Utworzono blok o id=" << id << " i d�ugo�ci " << width);
    
    // Inicjalizacja wektora stan�w
    states.clear();
    for(unsigned i = 0; i < lineWidth; i++){
        states.push_back(STATE_NOT_INTERESTING);
    }
}

/**
 * Destruktor
 */
Block::~Block()
{
    states.clear();
}

/**
 * Pobierz ID bloku
 */
unsigned long Block::getId() const
{
    return id;
}

/**
 * Pobierz d�ugo�� bloku
 *
 * @return D�ugo�� bloku
 * @author pawel
 */
unsigned Block::getWidth() const
{
    return width;
}

/**
 * Pobierz lew� granic� zainteresowa�
 *
 * \return Lewa granica zainteresowa�
 */
unsigned Block::getLeftBoundary()
{
    return left_boundary;
}

/**
 * Ustaw lew� granic� zainteresowa�
 *
 * \param boundary Lewa granica zainteresowa�
 */
void Block::setLeftBoundary(unsigned boundary)
{
    left_boundary = boundary;
    return;
}

/**
 * Pobierz praw� granic� zainteresowa�
 *
 * \return Prawa granica zainteresowa�
 */
unsigned Block::getRightBoundary()
{
    return right_boundary;
}

/**
 * Ustaw praw� granic� zainteresowa�
 *
 * \param boundary Prawa granica zainteresowa�
 */
void Block::setRightBoundary(unsigned boundary)
{
    right_boundary = boundary;
    return;
}

/**
 * Zainicjuj dane o polach b�d�cych obiektem zainteresowania
 */
void Block::initializeFieldStates()
{
    Board *board = Board::getInstance();

    for(unsigned i = left_boundary; i <= right_boundary; i++){
        states.at(i) = STATE_INTERESTING;
        board->getFieldByRef(lineIndex, i)->addBlock(id);
    }
    
    return;
}

/**
 * Pouzpe�niaj pola bior�c pod uwag� ograniczony zakres ruchu blok�w
 * 
 * \param Dozwolony zakres ruchu blok�w
 */
void Block::alignToAllowedSpace(unsigned space_left)
{
    if(width <= space_left){ // Nie ma mo�liwo�ci ustawienia �adnego bloku
        return;
    }

    Board *board = Board::getInstance();

    // Mamy interesuj�ce nas pola
    for(unsigned i = left_boundary + space_left; i <= right_boundary - space_left; i++){
        states.at(i) = STATE_FILLED_BY_ME;
        board->getFieldByRef(lineIndex, i)->setState(Field::STATE_FULL);
    }

    return;
}