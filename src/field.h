/* 
 * File:   field.h
 * Author: pawel
 *
 * Created on 5 kwiecieñ 2010, 16:32
 */

#ifndef _FIELD_H
#define	_FIELD_H

#include <vector>

class Field
{
private:
    int col; ///< Indeks kolumny
    int row; ///< Indeks wiersza
    int state;
    std::vector<unsigned long> blocks; ///< Lista potencjalnych bloków, które mog± byæ przypisane do pola
    std::vector<unsigned long> row_blocks; ///< Lista potencjalnych poziomych bloków, -*-
    std::vector<unsigned long> col_blocks; ///< Lista potencjalnych pionowych bloków, -*-

    bool checkBlockExistence(std::vector<unsigned long> collection, unsigned long blockId);
    void removeBlock(std::vector<unsigned long> collection, unsigned long blockId);

public:
    static const int STATE_UNKNOWN = 0; ///< Stan pola nieznany
    static const int STATE_EMPTY = 1; ///< Pole oznaczone jako puste
    static const int STATE_FULL = 2; ///< Pole oznaczone jako pe³ne

    /**
     * Konstruktor
     *
     * \param col Indeks kolumny
     * \param row Indeks wiersza
     */
    Field(int col, int row);

    /**
     * Destruktor
     */
    virtual ~Field();

    void addBlock(unsigned long blockId);

    void addRowBlock(unsigned long blockId);

    void addColBlock(unsigned long blockId);

    void removeBlock(unsigned long blockId);

    std::vector<unsigned long> getBlocks() const;

    void setState(int state);

    int getState() const;
};

#endif	/* _FIELD_H */
