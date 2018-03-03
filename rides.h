#ifndef RIDES_H_INCLUDED
#define RIDES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

typedef struct Car Car;

class Rides
{
    public :

        Rides();
        Rides(int a, int b, int x, int y, int e, int f, int i);
        Rides& operator=(const Rides& b);
        void update(int a, int b, int x, int y, int e, int f, int i);
        void afficher();
    private :

        int m_distance;
        int m_tempsTrajet;
        int m_retardPossible;
        int m_a;
        int m_b;
        int m_x;
        int m_y;
        int m_earliest;
        int m_finish;
        int m_i;
        int m_lastStart;

    friend void sortRides(std::vector<Rides>& Tab, int debut, int fin);
    friend void echanger(std::vector<Rides>& tableau, int a, int b);
    friend std::vector< std::vector<Rides> > pathFinding(std::vector<Rides> tabRides, int limTemps);
    friend int **carFinder(std::vector< std::vector<Rides> > paths, int nbCar);
    friend Car;
    friend std::vector< std::vector<Rides> > pathFinding(std::vector<Rides> tabRides, int limTemps, int rides);

};


    typedef struct Car
    {
      int m_x;
      int m_y;
      int m_time;
      int timeToArrive(Rides ride);
      void update(Rides ride);
    };

#endif // RIDES_H_INCLUDED
