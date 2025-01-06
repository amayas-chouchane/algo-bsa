
#include <iostream>

#include <vector>


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
   // algorithme algo {10,10};
    vector <double> low, up ;
    low.resize(10,0.1);
    up.resize(10,0.9);

    //algo.affichage(algo.genererPopulation(low,up));


    /*
    double crossoverRate = 0.8; // Exemple : Taux de crossover
        for (int i = 0; i < pop_size; ++i) {
            for (int j = 0; j < dim; ++j) {
                double r = static_cast<double>(rand()) / RAND_MAX;
                if (r < crossoverRate) {
                    T[i][j] = mutant[i][j]; // Prendre le gène de mutant
                } else {
                    T[i][j] = P[i][j]; // Garder le gène de P
                }
            }
        }
    */
    return 0;


}

