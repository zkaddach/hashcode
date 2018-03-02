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
        Rides& operator=(const Rides& b);
        void update(int a, int b, int x, int y, int e, int f, int i);
        void afficher();
    private :

        int m_distance;
        int m_a;
        int m_b;
        int m_x;
        int m_y;
        int m_earliest;
        int m_finish;
        int m_i;

    friend void sortRides(std::vector<Rides>& Tab, int debut, int fin);
    friend void echanger(std::vector<Rides>& tableau, int a, int b);
};


#endif // RIDES_H_INCLUDED
