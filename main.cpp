#include <iostream>
#include <vector>
#include <limits> // Pour numeric_limits
#include "./include/Solution.h" // Inclure vos fichiers d'en-t�te
#include "./include/algorithme.h"

using namespace std;

int main() {
    // Variables pour les donn�es utilisateur
    int dim, func_id;
    int pop_size, epoch, nb_runs;
    double mixRate;
    vector<double> low, up;



    // Demander les donn�es pour l'objet algorithme
    cout << "\n=== Initialisation de la classe algorithme ===" << endl;
    cout << "Entrez la taille de la population (pop_size) : ";
    cin >> pop_size;
    cout << "Entrez la dimension (dim) : ";
    cin >> dim;

    cout << "Entrez le nombre d'epochs (epoch) : ";
    cin >> epoch;

    cout << "Entrez le nombre de runs (nb_runs) : ";
    cin >> nb_runs;

    cout << "Entrez le taux de m�lange (mixRate) : ";
    cin >> mixRate;

    cout << "Entrez les limites inf�rieures pour chaque dimension (s�par�es par des espaces, longueur = " << dim << ") : ";
    double vallow ;
    cin>>vallow;
    low.resize(dim,vallow);


    cout << "Entrez les limites sup�rieures pour chaque dimension (s�par�es par des espaces, longueur = " << dim << ") : ";
    double valup;
    cin>>valup;
     up.resize(dim,valup);


    cout << "choisisez la fonction Objectif a executer : " << endl;
	cout << "	1 - Rosenbrock" << endl<< "	2 - Rastragin" << endl	<< "        3 - Ackley" << endl
     << "	4 - Schwefel" << endl;

    cout << "Entrez l'ID de la fonction (func_id) : ";
    cin >> func_id;
       // Cr�ation de l'objet Solution
    Solution sol(dim, func_id);

    // Cr�ation de l'objet algorithme
    algorithme algo(sol, pop_size, dim, epoch, nb_runs, mixRate, low, up);


    algo.bsa();


    return 0;
}
