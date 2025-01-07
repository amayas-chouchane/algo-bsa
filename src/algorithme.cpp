#include "../include/algorithme.h"
#include "../solution.h"
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <algorithm>
#include <random>

using namespace std;


algorithme::algorithme(int popsize, int dim, int func_id)
    : pop_size(popsize), dim(dim), globalMinimizer(dim), globalMin(numeric_limits<double>::infinity()), func_id(func_id)
{
}

algorithme::~algorithme()
{
}

std::vector<std::vector<double>> algorithme::genererPopulation(std::vector<double> low, std::vector<double> up)
{
    std::vector<std::vector<double>> pop(pop_size, std::vector<double>(dim));
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            pop[i][j] = (static_cast<double>(std::rand()) / RAND_MAX) * (up[j] - low[j]) + low[j];
        }
    }
    return pop;
}

double algorithme::randn()
{
    static std::default_random_engine generator(std::random_device{}());
    static std::normal_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}
// Méthode pour définir les bornes de la population
void algorithme::setLowUpLimits(std::vector<double> low, std::vector<double> up)
{
    this->low = low;
    this->up = up;
}

double algorithme::min(const vector<double>& vec, int& indexMin)
{
    double valeurMin = vec[0];
    indexMin = 0;

    for (int i = 0; i < vec.size(); ++i)
    {
        if (vec[i] < valeurMin)
        {
            valeurMin = vec[i];
            indexMin = i;
        }
    }

    return valeurMin;
}

void algorithme::affichage(const std::vector<std::vector<double>>& tab)
{
    for (int i = 0; i < pop_size; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }
}

double algorithme::ObjFun(const std::vector<double>& pop)
{
    Solution sol(dim, func_id); // Utilisation de func_id pour choisir la fonction objectif
    sol.fitness(pop);
    return sol.getFitness();
}

void algorithme::bsa()
{
    vector<vector<double>> P(pop_size, vector<double>(dim));
    vector<vector<double>> OldP(pop_size, vector<double>(dim));
    vector<vector<double>> mutant(pop_size, vector<double>(dim));
    vector<vector<double>> map(pop_size, vector<double>(dim));
    vector<vector<double>> T(pop_size, vector<double>(dim));
    vector<double> fitnessP(pop_size);
    vector<double> fitnessT(pop_size);
    vector<double> low(dim, -5.0); // Exemple de borne basse
    vector<double> up(dim, 5.0);   // Exemple de borne haute

    // Générer une population initiale
    P = genererPopulation(low, up);

    // Calculer les fitness pour la population P
    for (int i = 0; i < pop_size; i++)
    {
        fitnessP[i] = ObjFun(P[i]);
    }

    OldP = genererPopulation(low, up);

    // Répéter pour les itérations spécifiées
    for (int k = 0; k < epoch; k++)
    {
        for (int i = 0; i < pop_size; i++)
        {
            double a = rand() / (RAND_MAX + 1.0);
            double b = rand() / (RAND_MAX + 1.0);
            if (a < b)
            {
                for (int j = 0; j < dim; j++)
                {
                    OldP[i][j] = P[i][j];
                }
            }
        }

        for (int i = 0; i < pop_size; i++)
        {
            std::random_device grain;
            std::mt19937 generateur(grain());
            shuffle(OldP[i].begin(), OldP[i].end(), generateur);
        }

        // Mutation
        for (int i = 0; i < pop_size; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                mutant[i][j] = P[i][j] + 3 * randn() * (OldP[i][j] - P[i][j]);
            }
        }

        // Crossover (mélange de population)
        for (int i = 0; i < pop_size; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                map[i][j] = 1;
            }
        }

        // Test de croisement
        double c = rand() / (RAND_MAX + 1.0);
        double d = rand() / (RAND_MAX + 1.0);
        if (c < d)
        {
            std::vector<int> u(dim);
            for (int j = 0; j < dim; ++j)
            {
                u[j] = j;
            }
            for (int i = 0; i < pop_size; i++)
            {
                std::random_shuffle(u.begin(), u.end());
                int temp = static_cast<int>(std::ceil(0.8 * dim * rand())); // mixRate est 0.8 pour cet exemple
                for (int j = 1; j < temp; j++)
                {
                    map[i][u[j]] = 0;
                }
            }
        }
        else
        {
            for (int i = 0; i < pop_size; i++)
            {
                int randi = rand() % dim;
                map[i][randi] = 0;
            }
        }

        // Créer une population de test
        for (int i = 0; i < pop_size; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                T[i][j] = mutant[i][j];
            }
        }

        for (int i = 0; i < pop_size; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (map[i][j] == 1)
                {
                    T[i][j] = P[i][j];
                }
            }
        }

        // Contrôle des bornes
        for (int i = 0; i < pop_size; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                if (T[i][j] < low[j] || T[i][j] > up[j])
                {
                    T[i][j] = (static_cast<double>(std::rand()) / RAND_MAX) * (up[j] - low[j]) + low[j];
                }
            }
        }

        // Calculer les fitness pour la population de test
        for (int i = 0; i < pop_size; i++)
        {
            fitnessT[i] = ObjFun(T[i]);
        }

        // Sélection II (mettre à jour P si nécessaire)
        for (int i = 0; i < pop_size; i++)
        {
            if (fitnessT[i] < fitnessP[i])
            {
                fitnessP[i] = fitnessT[i];
                P[i] = T[i];
            }
        }

        // Mise à jour globale
        int indexMin;
        double fitnessPbest = min(fitnessP, indexMin);

        if (fitnessPbest < globalMin)
        {
            globalMin = fitnessPbest;
            for (int j = 0; j < dim; j++)
            {
                globalMinimizer[j] = P[indexMin][j];
            }
        }
    }
}
