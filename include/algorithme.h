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
    int epoch = 100; // Nombre d'itérations (modifiable)
    double globalMin;
    std::vector<double> globalMinimizer; // Meilleur résultat global
    int func_id; // Identifiant de la fonction objectif (1: Rosenbrock, 2: Rastrigin, etc.)
      std::vector<double> low;
    std::vector<double> up;

public:
    algorithme(int popsize, int dim, int func_id);  // Modification du constructeur
    ~algorithme();

    // Méthode pour générer une population aléatoire
    std::vector<std::vector<double>> genererPopulation(std::vector<double> low, std::vector<double> up);

    // Méthode pour calculer la valeur d'une fonction aléatoire
    double randn();

    // Méthode pour récupérer le minimum d'un tableau
    double min(const std::vector<double>& vec, int& indexMin);

    // Méthode d'affichage
    void affichage(const std::vector<std::vector<double>>& tab);

    // Fonction pour retourner une valeur d'objectif (fonction de test, peut être modifiée)
    double ObjFun(const std::vector<double>& pop);

    // BSA (C'est la méthode principale de l'algorithme d'optimisation)
    void bsa();

    // Accesseurs pour obtenir la valeur minimale globale
    double getGlobalMin() const { return globalMin; }
    const std::vector<double>& getGlobalMinimizer() const { return globalMinimizer; }

    // Setters pour les limites inférieure et supérieure si nécessaires
    void setLowUpLimits(std::vector<double> low, std::vector<double> up);
};


#endif
