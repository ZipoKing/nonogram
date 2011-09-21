/*
 * File:   main.cpp
 * Author: pawel
 *
 * Created on 3 kwiecie� 2010, 09:22
 */

#include "global.h"
#include "application.h"

/**
 * Punkt startu programu
 *
 * \param argc Liczba argument�w
 * \param argv Tablica argument�w
 */
int main(int argc, char **argv)
{
    if(argc != 2){
        std::cerr << "Nieprawid�owa liczba argument�w" << std::endl;
        return -1;
    }

    Application app = Application();
    app.solveNonogram(argv[1]);

    return 0;
}
