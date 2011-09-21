/* 
 * File:   line.h
 * Author: pawel
 *
 * Created on 11 kwiecie� 2010, 21:06
 */

#ifndef _LINE_H
#define	_LINE_H

#include <vector>
#include "block.h"

class Line
{
private:
    int line_index;
    unsigned line_width;
    std::vector<Block *> blocks;

public:
    /**
     * Konstruktor
     *
     * \param lineIndex Indeks linii (dodatnie - wiersz, ujemne - kolumna)
     * \param lineWidth D�ugo�� linii
     */
    Line(int line_index, unsigned line_width);

    /**
     * Destruktor
     */
    virtual ~Line();

    /**
     * Dodaj blok do listy
     *
     * \param block Blok do dodania
     */
    void addBlock(Block *block);

    /**
     * Oblicz granice w jakich poszczeg�lne bloki mog� operowa�
     */
    void calculateBlockBorders();

    /**
     * Zbadaj poszczeg�lne bloki odno�nie mo�liwo�ci zmiany status�w poszczeg�lnych
     * p�l na planszy
     */
    void checkBlocksForFixedFields();
};

#endif	/* _LINE_H */
