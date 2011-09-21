/* 
 * File:   global.h
 * Author: pawel
 *
 * Created on 3 kwiecie� 2010, 09:18
 */

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <iostream>

/*
 * W trybie debugowania uruchamiamy logowanie komunikat�w na konsol�
 */
#ifdef DEBUG
    #define log(a) std::cout << a << std::endl
#else /* DEBUG not defined */
    #define log(a)
#endif /* DEBUG defined */

/*
 * Za ka�dym razem gdy usuwamy obiekt musimy wyzerowa� wska�nik
 */
#define SMART_DELETE(a) if(a != NULL){delete a; a = NULL;}
#define SMART_DELETE_TAB(a) if(a != NULL){delete[] a; a = NULL;}

/*
 * Kilka po�ytecznych sta�ych
 */
static const int MAX_LINE_COUNT = 100; ///< Maksymalna liczba wierszy/kolumn
static const int MAX_BLOCK_COUNT = 50; ///< Maksymalna liczba blok�w w linii

#endif /* _GLOBAL_H */
