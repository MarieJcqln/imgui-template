#include "math.hpp"
#include <imgui.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <vector>
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

// Chaine de Markov
// pour obtenir les coordonnées x et y de la case piégée (compris entre 0 et 8)
// probabilités par case = quand on est au milieu, moins de chance de bouger

constexpr int SIZE      = 8;
constexpr int NB_STATES = SIZE * SIZE;

// Fonction pour l'attraction vers le centre
double center_weight(int x, int y)
{
    double dx   = x - 3.5;
    double dy   = y - 3.5;
    double dist = std::sqrt(dx * dx + dy * dy);
    return 1.0 / (1.0 + dist); // Plus proche du centre = poids plus grand
}

// Génération de la matrice de transition
std::vector<std::vector<double>> build_transition_matrix()
{
    std::vector<std::vector<double>> matrix(NB_STATES, std::vector<double>(NB_STATES, 0.0));

    for (int y = 0; y < SIZE; ++y)
    {
        for (int x = 0; x < SIZE; ++x)
        {
            int from = y * SIZE + x;

            std::vector<int>    neighbors;
            std::vector<double> weights;

            // Rester sur place
            neighbors.push_back(from);
            weights.push_back(0.4 * center_weight(x, y)); // pondération selon la position

            // Pour chaque voisins dans le plateau
            // On pondère encore selon la position par rapport au centre
            if (x > 0)
            {
                int to = y * SIZE + (x - 1);
                neighbors.push_back(to);
                weights.push_back(center_weight(x - 1, y));
            }
            if (x < SIZE - 1)
            {
                int to = y * SIZE + (x + 1);
                neighbors.push_back(to);
                weights.push_back(center_weight(x + 1, y));
            }
            if (y > 0)
            {
                int to = (y - 1) * SIZE + x;
                neighbors.push_back(to);
                weights.push_back(center_weight(x, y - 1));
            }
            if (y < SIZE - 1)
            {
                int to = (y + 1) * SIZE + x;
                neighbors.push_back(to);
                weights.push_back(center_weight(x, y + 1));
            }

            // Normalisation
            double total = std::accumulate(weights.begin(), weights.end(), 0.0);
            for (double& w : weights)
                w /= total;

            // Remplir la ligne de la matrice
            for (size_t i = 0; i < neighbors.size(); ++i)
            {
                matrix[from][neighbors[i]] = weights[i];
            }
        }
    }

    return matrix;
}

// Simulation d’un pas selon la matrice
int simulate_next_position(int current_index, const std::vector<std::vector<double>>& matrix)
{
    std::discrete_distribution<> dist(matrix[current_index].begin(), matrix[current_index].end());
    return dist(gen);
}

// Fonction utilisateur pour obtenir la position suivante
std::pair<int, int> next_markov_position(int x, int y, const std::vector<std::vector<double>>& matrix)
{
    int index      = y * SIZE + x;
    int next_index = simulate_next_position(index, matrix);
    int new_x      = next_index % SIZE;
    int new_y      = next_index / SIZE;
    return {new_x, new_y};
}
