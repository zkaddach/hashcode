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
/*
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


            if((finish + distance < start) && (finish - start <= limTemps) )
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

/*
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

/*
void sortPath(vector< vector<Rides> > path)
{
    int taille = path.size();

}*/


vector< vector<Rides> > pathFinding(vector<Rides> tabRides, int limTemps, int rides)
{
    sortRides(tabRides, 0 , rides-1);
    vector< vector<Rides> > paths;
    int id_paths(0), id_rides(0), past_time(0);
    Rides head;
    while(tabRides.size() > 0)
    {
        id_rides = 0; //New path
        paths.push_back(vector <Rides>(1));
        paths[id_paths][0] = tabRides[0];
        head = tabRides[0];
        tabRides.erase(tabRides.begin());
        past_time = head.m_a + head.m_b;
        for(int i = 0; i < tabRides.size(); i++)
        {
            past_time += head.m_distance;
            if(inInterval(head.m_finish+distanceRides(head,tabRides[i]), tabRides[i].m_earliest, tabRides[i].m_lastStart))
            {
                id_rides++;
                if(id_rides == 0)
                    paths[id_paths][id_rides] = tabRides[i];
                else
                    paths[id_paths].push_back(tabRides[i]);
                head = tabRides[i];
                tabRides.erase(tabRides.begin() + i);
                i = 0;
                past_time += distanceRides(head,tabRides[i]);
            }
            else if(inInterval(past_time+distanceRides(head,tabRides[i]), tabRides[i].m_earliest, tabRides[i].m_lastStart))
            {
                id_rides++;
                if(id_rides == 0)
                    paths[id_paths][id_rides] = tabRides[i];
                else
                    paths[id_paths].push_back(tabRides[i]);
                head = tabRides[i];
                tabRides.erase(tabRides.begin() + i);
                i = 0;
                past_time += distanceRides(head,tabRides[i]);
            }

        }
        id_paths++;
    }
    return paths;
}


vector <vector <int> > carFinder(std::vector< std::vector<Rides> > paths, int nbCar)
{
    vector <vector <int> > results;
    vector <Rides> notAffected;
    vector <int> notAffected2;
    //Car definition
    Car cars[nbCar];
    for(int i = 0; i < nbCar; i++)
    {
        cars[i].m_x = 0;
        cars[i].m_y = 0;
        cars[i].m_time = 0;
    }

    //Association
    int posInPaths(0), posInCars(0),compteur(0);
    for(int i = 0; i < nbCar; i++)
        results.push_back(vector <int>(1));

        while(posInPaths < paths.size())
        {
            if(cars[posInCars].arriveOnTime(paths[posInPaths][compteur]))
            {

                results[posInCars][0] = (paths[posInPaths].size() - compteur);

                for(int j = compteur; j < paths[posInPaths].size(); j++)
                {
                    results[posInCars].push_back(paths[posInPaths][j].m_i);
                }
                cars[posInCars].update(paths[posInPaths][paths[posInPaths].size()-1]);
                posInCars++;
                posInPaths++;
                if(compteur != 0)
                {
                        notAffected.push_back(paths[posInPaths][0]);
                        notAffected2.push_back(compteur);
                }
            }
            else if (compteur < paths[posInPaths].size())
            {

                compteur++;
            }
            else
            {
                notAffected.push_back(paths[posInPaths][0]);
                notAffected2.push_back(0);
                posInPaths++;
                compteur = 0;
            }

        }
        for(int i = 0 ; i < notAffected.size();i++)
        {
            notAffected[i].afficher();
            cout << endl;
        }
        cout << notAffected.size() << endl<<endl;



//Not Affectation association
/*
    int posInNotAffected(0);
    for(posInCars = 0, posInCars < nbCar; posInCars++)
    {
        if(cars[posInCars].arriveOnTime(notAffected[posInNotAffected]))
        {
            results[posInCars].push_back(notAffected[posInNotAffected][j].m_i);
            cars[posInCars].update(notAffected[posInNotAffected][j]);
            posInNotAffected++;
        }

    }
*/
    //Printing results
/*
    for(int i = 0; i < nbCar; i++)
    {
        if(results.size() > 0 && results[i].size() > 0)
        {
            for(int j = 0; j < results[i].size(); j++)
            cout << results[i][j] << " " ;
        }
        cout << endl;
    }*/

    return results;
}


bool Car::arriveOnTime(Rides ride)
{
    return (fabs(m_x-ride.m_a) + fabs(m_y-ride.m_b)) + m_time < ride.m_lastStart-1;
}

void Car::update(Rides ride)
{
    m_x = ride.m_x;
    m_y = ride.m_y;
    m_time = ride.m_finish;
}

bool inInterval (int x, int a, int z)
{
    return (x >= a && x < z);
}

int distanceRides (Rides a, Rides b)
{
    return fabs(b.m_a - a.m_x) + fabs(b.m_b-a.m_y);
}
