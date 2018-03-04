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

// trie le tableau de rides dans l'ordre croissant par rapport à l'attribut m_lastStart

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

// construit les chemins les plus long entre les rides
vector< vector<Rides> > pathFinding(vector<Rides> tabRides, int limTemps, int rides)
{
    vector< vector<Rides> > path;
    int finish(0), indice(0), distance(0), start(0), i(0), j(0), k(-1);
    bool cond(true), cond2(true);

    sortRides(tabRides, 0 , rides-1);

    while (cond2 && (tabRides.size() >= 0))
    {
        k++;    // compteur de ligne
        i = 0; // on se remet à la premiere rides non affectée
        j = 1; // rides non effectuée suivante
        path.push_back(vector<Rides>(1)); // création d'une ligne
        path[k][0] = tabRides[i];  // on met le premier rides dans la k_iém ligne

        while (cond)
        {

            if (tabRides.size() == 2)   //si le tableau a une taille de 1
            {

                if (i == 0)
                    tabRides.erase(tabRides.begin());
                else
                    tabRides.erase(tabRides.begin() + i);

                cond = false;
                cond2 = false;
                break;
            }
            else if (j >= tabRides.size()) // si j est supérieur à la taille on arrête
            {

                if (i == 0)
                    tabRides.erase(tabRides.begin());
                else
                    tabRides.erase(tabRides.begin() + i);

                cond = false;
                break;
            }

            distance = fabs (tabRides[i].m_x - tabRides[j].m_a)  + fabs (tabRides[i].m_y - tabRides[j].m_b);
            finish = tabRides[i].m_finish;
            indice = tabRides[i].m_i;
            start = tabRides[j].m_lastStart;


            if((finish + distance <= start) && (finish - start <= limTemps) )
            {
                if (i == 0)
                    tabRides.erase(tabRides.begin());
                else
                    tabRides.erase(tabRides.begin() + i); //suppression de la course i de tabRides (déjà ajouté dans path)
                path[k].push_back(tabRides[j]);             // on ajoute la rides j à la suite de i dans path
                i = j;                                  // i toujours ajouté alors
                j++;
            }
            else if ((finish - start >= limTemps ) )
            {
                if (i == 0)
                    tabRides.erase(tabRides.begin());
                else
                    tabRides.erase(tabRides.begin() + i); //suppression de la course i de tabRides
                cond = false;
            }
            else
            {
                j++;
            }
        }

        cond = true;
    }


    for (int l = 0; l<= 2 ; l++)
    {
        cout << l <<"éme chemin \n\n";
        for (int h = 0; h <  path[l].size();h++)
        {
            path[l][h].afficher();
        }
        cout <<"\n\n\n";
    }

    return path;
}







vector <vector <int> > carFinder(std::vector< std::vector<Rides> > paths, int nbCar)
{
    int sizeOfPaths = paths.size();
    vector <vector <int> > results;

    //Car definition
    Car cars[nbCar];

    int posInPaths(0);
    for(posInPaths = 0; posInPaths < nbCar ; posInPaths++)
    {
        results.push_back(vector<int>(1));
        if(posInPaths < paths.size())
            results[posInPaths][0]= paths[posInPaths].size();
        else
            results[posInPaths][0]= 0;
    }
    posInPaths = 0;

    //First car association
    for(int i = 0; i < paths.size(); i++)
    {
        for(int j = 0; j < paths[i].size(); j++)
        {
            results[i].push_back(paths[i][j].m_i);
        }
        cout << endl;
    }


    //Printing results
    for(int i = 0; i < nbCar; i++)
    {
        for(int j = 0; j < results[i].size(); j++)
            cout << results[i][j] << " " ;
        cout << endl;
    }

    return results;
}


int Car::timeToArrive(Rides ride)
{
    return fabs(m_x-ride.m_a) + fabs(m_y-ride.m_b);
}

void Car::update(Rides ride)
{
    m_x = ride.m_x;
    m_y = ride.m_y;
    m_time = ride.m_finish;
}
