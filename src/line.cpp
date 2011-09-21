/* 
 * File:   line.cpp
 * Author: pawel
 * 
 * Created on 11 kwiecieñ 2010, 21:06
 */

#include "global.h"
#include "line.h"

using namespace std;

Line::Line(int line_index, unsigned line_width) : line_index(line_index),
        line_width(line_width)
{
    /* NOP */
}

Line::~Line()
{
    // Usuwamy wszystkie bloki
    vector<Block *>::iterator iter;
    for(iter = blocks.begin(); iter < blocks.end();){
        delete *iter;
        iter = blocks.erase(iter);
    }
}

/**
 * Dodaj blok do listy
 *
 * \param block Blok do dodania
 */
void Line::addBlock(Block* block)
{
    blocks.push_back(block);
    return;
}

/**
 * Oblicz granice bloków, w ramach któryc poszczególne bloki mog± dzia³aæ
 */
void Line::calculateBlockBorders()
{
    unsigned idx;
    vector<Block *>::iterator left_iter;
    vector<Block *>::reverse_iterator right_iter;

    // Granice z lewej strony
    idx = 0;
    for(left_iter = blocks.begin(); left_iter != blocks.end(); left_iter++){
        //og("Blok " << (*left_iter)->getId() << " lewa " << idx);
        (*left_iter)->setLeftBoundary(idx);
        idx += (*left_iter)->getWidth() + 1;
    }
    
    // Granice z prawej strony
    idx = line_width - 1;
    for(right_iter = blocks.rbegin(); right_iter != blocks.rend(); right_iter++){
        //log("Blok " << (*right_iter)->getId() << " prawa " << idx);
        (*right_iter)->setRightBoundary(idx);
        idx -= ((*right_iter)->getWidth() + 1);

        // W tym momencie bloki mog± juz ustaliæ listê interesuj±cych pól
        (*right_iter)->initializeFieldStates();
    }

    return;
}

/**
 * Zbadaj poszczególne bloki odno¶nie mo¿liwo¶ci zmiany statusów poszczególnych
 * pól na planszy
 */
void Line::checkBlocksForFixedFields()
{
    // Liczba pól, w ramach których poszczególne pola mog± siê poruszaæ
    unsigned space_left = 0;
    vector<Block *>::iterator iter;

    for(iter = blocks.begin(); iter != blocks.end(); iter++){
        space_left += (*iter)->getWidth() + 1;
    }
    space_left -= 1;
    space_left = line_width - space_left;

    // Przeszukujemy bloki na okoliczno¶æ wystêpowania pe³nych pól
    for(iter = blocks.begin(); iter != blocks.end(); iter++){
        (*iter)->alignToAllowedSpace(space_left);
    }

    return;
}
