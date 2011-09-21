/* 
 * File:   block.h
 * Author: pawel
 *
 * Created on 5 kwiecieñ 2010, 22:38
 */

#ifndef _BLOCK_H
#define	_BLOCK_H

#include <vector>

class Block
{
private:
    unsigned long static idCounter;
    unsigned long id; ///< Identyfikator bloku
    int lineIndex; ///< Indeks wiersza (dodatnie) / kolumny (ujemne)
    unsigned lineWidth; ///< D³ugo¶æ linii
    unsigned width; ///< D³ugo¶æ bloku
    unsigned left_boundary; ///< Lewa granica zainteresowañ danego bloku
    unsigned right_boundary; ///< Prawa granica zainteresowañ danego bloku
    std::vector<int> states; ///< Stany zainteresowania odno¶nie ilo¶ci pól

public:
    static const int STATE_NOT_INTERESTING; ///< Dane pole le¿y poza obszarem zainteresowania
    static const int STATE_INTERESTING; ///< Dane pole le¿y w obszarze zainteresowania
    static const int STATE_FILLED_BY_ME; ///< Dane pole jest pe³ne i nale¿y do danego bloku
    /**
     * Konstruktor
     *
     * \param width D³ugo¶æ bloku
     * \param lineIndex indeks linii, w której znajduje siê dany blok
     * \param lineWidth d³ugo¶æ linii, w której znajduje siê dany blok
     */
    Block(unsigned width, int lineIndex, unsigned lineWidth);

    /**
     * Destruktor
     */
    virtual ~Block();

    /**
     * Pobierz ID bloku
     *
     * \return ID bloku
     */
    unsigned long getId() const;

    /**
     * Pobierz d³ugo¶æ bloku
     *
     * \return D³ugo¶æ bloku
     */
    unsigned getWidth() const;

    /**
     * Pobierz lew± granicê zainteresowañ
     *
     * \return Lewa granica zainteresowañ
     */
    unsigned getLeftBoundary();

    /**
     * Ustaw lew± granicê zainteresowañ
     *
     * \param boundary Lewa granica zainteresowañ
     */
    void setLeftBoundary(unsigned boundary);

    /**
     * Pobierz praw± granicê zainteresowañ
     * 
     * \return Prawa granica zainteresowañ
     */
    unsigned getRightBoundary();
    
    /**
     * Ustaw praw± granicê zainteresowañ
     *
     * \param boundary Prawa granica zainteresowañ
     */
    void setRightBoundary(unsigned boundary);

    /**
     * Zainicjuj dane o polach bêd±cych obiektem zainteresowania
     */
    void initializeFieldStates();

    /**
     * Pouzpe³niaj pola bior±c pod uwagê ograniczony zakres ruchu bloków
     *
     * \param Dozwolony zakres ruchu bloków
     */
    void alignToAllowedSpace(unsigned space_left);

};

#endif	/* _BLOCK_H */
