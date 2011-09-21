/* 
 * File:   application.cpp
 * Author: pawel
 * 
 * Created on 11 kwiecieñ 2010, 21:21
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "application.h"
#include "board.h"
#include "global.h"

using namespace std;

/**
 * Konstruktor
 */
Application::Application()
{
    /* NOP */
}

/**
 * Destruktor
 */
Application::~Application()
{
    delete Board::getInstance(); // usuwamy obiekt planszy
}

/**
 * Rozwi±¿ obrazek na podstawie danych podanych w pliku
 */
void Application::solveNonogram(char* filename)
{
    ifstream infile;
    int width, height; // Szeroko¶æ i wysoko¶æ planszy
    Board *board;
    
    log("Nazwa pliku wej¶ciowego: " << filename);

    //Na pocz±tek sprawdzamy, czy podany plik istnieje
    infile.open(filename, std::ifstream::in);
    infile.close();
    if(infile.fail()){
        cerr << "Plik nie istnieje: " << filename << endl;
        return;
    }

    // Plik istnieje, mo¿emy zacz±æ wczytywaæ dane
    infile.open(filename, ifstream::in);
    infile >> width;
    infile >> height;
    log("Wymiary planszy: " << width << "x" << height);

    if(width < 1 || width > MAX_LINE_COUNT || height < 1 || height > MAX_LINE_COUNT){
        cerr << "Nieprawid³owy rozmiar planszy" << endl;
        return;
    }

    // Wczytujemy listê opisuj±c± d³ugo¶ci poszczególnych bloków
    int count = width + height; // Tyle linii powinni¶my wczytaæ
    vector<int> sizes;
    int i;

    while(!infile.eof() && count > 0){
        infile >> i;
        sizes.push_back(i);
        if(i == -1){
            count--;
        }
    }

    // Na tym etapie mamy za³adowane wszelkie potrzebne dane z pliku wej¶ciowego
    infile.close();

    // Walidacja d³ugo¶ci bloków:
    // - ka¿da liczba musi byæ dodatnia
    // - suma d³ugo¶ci z wierszy musi zgadzaæ siê z odpowiedni± sum± z kolumn
    count = 0;
    int sum = 0;
    int factor = 1;
    vector<int>::iterator iter;

    for(iter = sizes.begin(); iter != sizes.end(); iter++){
        i = *iter;
        if(i <= 0 && i != -1){
            cerr << "Nieprawid³owa d³ugo¶æ bloku: " << i << endl;
            return;
        }
        if(i != -1){
            sum += i * factor;
        } else { // Przy przej¶ciu opisu wiersze -> kolumny factor zmieniamy na -1
            count++;
            if(count == width){
                factor = -1;
            }
        }
    }

    log("Suma: " << sum);

    if(sum != 0){
        std:cerr << "B£¡D: Nieprawid³owa definicja planszy!" << std::endl;
        SMART_DELETE(board);
        return;
    }

    board = new Board(width, height);
    board->initialize(sizes);

    board->draw();
    board->firstSolveStep();
    board->draw();

    SMART_DELETE(board);
    return;
}
