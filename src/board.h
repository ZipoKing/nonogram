/* 
 * File:   board.h
 * Author: pawel
 *
 * Created on 11 kwiecieñ 2010, 21:21
 */

#ifndef _BOARD_H
#define	_BOARD_H

#include <map>
#include <vector>
#include "block.h"
#include "field.h"
#include "line.h"

class Board
{
private:
    static Board *instance; /// Instancja planszy
    unsigned width; ///< Szeroko¶æ planszy
    unsigned height; ///< Wysoko¶æ planszy
    std::map<unsigned, Block *> blocks; ///< Mapa opisuj±ca bloki na planszy
    Field ***fields; ///< Dwuwymiarowa tablica z polami
    Line **rows; ///< Lista wierszy
    Line **cols; ///< Lista kolumn

public:
    /**
     * Konstruktor
     *
     * \param width Szeroko¶æ planszy
     * \param height Wysoko¶æ planszy
     */
    Board(unsigned width, unsigned height);

    /**
     * Destruktor
     */
    virtual ~Board();

    /**
     * Pobierz instancjê planszy
     *
     * \return Instancja planszy
     */
    static Board *getInstance();

    /**
     * Zainicjuj dane planszy na podstawie podanych danych
     *
     * \param data Dane planszy
     */
    void initialize(std::vector<int> data);

    /**
     * Pobierz obiekt pola o zadanych wspó³rzêdnych
     *
     * @param col Kolumna
     * @param row Wiersz
     * @return Obiekt pola
     */
    Field *getFieldAt(unsigned col, unsigned row) const;

    /**
     * Pobierz obiekt pola na podstawie indeksu linii oraz pozycji w niej
     *
     * @param lineIndex Indeks linii
     * @param pos Pozycja pola w linii
     * @return Obiekt pola
     */
    Field *getFieldByRef(int lineIndex, unsigned pos) const;

    /**
     * Narysuj planszê na ekranie, uwzglêdniaj±c jej stan
     */
    void draw();

    /**
     * Dokonaj pierwszego kroku procesu rozwi±zania planszy
     */
    void firstSolveStep();
};

#endif	/* _BOARD_H */
