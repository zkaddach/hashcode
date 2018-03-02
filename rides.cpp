#include "rides.h"

using namespace std;

Rides::Rides(int a, int b, int x, int y, int e, int f, int i) : m_a(a), m_b(b), m_x(x), m_y(y), m_earliest(e), m_finish(f), m_i(i)
{
    m_distance = fabs(a-x) + fabs (b-y);
    m_tempsTrajet = f - e;
    m_retardPossible = m_tempsTrajet - m_distance;
}

void Rides::update(int a, int b, int x, int y, int e, int f, int i)
{
    m_a = a;
    m_b = b;
    m_x = x;
    m_y = y;
    m_earliest = e;
    m_finish = f;
    m_i = i;
    m_distance = fabs(a-x) + fabs (b-y);
    m_tempsTrajet = f - e;
    m_retardPossible = m_tempsTrajet - m_distance;
}

void Rides::afficher()
{
    std::cout << m_a << " " << m_b << " " << m_x << " " << m_y << " " << m_earliest << " " << m_finish << " " << m_i << std::endl;
    std::cout << "Distance : " << m_distance << std::endl;
    std::cout << "Temps de trajet : " << m_tempsTrajet<< std::endl;
    std::cout << "Retard possible: " << m_retardPossible<< std::endl;
}

Rides& Rides::operator=(const Rides& b)
{
    m_a = b.m_a;
    m_b = b.m_b;
    m_distance = b.m_distance;
    m_earliest = b.m_earliest;
    m_finish = b.m_finish;
    m_i = b.m_i;
    m_x = b.m_x;
    m_y = b.m_y;
    m_tempsTrajet = b.m_tempsTrajet;
    m_retardPossible = b.m_retardPossible;
    return *this;
}





void echanger(vector<Rides>& tableau, int a, int b)
{
  Rides tmp(0,0,0,0,0,0,0);
  tmp = tableau[a];
  tableau[a] = tableau[b];
  tableau[b]= tmp;
}


void sortRides(vector<Rides>& Tab, int debut, int fin)
{
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = Tab[debut].m_earliest;

    if(debut >= fin)

        return;

    while(1)
    {
        do droite--; while(Tab[droite].m_earliest > pivot);
        do gauche++; while(Tab[gauche].m_earliest < pivot);

        if(gauche < droite)
            echanger(Tab, gauche, droite);

        else break;

    }
    sortRides(Tab, debut, droite);

    sortRides(Tab, droite+1, fin);

}


//Rides r(b.m_a,b.m_b,b.m_x, b.m_y, b.m_earliest, b.m_finish, b.m_i);
