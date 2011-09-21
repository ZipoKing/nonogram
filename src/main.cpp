/*
 * File:   main.cpp
 * Author: pawel
 *
 * Created on 3 kwiecieñ 2010, 09:22
 */

#include "global.h"
#include "application.h"

/**
 * Punkt startu programu
 *
 * \param argc Liczba argumentów
 * \param argv Tablica argumentów
 */
int main(int argc, char **argv)
{
    if(argc != 2){
        std::cerr << "Nieprawid³owa liczba argumentów" << std::endl;
        return -1;
    }

    Application app = Application();
    app.solveNonogram(argv[1]);

    return 0;
}
