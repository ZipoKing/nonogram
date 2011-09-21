/* 
 * File:   application.h
 * Author: pawel
 *
 * Created on 11 kwiecieñ 2010, 21:21
 */

#ifndef _APPLICATION_H
#define	_APPLICATION_H

class Application
{
public:
    /**
     * Konstruktor
     */
    Application();

    /**
     * Destruktor
     */
    virtual ~Application();

    /**
     * Rozwi±¿ obrazek na podstawie danych podanych w pliku
     */
    void solveNonogram(char *filename);
};

#endif	/* _APPLICATION_H */
