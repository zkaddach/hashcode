#ifndef RIDES_H_INCLUDED
#define RIDES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

class Rides
{
    public :

        Rides(int a, int b, int x, int y, int e, int f, int i);
        void update(int a, int b, int x, int y, int e, int f, int i);
        void afficher();

        Rides& operator=(const Rides& b);
    private :

        int m_a;
        int m_b;
        int m_x;
        int m_y;
        int m_earliest;
        int m_finish;

        int m_distance;
        int m_i;
};



#endif // RIDES_H_INCLUDED
