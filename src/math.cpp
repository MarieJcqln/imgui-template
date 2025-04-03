#include "math.hpp"
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include "quick_imgui/quick_imgui.hpp"

// Générateur aléatoire global
static std::random_device rd;
std::mt19937              gen(rd());

// Fonction pour générer un nombre suivant une loi uniforme entre [a, b]
double random_uniform(double a, double b)
{
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(gen);
}

// Fonction pour générer un nombre suivant une loi normale (Gaussienne)
double random_normal(double mean, double stddev)
{
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(gen);
}

// Fonction pour générer un nombre suivant une loi exponentielle
double random_exponential(double lambda)
{
    std::exponential_distribution<double> distribution(lambda);
    return distribution(gen);
}

/* int main()
{
    // Test des fonctions
    std::cout << "Loi uniforme (0, 1) : " << random_uniform(0.0, 1.0) << std::endl;
    std::cout << "Loi normale (moyenne = 0, écart-type = 1) : " << random_normal(0.0, 1.0) << std::endl;
    std::cout << "Loi exponentielle (lambda = 1.0) : " << random_exponential(1.0) << std::endl;

    return 0;
} */
