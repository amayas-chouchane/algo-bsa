#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "../solution.h"
#include <vector>
#include <limits>
#include <random>
#include <algorithm>

class algorithme
{
private:
    int pop_size; // Taille de la population
    int dim; // Dimension des solutions
    int epoch = 100; // Nombre d'it�rations (modifiable)
    double globalMin;
    std::vector<double> globalMinimizer; // Meilleur r�sultat global
    int func_id; // Identifiant de la fonction objectif (1: Rosenbrock, 2: Rastrigin, etc.)
      std::vector<double> low;
    std::vector<double> up;

public:
    algorithme(int popsize, int dim, int func_id);  // Modification du constructeur
    ~algorithme();

    // M�thode pour g�n�rer une population al�atoire
    std::vector<std::vector<double>> genererPopulation(std::vector<double> low, std::vector<double> up);

    // M�thode pour calculer la valeur d'une fonction al�atoire
    double randn();

    // M�thode pour r�cup�rer le minimum d'un tableau
    double min(const std::vector<double>& vec, int& indexMin);

    // M�thode d'affichage
    void affichage(const std::vector<std::vector<double>>& tab);

    // Fonction pour retourner une valeur d'objectif (fonction de test, peut �tre modifi�e)
    double ObjFun(const std::vector<double>& pop);

    // BSA (C'est la m�thode principale de l'algorithme d'optimisation)
    void bsa();

    // Accesseurs pour obtenir la valeur minimale globale
    double getGlobalMin() const { return globalMin; }
    const std::vector<double>& getGlobalMinimizer() const { return globalMinimizer; }

    // Setters pour les limites inf�rieure et sup�rieure si n�cessaires
    void setLowUpLimits(std::vector<double> low, std::vector<double> up);
};


#endif
