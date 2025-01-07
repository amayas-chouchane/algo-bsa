#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <limits>

using namespace std;

#define PI 3.14159265

class Solution
{
public:
    // Constructor with dimensions and function index (for example: Rosenbrock, Ackley, etc.)
    Solution(int dim, int func_id);

    // Fitness calculation
     double getFitness()const ;                     // Get fitness value
    void random(double lower, double upper); // Generate random solution within bounds

    // Friend function for displaying Solution
    friend ostream& operator<<(ostream& os, const Solution& sol);

    // Public properties
    vector<double> tabLine; // Representation of variables
    int functionIndex;      // Type of the objective function (1=Rosenbrock, 2=Rastrigin, etc.)
    // Function to calculate fitness based on selected objective function
 void fitness(const vector<double>& solution);

private:
    double currentFitness; // Current fitness value
    int dimension;         // Dimension of the solution

    // Methods to evaluate specific objective functions
    double rosenbrock(const vector<double>& solution);
    double rastrigin(const vector<double>& solution);
    double ackley(const vector<double>& solution);
    double schwefel(const vector<double>& solution);


};

#endif // SOLUTION_H_INCLUDED
