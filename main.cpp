#include "rides.h"
using namespace std;


int main()
{
    string adr_file = "d_metropolis.in";
    ifstream file(adr_file.c_str());

    //Loading header
    int rows(0), cols(0), vehicles(0), rides(0), bonus(0), steps(0);
    file >> rows >> cols >> vehicles >> rides >> bonus >> steps;

    //Loading Rides
    vector<Rides> array_rides;
    int a(0), b(0), x(0), y(0), e(0), f(0);

    Rides newR(0,0,0,0,0,0,0);

    for (int i = 0; i < rides ; i++)
    {
        file >> a >> b >> x >> y >> e >> f ;
        newR.update(a,b,x,y,e,f,i);
        array_rides.push_back(newR);
    }

    /*for (int i = 0; i < rides ; i++)
        array_rides[i].afficher();*/
    Rides newR2(0,0,0,0,0,0,0);
    newR2 = array_rides[0];
    //sortRides(array_rides, 0 , rides-1);
    cout << endl;
    for (int i = 0; i < 100 ; i++)
        array_rides[i].afficher();

    pathFinding(array_rides, 2);

    return 0;
}

