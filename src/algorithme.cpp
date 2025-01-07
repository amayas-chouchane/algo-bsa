#include "algorithme.h"
#include <stdlib.h>
#include <iostream>
#include <limits> //pour numeric_limits (l'infini)
#include <algorithm> // Pour shuffle
#include <random>
using namespace std ;
algorithme::algorithme(int popsize, int dim): pop_size {popsize}, dim {dim}, globalMinimizer {dim}, globalMin {numeric_limits<double>::infinity()}
{
    //ctor
}

algorithme::~algorithme()
{
    //dtor
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
    // Générateur de nombres pseudo-aléatoires
    static std::default_random_engine generator(std::random_device{}());
    // Distribution normale standard N(0, 1)
    static std::normal_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
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

void algorithme :: affichage (const std::vector<std::vector<double>> &tab)
{

    for (int i=0 ; i< pop_size; i++ )
    {
        for (int j=0; j<dim; j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl ;
    }
}
double algorithme::ObjFun(const vector<double> &pop)
{
    return 0.1;
}
void algorithme::bsa ()
{
    //création des tableaux nécessaires
    vector<vector<double>> P(pop_size, vector<double>(dim));
    vector<vector<double>> OldP(pop_size, vector<double>(dim));
    vector<vector<double>> mutant(pop_size, vector<double>(dim));
    vector<vector<double>> map (pop_size, vector<double>(dim));
    vector<vector<double>> T(pop_size, vector<double>(dim));
    vector<double> fitnessP(pop_size);
    vector<double> fitnessT(pop_size);
    vector <double> low, up ;
    //initalisation de la population P
    P=genererPopulation(low,up);
    //calculer fitness de p
    for (int i=0 ; i<pop_size ; i++)
    {
        fitnessP[i]=ObjFun(P[i]);
    }
    //initalisation de la population OldP
    OldP=genererPopulation(low,up);

    //répéter jusqu'à nombre d'itérations atteint
    for (int k =0 ; k <epoch ; k++)
    {


        //sélection I
        for (int i=0 ; i< pop_size ; i++)
        {
            //générer des variables aléatoires entre 0.0 et 1.0
            double a = rand() / (RAND_MAX + 1.0);
            double b = rand() / (RAND_MAX + 1.0);
            if (a<b )
            {
                for (int j=0; j<dim ; j++)
                {
                    OldP[i][j]=P[i][j];
                }
            }
        }
        //permuation de OldP  avec la fonction shuffle
        for (int i=0 ; i< pop_size; i++)
        {

            // Création d'un générateur aléatoire
            std::random_device grain;  // Graine aléatoire
            std::mt19937 generateur(grain()); // Générateur Mersenne Twister

            // Mélanger le vecteur OldP
            shuffle(OldP[i].begin(), OldP[i].end(), generateur);
        }
        //mutation
        for (int i=0 ; i < pop_size ; i++)
        {
            for (int j=0; j < dim ; j++)
            {
                mutant [i][j] = P[i][j] +3*randn() * (OldP[i][j]-P[i][j]);
            }

        }
        //croissement
        for (int i=0 ; i < pop_size ; i++)
        {
            for (int j=0; j < dim ; j++)
            {
                map [i][j] = 1 ;
            }

        }

        //générer des variables aléatoires entre 0.0 et 1.0
        double c = rand() / (RAND_MAX + 1.0);
        double d = rand() / (RAND_MAX + 1.0);

        if ( c < d )
        {
            std::vector<int> u(dim);
            for (int j = 0; j < dim; ++j)
            {
                u[j] = j;
            }
            for (int i =0 ; i < pop_size ; i++)
            {
                std::random_shuffle(u.begin(), u.end());
                int temp = static_cast<int>(std::ceil(mixRate * dim * rand()));
                for (int j =1 ; j< temp ; j++)
                {
                    map[i][u[j]] = 0 ;
                }
            }


        }
        else
        {

            for (int i =0 ; i < pop_size ; i++)
            {
                int randi = rand() % dim ;
                map[i][randi]=0;
            }
        }


        // Generation of a trial population
        for (int i=0 ; i < pop_size ; i++)
        {
            for (int j=0; j < dim ; j++)
            {
                T [i][j] = mutant [i][j] ;
            }

        }

        for (int i=0 ; i < pop_size ; i++)
        {
            for (int j=0; j < dim ; j++)
            {
                if (map[i][j] == 1)
                {
                    T [i][j] = P [i][j] ;
                }
            }


        }

        //controle des bornes ( boundary control )

        for (int i=0 ; i < pop_size ; i++)
        {
            for (int j=0; j < dim ; j++)
            {
                if ( (T[i][j] < low [j]) ||  (T[i][j] > up [j]))
                {
                    T [i][j] =(static_cast<double>(std::rand()) / RAND_MAX) * (up[j] - low[j]) + low[j] ;
                }
            }


        }

        //sélection II
        for (int i=0 ; i<pop_size ; i++)
        {
            fitnessT[i]=ObjFun(T[i]);
        }

        for (int i=0 ; i<pop_size ; i++)
        {
            if ( fitnessT[i] < fitnessP[i])
            {
                fitnessP[i]=fitnessT[i];
                P[i]=T[i] ;
            }
        }
        int indexMin ;
        double fitnessPbest = min(fitnessP,indexMin);
        if (fitnessPbest< globalMin)
        {
            globalMin=fitnessPbest;
            for (int j =0 ; j< dim ; j++ )
            {
                globalMinimizer[j]=P[indexMin][j];
            }
        }
    }
}
