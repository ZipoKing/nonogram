/* 
 * File:   field.cpp
 * Author: pawel
 * 
 * Created on 5 kwiecieñ 2010, 16:32
 */

#include "field.h"

/**
 * Konstruktor
 */
Field::Field(int col, int row) : col(col), row(row)
{
    this->state = STATE_UNKNOWN;
    this->blocks.clear();
    this->row_blocks.clear();
    this->col_blocks.clear();
}

/**
 * Destruktor
 */
Field::~Field()
{
    this->blocks.clear();
    this->row_blocks.clear();
    this->col_blocks.clear();
}

bool Field::checkBlockExistence(std::vector<unsigned long> collection, unsigned long blockId)
{
    unsigned size = collection.size();
    for(unsigned i = 0; i < size; i++){
        if(collection[i] == blockId){
            return true;
        }
    }

    return false;
}

/**
 * Dodaj blok do listy zainteresowanych
 *
 * \param blockId ID bloku
 */
void Field::addBlock(unsigned long blockId)
{
    // Czy podany blok ju¿ znajduje siê na li¶cie?
    if(checkBlockExistence(blocks, blockId)){
        return;
    }

    blocks.push_back(blockId);
    return;
}

void Field::addColBlock(unsigned long blockId)
{
    // Czy podany blok ju¿ znajduje siê na li¶cie?
    if(checkBlockExistence(col_blocks, blockId)){
        return;
    }

    col_blocks.push_back(blockId);
}

void Field::addRowBlock(unsigned long blockId)
{
    // Czy podany blok ju¿ znajduje siê na li¶cie?
    if(checkBlockExistence(row_blocks)){
        return;
    }
}

/**
 * Usuñ block z listy zainteresowanych
 *
 * \param blockId ID bloku
 */
void Field::removeBlock(unsigned long blockId)
{
    removeBlock(blocks, blockId);
    removeBlock(row_blocks, blockId);
    removeBlock(col_blocks, blockId);

    return;
}

void Field::removeBlock(std::vector<unsigned long> collection, unsigned long blockId)
{
    // Odszukujemy blok i usuwamy go
    std::vector<unsigned long>::iterator iter;
    for(iter = collection.begin(); iter < collection.end(); iter++){
        if(*iter == blockId){
            collection.erase(iter);
        }
    }

    return;
}

std::vector<unsigned long> Field::getBlocks() const
{
    return blocks;
}

void Field::setState(int state)
{
    this->state = state;

    // TODO: nowy event
}

int Field::getState() const
{
    return state;
}
