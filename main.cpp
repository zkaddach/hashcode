#include "rides.h"

using namespace std;

int main()
{
    string adr_file = "a_example.in";
    ifstream file(adr_file.c_str());

    //Loading header
    int rows, cols, vehicles, rides, bonus, steps;
    file >> rows >> cols >> vehicles >> rides >> bonus >> steps;

    //Loading Rides
    vector<Rides> array_rides;
    int a, b, x, y, e, f;
    Rides newR(0,0,0,0,0,0,0);
    for (int i = 0; i < rides ; i++)
    {

        file >> a >> b >> x >> y >> e >> f ;
        newR.update(a,b,x,y,e,f,i);
        array_rides.push_back(newR);
    }
    for (int i = 0; i < rides ; i++)
    array_rides[i].afficher();
    Rides newR2(0,0,0,0,0,0,0);
    newR2 = array_rides[0];
    newR2.afficher();

    return 0;
}
