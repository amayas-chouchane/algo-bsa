#include "algorithme.h"
#include <stdlib.h>
#include <iostream>
#include <limits> //pour numeric_limits (l'infini)
#include <algorithm> // Pour shuffle
#include <random>
#include <ctime>
using namespace std ;

algorithme::algorithme(const Solution & sol,int pop_size, int dim,int epoch, int nbruns, double mixRate, const vector <double> &low, const vector <double> &up):
    d_sol{sol},
    pop_size {pop_size},
    dim {dim},
    epoch{epoch},
    nb_runs{nbruns},
    mixRate{mixRate},

    globalMin {numeric_limits<double>::infinity()},
    low {low},
    up {up}
{
    globalMinimizer.resize(dim);

}

algorithme::~algorithme()
{
    //dtor
}

std::vector<std::vector<double>> algorithme::genererPopulation(std::vector<double> low, std::vector<double> up)
{   srand(static_cast<unsigned>(time(0)));
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
    // Gï¿½nï¿½rateur de nombres pseudo-alï¿½atoires
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
void algorithme :: affichage (const std::vector<double> &tab)
{


    for (int j=0; j<dim; j++)
    {
        cout << tab[j] << " ";
    }
    cout << endl ;
}
void algorithme::bsa ()
{
    for (int r =0 ; r < nb_runs ; r++)
    {

        //crï¿½ation des tableaux nï¿½cessaires
        vector<vector<double>> P(pop_size, vector<double>(dim));
        vector<vector<double>> OldP(pop_size, vector<double>(dim));
        vector<vector<double>> mutant(pop_size, vector<double>(dim));
        vector<vector<double>> map (pop_size, vector<double>(dim));
        vector<vector<double>> T(pop_size, vector<double>(dim));
        vector<double> fitnessP(pop_size);
        vector<double> fitnessT(pop_size);


        //initalisation de la population P
        P=genererPopulation(low,up);
        //calculer fitness de p
        for (int i=0 ; i<pop_size ; i++)
        {
            fitnessP[i]=d_sol.fitness(P[i]);
        }
        //initalisation de la population OldP
        OldP=genererPopulation(low,up);

        //rï¿½pï¿½ter jusqu'ï¿½ nombre d'itï¿½rations atteint
        for (int k =0 ; k <epoch ; k++)
        {


            //sï¿½lection I
            for (int i=0 ; i< pop_size ; ++i)
            {   std::random_device rd; // Générateur aléatoire basé sur le matériel (si disponible)
            std::mt19937 gen(rd()); // Générateur Mersenne Twister

// Distribution pour les variables aléatoires entre 0.0 et 1.0
std::uniform_real_distribution<> dis(0.0, 1.0);
                //gï¿½nï¿½rer des variables alï¿½atoires entre 0.0 et 1.0
                double a = dis(gen);
                double b = dis(gen);
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

                // Crï¿½ation d'un gï¿½nï¿½rateur alï¿½atoire
                std::random_device grain;  // Graine alï¿½atoire
                std::mt19937 generateur(grain()); // Gï¿½nï¿½rateur Mersenne Twister

                // Mï¿½langer le vecteur OldP
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


           std::random_device rd; // Générateur aléatoire basé sur le matériel (si disponible)
            std::mt19937 gen(rd()); // Générateur Mersenne Twister

// Distribution pour les variables aléatoires entre 0.0 et 1.0
std::uniform_real_distribution<> dis(0.0, 1.0);
                //gï¿½nï¿½rer des variables alï¿½atoires entre 0.0 et 1.0
                double c = dis(gen);
                double d = dis(gen);

            if ( c < d )
            {
                vector<int> u(dim);
                for (int j = 0; j < dim; ++j)
                {
                    u[j] = j;
                }
                for (int i =0 ; i < pop_size ; i++)
                {
                    random_shuffle(u.begin(), u.end());
                    int temp = static_cast<int>(std::ceil(mixRate * dim * rand()/ double(RAND_MAX)));

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

            //sï¿½lection II
            for (int i=0 ; i<pop_size ; i++)
            {
                fitnessT[i]=d_sol.fitness(T[i]);
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
           cout<< "exécution n° : " << r <<endl ;
            cout<< " meilleur fitness : " << globalMin << endl ;
            cout<< "individu correspond : " << endl ;
            affichage(globalMinimizer);

    }


}

double algorithme::getGlobalMin() const
{

    return globalMin;
}
vector <double> algorithme::getGlobalMinimizer() const
{

    return globalMinimizer;
}

