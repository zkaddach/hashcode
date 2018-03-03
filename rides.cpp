#include "rides.h"

using namespace std;

Rides::Rides() : m_a(0), m_b(0), m_x(0), m_y(0), m_earliest(0), m_finish(0), m_i(0), m_distance(0), m_tempsTrajet(0), m_retardPossible(0), m_lastStart(0)
{
}

Rides::Rides(int a, int b, int x, int y, int e, int f, int i) : m_a(a), m_b(b), m_x(x), m_y(y), m_earliest(e), m_finish(f), m_i(i)
{
    m_distance = fabs(a-x) + fabs (b-y);
    m_tempsTrajet = f - e;
    m_retardPossible = m_tempsTrajet - m_distance;
    m_lastStart = e + m_retardPossible;
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
    m_lastStart = e + m_retardPossible;
}

void Rides::afficher()
{
    std::cout << m_a << " " << m_b << " " << m_x << " " << m_y << " " << m_earliest << " " << m_finish << " " << m_i << std::endl;
    std::cout << "Distance : " << m_distance << std::endl;
    std::cout << "Temps de trajet : " << m_tempsTrajet<< std::endl;
    std::cout << "Retard possible: " << m_retardPossible<< std::endl;
    std::cout << "Depart au plus tard: " << m_lastStart<< std::endl;

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
    m_lastStart = b.m_lastStart;
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
    const int pivot = Tab[debut].m_lastStart;

    if(debut >= fin)

        return;

    while(1)
    {
        do droite--; while(Tab[droite].m_lastStart > pivot);
        do gauche++; while(Tab[gauche].m_lastStart < pivot);

        if(gauche < droite)
            echanger(Tab, gauche, droite);

        else break;

    }
    sortRides(Tab, debut, droite);
    sortRides(Tab, droite+1, fin);

}

/*
vector< vector<Rides> > pathFinding(vector<Rides> tabRides, int limTemps)
{
    vector< vector<Rides> > path;
    vector<Rides> tabIndice;
    int finish(0), indice(0), distance(0), start(0), i(0), j(0), k(-1),compteur(0);
    bool cond(true);

    while (tabRides.size() != 0)
    {
        k++;
        j = 0;
        i = j;  // on se remet à la premiere rides non affectée

        while (cond)
        {
            compteur++;
            path.push_back(vector<Rides>(1));
            path[k][0] = tabRides[i];

            j= i+1;
            if (j > tabRides.size())
                cond = false;

            distance = fabs (tabRides[i].m_x - tabRides[j].m_a)  + fabs (tabRides[i].m_y - tabRides[j].m_b);
            finish = tabRides[i].m_finish;
            indice = tabRides[i].m_i;
            start = tabRides[j].m_lastStart;

            if((finish + distance <= start) && (finish - start <= limTemps) )
            {
                path[k][compteur] = tabRides[j];
            }
            else if ((finish - start <= limTemps ) )
            {
                tabRides.erase( (iterator)i );
                cond = false;
            }
            else
            {

            }
        }
        compteur = 0;

    }
    /*
    for(int i = 0; i < tabRides.size() - 1; i++)
    {
        earliest = tabRides[i].m_earliest;
        finish = tabRides[i].m_finish;
        indice = tabRides[i].m_i;


    }

    return path;
<<<<<<< HEAD
}

int **carFinder(std::vector< std::vector<Rides> > paths)
{

}
=======
}*/
>>>>>>> 6f0acb6d4dbe87914f05eacd409962442e7a58d8
