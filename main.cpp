#include <iostream>
#include <vector>
#include "solution.h"
#include "include/algorithme.h"


using namespace std;
int main()
{
    int populationSize = 50;
    int dimensions = 30;
    int func_id = 1; // 1 pour Rosenbrock, 2 pour Rastrigin, etc.
    // Créer l'objet algorithme
    algorithme algo(populationSize, dimensions, func_id);

    // Définir les bornes de la population
    vector<double> low(dimensions, -5.0);  // Bornes inférieures
    vector<double> up(dimensions, 5.0);    // Bornes supérieures
    algo.setLowUpLimits(low, up);  // Appliquer les bornes

    // Lancer l'algorithme BSA
    algo.bsa();

    // Afficher les résultats
    cout << "Meilleur fitness : " << algo.getGlobalMin() << endl;
    cout << "Meilleur optimiseur : ";
    for (double val : algo.getGlobalMinimizer())
    {
        cout << val << " ";
    }
    cout << endl;


    return 0;

}

