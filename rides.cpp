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
    for (int i = 0; i < rides ; i++)
        tabRides[i].afficher();

    while (cond2==true && (tabRides.size() != 0))
    {
        cout << "a\n";
        k++;    // compteur de ligne
        i = 0; // on se remet à la premiere rides non affectée
        j = 1; // rides non effectuée suivante
        path.push_back(vector<Rides>(1)); // création d'une ligne
        path[k][0] = tabRides[i];  // on met le premier rides dans la k_iém ligne

        cout << endl;
        path[k][0].afficher();

        while (cond)
        {
            cout << "\n\nb\n";

            if (tabRides.size() == 1)   //si le tableau a une taille de 1
            {
                cout<<"\n1er if\n";
                tabRides.erase(tabRides.begin() + i-1);
                cond = false;
                cond2 = false;
                break;
            }
            else if (j >= tabRides.size()) // si j est supérieur à la taille on arrête
            {
                cout<<"\n1er elseif\n";
                tabRides.erase(tabRides.begin() + i-1);
                cond = false;
                break;
            }

            distance = fabs (tabRides[i].m_x - tabRides[j].m_a)  + fabs (tabRides[i].m_y - tabRides[j].m_b);
            cout<<distance<<endl;
            finish = tabRides[i].m_finish;
            cout<<finish<<endl;
            indice = tabRides[i].m_i;
            cout<<indice<<endl;
            start = tabRides[j].m_lastStart;
            cout<<start<<endl;

            if((finish + distance <= start) && (finish - start <= limTemps) )
            {
                cout<<"\n2eme if\n";
                tabRides.erase(tabRides.begin() + i-1); //suppression de la course i de tabRides (déjà ajouté dans path)
                path[k].push_back(tabRides[j]);         // on ajoute la rides j à la suite de i dans path
                i = j;                                  // i toujours ajouté alors
                j++;
            }
            else if ((finish - start >= limTemps ) )
            {

                iterator m = i;
                tabRides.erase(m);

                cout<<"\n2eme elseif\n";
                tabRides.erase(tabRides.begin() + i-1); //suppression de la course i de tabRides

                cond = false;
            }
            else
            {
                cout<<"\n1er else\n";
                j++;
            }
        }

        compteur = 0;

    }

    for(int i = 0; i < tabRides.size() - 1; i++)
    {
        earliest = tabRides[i].m_earliest;
        finish = tabRides[i].m_finish;
        indice = tabRides[i].m_i;



        cout <<"path:\n";
        cout << tabRides.size();
        path[k][0].afficher();
        cond = true;

    }
    return path;


}


int **carFinder(std::vector< std::vector<Rides> > paths, int nbCar)
{
    int sizeOfPaths = paths.size();
    vector <vector <int> > results;
    //Car definition
    Car cars[nbCar];
    //First car association
    int i(0);
    for(i = 0; i < nbCar ; i++)
    {
        results.push_back(vector<int>(1));
        results[i][0]= i;
        for(int j = 0; j < paths[i].size(); j++)
            results[i][j] = paths[i][j].m_i;
        cars[i].update(paths[i][paths[i].size()]);
    }
/*
    for(int j = i + 1; j < sizeOfPaths; j++)
    {
        int k = 0;
        if(paths[j][0].m_lastStart < cars[k].timeToArrive(paths[j][0]))
        {
            cout << "le truc : " << paths[1][0].m_lastStart << endl;
        }
    }
    */
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
