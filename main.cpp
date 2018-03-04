#include "rides.h"
using namespace std;


int main()
{
    string adr_file = "b_should_be_easy.in";
    ifstream file(adr_file.c_str());

    //Loading header
    int rows(0), cols(0), vehicles(0), rides(0), bonus(0), steps(0);
    file >> rows >> cols >> vehicles >> rides >> bonus >> steps;

    //Loading rides
    vector<Rides> array_rides;
    int a(0), b(0), x(0), y(0), e(0), f(0);

    Rides newR(0,0,0,0,0,0,0);

    for (int i = 0; i < rides ; i++)
    {
        file >> a >> b >> x >> y >> e >> f ;
        newR.update(a,b,x,y,e,f,i);
        array_rides.push_back(newR);
    }

    //Calling pathfinder
    std::vector< std::vector<Rides> > paths;
    paths = pathFinding(array_rides, 1500, rides);

    //Calling carFinder
    vector <vector<int> > results;
    //results = carFinder(paths, vehicles);

    //Printing in File
    ofstream output("results.txt");
    for(int i = 0; i < vehicles; i++)
    {
        for(int j = 0; j < results[i].size(); j++)
            output << results[i][j] << " ";
        output << endl;
    }

    return 0;
}

