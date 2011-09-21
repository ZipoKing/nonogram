/* 
 * File:   block.h
 * Author: pawel
 *
 * Created on 5 kwiecie� 2010, 22:38
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
    unsigned lineWidth; ///< D�ugo�� linii
    unsigned width; ///< D�ugo�� bloku
    unsigned left_boundary; ///< Lewa granica zainteresowa� danego bloku
    unsigned right_boundary; ///< Prawa granica zainteresowa� danego bloku
    std::vector<int> states; ///< Stany zainteresowania odno�nie ilo�ci p�l

public:
    static const int STATE_NOT_INTERESTING; ///< Dane pole le�y poza obszarem zainteresowania
    static const int STATE_INTERESTING; ///< Dane pole le�y w obszarze zainteresowania
    static const int STATE_FILLED_BY_ME; ///< Dane pole jest pe�ne i nale�y do danego bloku
    /**
     * Konstruktor
     *
     * \param width D�ugo�� bloku
     * \param lineIndex indeks linii, w kt�rej znajduje si� dany blok
     * \param lineWidth d�ugo�� linii, w kt�rej znajduje si� dany blok
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
     * Pobierz d�ugo�� bloku
     *
     * \return D�ugo�� bloku
     */
    unsigned getWidth() const;

    /**
     * Pobierz lew� granic� zainteresowa�
     *
     * \return Lewa granica zainteresowa�
     */
    unsigned getLeftBoundary();

    /**
     * Ustaw lew� granic� zainteresowa�
     *
     * \param boundary Lewa granica zainteresowa�
     */
    void setLeftBoundary(unsigned boundary);

    /**
     * Pobierz praw� granic� zainteresowa�
     * 
     * \return Prawa granica zainteresowa�
     */
    unsigned getRightBoundary();
    
    /**
     * Ustaw praw� granic� zainteresowa�
     *
     * \param boundary Prawa granica zainteresowa�
     */
    void setRightBoundary(unsigned boundary);

    /**
     * Zainicjuj dane o polach b�d�cych obiektem zainteresowania
     */
    void initializeFieldStates();

    /**
     * Pouzpe�niaj pola bior�c pod uwag� ograniczony zakres ruchu blok�w
     *
     * \param Dozwolony zakres ruchu blok�w
     */
    void alignToAllowedSpace(unsigned space_left);

};

#endif	/* _BLOCK_H */
