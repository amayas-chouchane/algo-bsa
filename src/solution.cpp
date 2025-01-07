#include "Solution.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

Solution::Solution(int dim, int func_id)
{
    this->dimension = dim;
    this->functionIndex = func_id;
    this->tabLine.resize(dimension, 0.0); // Initialize solution vector with zeros
    this->currentFitness = numeric_limits<double>::infinity(); // Start with high fitness (placeholder)
}
Solution::Solution(const Solution& autre)
    : dimension(autre.dimension),
      functionIndex(autre.functionIndex)
{

}

// Calculate fitness based on the selected objective function
double Solution::fitness(const vector<double>& solution)
{
    switch (functionIndex)
    {
        case 1:  // Rosenbrock
          return rosenbrock(solution);
            break;
        case 2:  // Rastrigin
            return rastrigin(solution);
            break;
        case 3:  // Ackley
            return ackley(solution);
            break;
        case 4:  // Schwefel
            return schwefel(solution);
            break;
        default:
          return numeric_limits<double>::infinity(); // Return high value for invalid function index
            break;
    }
}

// Generate a random solution within the given bounds
void Solution::random(double lower, double upper)
{
    for (int i = 0; i < dimension; ++i)
    {
        tabLine[i] = lower + static_cast<double>(rand()) / RAND_MAX * (upper - lower);  // Random value within bounds
    }
}

// Rosenbrock's function (commonly used benchmark for optimization)
double Solution::rosenbrock(const vector<double>& solution)
{
    double sum = 0.0;
    for (int i = 0; i < dimension - 1; ++i)
    {
        sum += 100.0 * pow((solution[i + 1] - pow(solution[i], 2)), 2) + pow((solution[i] - 1), 2); // Rosenbrock formula
    }
    return sum;
}

// Rastrigin's function (widely used as a benchmark for optimization algorithms)
double Solution::rastrigin(const vector<double>& solution)
{
    double sum = 0.0;
    for (int i = 0; i < dimension; ++i)
    {
        sum += pow(solution[i], 2) - 10.0 * cos(2.0 * M_PI * solution[i]);  // Rastrigin formula
    }
    return 10.0 * dimension + sum;
}

// Ackley's function (another common benchmark test function)
double Solution::ackley(const vector<double>& solution)
{
    double sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < dimension; ++i)
    {
        sum1 += pow(solution[i], 2);
        sum2 += cos(2.0 * M_PI * solution[i]);
    }
    return -20.0 * exp(-0.2 * sqrt(sum1 / dimension)) - exp(sum2 / dimension) + 20.0 + exp(1); // Ackley formula
}

// Schwefel's function (often used for complex non-linear optimization problems)
double Solution::schwefel(const vector<double>& solution)
{
    double sum = 0.0;
    for (int i = 0; i < dimension; ++i)
    {
        sum += -solution[i] * sin(sqrt(abs(solution[i])));  // Schwefel formula
    }
    return 418.9829 * dimension - sum;  // Adjusted for Schwefel's constant
}

// Friend function to display solution details (solution vector and fitness)
ostream& operator<<(ostream& os, const Solution& sol)
{
    os << "Solution: [";
    for (int i = 0; i < sol.dimension; ++i)
    {
        os << sol.tabLine[i];
        if (i < sol.dimension - 1)
        {
            os << ", ";
        }
    }
    os << "], Fitness: " << sol.getFitness();  // Print fitness value as well
    return os;
}

double Solution::getFitness() const
{
    return currentFitness;  // Return the current fitness value (now correctly updated)
}
