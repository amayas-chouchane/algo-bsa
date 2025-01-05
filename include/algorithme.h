#ifndef ALGORITHME_H
#define ALGORITHME_H
#include <vector>
using namespace std ;
class solution ;

class algorithme
{
    public:
        algorithme(int pop_size, int dim);
        virtual ~algorithme();
       std::vector<std::vector<double>> genererPopulation(std::vector<double> low, std::vector<double> up);
       void  affichage (const std::vector<std::vector<double>> &tab);
       double ObjFun(const vector<double> &pop);
       void bsa () ;

    protected:

    private:
       double d_sol;
       int pop_size; //taille de la population
       int dim;// dimensionn de l'individu

       vector <double> globalMinimizer; //meilleur individu d'une itération
       double globalMin; // meilleur fitnesse d'une itération

};

#endif // ALGORITHME_H
