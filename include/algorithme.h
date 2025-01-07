#ifndef ALGORITHME_H
#define ALGORITHME_H
#include <vector>
#include "solution.h"
using namespace std ;

class algorithme
{
public:
    algorithme(const Solution & sol,int pop_size, int dim,int epoch, int nbruns, double mixRate, const vector <double> &low, const vector <double> &up);
    virtual ~algorithme();
    std::vector<std::vector<double>> genererPopulation(std::vector<double> low, std::vector<double> up);
    double randn() ;
    double min(const vector<double>& vec, int &indexMin);
    void  affichage (const std::vector<double> &tab);
     void affichage(const std::vector<std::vector<double>>& tab);
    double ObjFun(const vector<double> &pop);
    void bsa () ;
    double getGlobalMin() const ;
    vector <double> getGlobalMinimizer() const ;


private:
    Solution d_sol;
    int pop_size; //taille de la population
    int dim;// dimensionn de l'individu


    int epoch ; //nombre d'it�rations
    int nb_runs ;// nombre �xecution
    double mixRate;
    vector <double> globalMinimizer; //meilleur individu d'une it�ration
    double globalMin; // meilleur fitnesse d'une it�ration// mixrate pour le croissement
    vector <double> low ;
    vector <double> up;
};

#endif // ALGORITHME_H
