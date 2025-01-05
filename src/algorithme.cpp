#include "algorithme.h"
#include <stdlib.h>
#include <iostream>
#include <limits> //pour numeric_limits (l'infini)
using namespace std ;
algorithme::algorithme(int popsize , int dim): pop_size {popsize} , dim {dim} , globalMinimizer {dim} , globalMin {numeric_limits<double>::infinity()}
{
    //ctor
}

algorithme::~algorithme()
{
    //dtor
}

std::vector<std::vector<double>> algorithme::genererPopulation(std::vector<double> low, std::vector<double> up) {
    std::vector<std::vector<double>> pop(pop_size, std::vector<double>(dim));
    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < dim; j++) {
          pop[i][j] = (static_cast<double>(std::rand()) / RAND_MAX) * (up[j] - low[j]) + low[j];
    }
    }
    return pop;
}

void algorithme :: affichage (const std::vector<std::vector<double>> &tab)
{

    for (int i=0 ; i< tab.size();i++ )
        {for (int j=0; j<tab[i].size(); j++){
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
{   //création des tableaux nécessaires
    vector<vector<double>> P(pop_size, vector<double>(dim));
    vector<vector<double>> OldP(pop_size, vector<double>(dim));
    vector<vector<double>> mutant(pop_size, vector<double>(dim));
    vector<vector<double>> map (pop_size, vector<double>(dim));
    vector<vector<double>> T(pop_size, vector<double>(dim));
    vector<double> fitnessP(pop_size);
     vector<double> fitnessT(pop_size);
     vector <double> low , up ;
     //initalisation de la population P
    P=genererPopulation(low,up);
    //calculer fitness de p
    for (int i=0 ; i<pop_size ; i++)
        {
            fitnessP[i]=ObjFun(P[i]);
        }
    //initalisation de la population OldP
    OldP=genererPopulation(low,up);








   //sélection II
    for (int i=0 ; i<pop_size ; i++)
        {
            fitnessT[i]=ObjFun(T[i]);
        }

    for (int i=0 ; i<pop_size ; i++)
    { if ( fitnessT[i] < fitnessP[i])
        {fitnessP[i]=fitnessT[i];
        P[i]=T[i] ;
        }
    }
    double fitnessPbest;
    //=min(fitnessP);
    if (fitnessPbest< globalMin)
    {
        globalMin=fitnessPbest;
       // globalMinimizer=P;
    }
}
