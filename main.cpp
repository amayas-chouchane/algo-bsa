#include <iostream>
#include "algorithme.h"

#include <vector>


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    algorithme algo {10,10};
    vector <double> low , up ;
    low.resize(10,0.1);
    up.resize(10,0.9);

        algo.affichage(algo.genererPopulation(low,up));
    return 0;


}
