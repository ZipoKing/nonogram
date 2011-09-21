/* 
 * File:   board.cpp
 * Author: pawel
 * 
 * Created on 11 kwiecie� 2010, 21:21
 */

#include "board.h"
#include "global.h"

using namespace std;

// Inicjalizacja zmiennych statycznych
Board *Board::instance = NULL;

/**
 * Konstruktor
 */
Board::Board(unsigned width, unsigned height) : width(width), height(height)
{
    log("Konstruktor planszy");
    
    // Zapisujemy wska�nik do planszy tak, aby mo�na by�o si� do niej
    // potem �atwo odwo�a�
    Board::instance = this;

    // Inicjujemy tablic� z polami
    fields = new Field **[width];
    for(unsigned i = 0; i < width; i++){
        fields[i] = new Field *[height];
        for(unsigned j = 0; j < height; j++){
            fields[i][j] = new Field(i, j);
        }
    }

    // Inicjujemy tablice wierszy i kolumn
    cols = new Line *[width];
    for(unsigned i = 0; i < width; i++){
        cols[i] = new Line(-((int) i), height);
    }

    rows = new Line *[height];
    for(unsigned i = 0; i < height; i++){
        rows[i] = new Line((int) i, width);
    }
}

/**
 * Destruktor
 */
Board::~Board()
{
    log("Destruktor planszy");
    
    // Lista blok�w nie jest nam ju� do niczego potrzebna
    blocks.clear();

    // Usuwamy tablice z wierszami/kolumnami
    for(unsigned i = height - 1; i >= 0 && i < height; i--){
        SMART_DELETE(rows[i]);
    }
    SMART_DELETE_TAB(rows);

    for(unsigned i = width - 1; i >= 0 && i < width; i--){
        SMART_DELETE(cols[i]);
    }
    SMART_DELETE_TAB(cols);

    // Usuwamy tablic� z polami
    for(unsigned i = width - 1; i >= 0 && i < width; i--){
        for(unsigned j = height - 1; j >= 0 && j < height; j--){
            SMART_DELETE(fields[i][j]);
        }
        SMART_DELETE_TAB(fields[i]);
    }
    SMART_DELETE_TAB(fields);

    Board::instance = NULL;
}

/**
 * Pobierz instancj� planszy
 */
Board *Board::getInstance()
{
    return Board::instance;
}

/**
 * Inicjalizacja danych planszy na podstawie podanych danych
 *
 * \param data Dane z d�ugo�ciami blok�w
 */
void Board::initialize(vector<int> data)
{
    int i, j;
    Block *b;
    vector<int>::iterator iter = data.begin();
    
    log("Inicjalizacja danych planszy");

    // TODO: suma d�ugo�ci blok�w nie mo�e by� wi�ksza od d�ugo�ci linii

    // W pierwszej kolejno�ci wczytujemy dane kolumn...
    for(i = 0; i < width; i++){
        //log("Wczytanie danych kolumny " << i);
        while(*iter != -1){
            b = new Block(*iter, -i, height);
            blocks.insert(make_pair(b->getId(), b));
            cols[i]->addBlock(b);
            iter++;
        }
        cols[i]->calculateBlockBorders();
        iter++;
    }

    // ...a nast�pnie wierszy
    for(i = 0; i < height; i++){
        //log("Wczytanie danych wiersza " << i);
        while(*iter != -1){
            b = new Block(*iter, i, width);
            blocks.insert(make_pair(b->getId(), b));
            rows[i]->addBlock(b);
            iter++;
        }
        rows[i]->calculateBlockBorders();
        iter++;
    }

    return;
}

/**
 * Pobierz obiekt pola o zadanych wsp�rz�dnych
 *
 * @param col Kolumna
 * @param row Wiersz
 * @return Obiekt pola
 */
Field *Board::getFieldAt(unsigned col, unsigned row) const
{
    return fields[col][row];
}

/**
 * Pobierz obiekt pola na podstawie indeksu linii oraz pozycji w niej
 *
 * @param lineIndex Indeks linii
 * @param pos Pozycja w linii
 * @return Obiekt pola
 */
Field *Board::getFieldByRef(int lineIndex, unsigned pos) const
{
    // Kolumny maj� ujemny indeks
    return lineIndex < 0 ?
        getFieldAt(-lineIndex, pos) : // Kolumna
        getFieldAt(pos, lineIndex); // Wiersz
}

void Board::draw()
{
    cout << endl << endl;

    // G�rna krawed�
    std::cout << "+";
    for(int i = 0; i < width; i++){
        cout << "-";
    }

    cout << "+" << endl;

    // Poszczeg�lne wiersze
    for(int i = 0; i < height; i++){
        cout << "|";
        for(int j = 0; j < width; j++){
            switch(fields[j][i]->getState()){
                case Field::STATE_EMPTY:
                    cout << " ";
                    break;
                case Field::STATE_FULL:
                    cout << "X";
                    break;
                default:
                    cout << fields[j][i]->getBlocks().size();
                    break;
            }
        }
        cout << "|" << endl;
    }

    // Dolna krawed�
    std::cout << "+";
    for(int i = 0; i < width; i++){
        cout << "-";
    }

    cout << "+" << endl;


    return;
}

/**
 * Dokonaj pierwszego kroku procesu rozwi�zania planszy
 */
void Board::firstSolveStep()
{
    // Dla ka�dego wiersza oraz ka�dej linii odnajdujemy pola,
    // kt�re z racji ograniczonego zakresu ruchu blok�w musz� by� zape�nione.
    for(int i = 0; i < height; i++){
        //log("Wiersz " << i);
        rows[i]->checkBlocksForFixedFields();
    }

    for(int i = 0; i < width; i++){
        //log("Kolumna " << i);
        cols[i]->checkBlocksForFixedFields();
    }

    return;
}
