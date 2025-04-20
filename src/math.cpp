#include "math.hpp"
#include <imgui.h>
#include <math.h>
#include <algorithm>
#include <cstdlib> // Pour std::rand() et std::srand()
#include <ctime>   // Pour std::time()
#include <iomanip>
#include <iostream>
#include <list>
#include <numbers>
#include <numeric>
#include <vector>
#include "quick_imgui/quick_imgui.hpp"

// std::srand(static_cast<unsigned int>(std::time(nullptr)));
static std::random_device rd;
std::mt19937              gen(rd());
// Générateur aléatoire global
void init_random()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Loi uniforme entre O et 1
double random_uniform_01()
{
    return static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}

// Fonction pour générer un nombre avec la loi uniforme entre [a, b]
double random_uniform(double a, double b)
{
    // rand() retourne un entier entre 0 et RAND_MAX
    double u = static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    return a + u * (b - a);
}

// 2 vecteurs de couleurs : un pour les couleurs claires et un pour les couleurs foncées
// Tirer aléatoirement une couleur claire et une couleur foncée
std::vector<std::vector<int>> tirage_couleur()
{
    std::vector<std::vector<int>> light_colors;
    std::vector<std::vector<int>> dark_colors;

    // Ajout de couleurs au vecteur light_colors
    light_colors.push_back({251, 252, 252});
    light_colors.push_back({249, 231, 159});
    light_colors.push_back({210, 180, 222});
    light_colors.push_back({212, 239, 223});
    light_colors.push_back({250, 219, 216});

    // dark_colors
    dark_colors.push_back({23, 165, 137});
    dark_colors.push_back({28, 40, 51});
    dark_colors.push_back({46, 134, 193});
    dark_colors.push_back({125, 60, 152});
    dark_colors.push_back({183, 149, 11});

    std::vector<std::vector<int>> choix;

    // Tirage aléatoire

    int light_index = std::rand() % 5; // Générer un nombre entre 0 et 4
    int dark_index  = std::rand() % 5; // Générer un nombre entre 0 et 4

    choix.push_back(light_colors[light_index]);
    choix.push_back(dark_colors[dark_index]);

    return choix;
}

/* // Fonction pour générer un nombre suivant une loi normale (Gaussienne)
double random_normal(double mean, double stddev)
{
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(gen);
} */

/* // Pour générer une durée
double generate_time()
{
    // Paramètres de la loi normale
    double mean   = 35.0; // Moyenne de 35 secondes
    double stddev = 10.0; // Écart-type de 10 secondes

    // On génère une durée en secondes
    double duration = random_normal(mean, stddev);

    duration = std::clamp(duration, 0.0, 100.0);

    return duration;
} */

// Constantes
const double PI        = std::numbers::pi;
const double SQRT_2PI  = std::sqrt(2 * PI);
const double SQRT_2EPI = std::sqrt(2 * std::exp(1) * PI);

// Fonction f(x) = densité normale standard
double f(double x)
{
    return std::exp(-x * x / 2) / SQRT_2PI;
}

// Fonction g(x) = enveloppe exponentielle symétrique
double g(double x)
{
    return std::exp(-std::abs(x)) / 2.0;
}

// Générer une variable normale standard avec méthode du rejet
double normal_standard()
{
    double u = NAN;
    double x = 0;
    double v = 1;

    while (v > f(x))
    {
        // Générer x selon la loi exponentielle symétrique
        double a = random_uniform_01();
        x        = (a < 0.5) ? -std::log(2 * a) : std::log(2 * (1 - a));

        // Générer v ∈ [0, g(x)]
        v = g(x) * random_uniform_01();
    }

    return x;
}

// Générer une loi normale N(mean, stddev)
double random_normal(double mean, double stddev)
{
    return mean + stddev * normal_standard();
}

// Exemple d'utilisation
double generate_time()
{
    double mean   = 35.0;
    double stddev = 10.0;

    double duration = random_normal(mean, stddev);
    duration        = std::max(duration, 0.0);
    duration        = std::min(duration, 100.0);

    return duration;
}

// Fonction pour générer un nombre suivant une loi exponentielle
double random_exponential(double lambda)
{
    double u{};
    while (u <= 1e-10)
    {
        u = random_uniform_01();
    }

    return -std::log(u) / lambda;
}

// On générer une durée au bout de laquelle les pions des joueurs seront inversés
double generate_duration_exp()
{
    double mean = 100;
    // Calcul du lambda (inverse de la moyenne)
    double lambda = 1.0 / mean;

    // On génère une durée en secondes
    double duration = random_exponential(lambda);

    return duration;
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

// Simulation selon la matrice
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

// Bernoulli

// Succès / échec
// Opportunité de récupérer sa dame quand il la perd
// Bouton "essaie de récupérer ta dame"

std::string random_bernoulli(double p)
{
    double u = random_uniform_01();
    return (u < p) ? "Succès" : "Échec";
}

// Si le joueur obtient M succès sur n essais,
// Il pourra jouer 2 fois
int random_binomial(int n, double p)
{
    int successes = 0;
    for (int i = 0; i < n; ++i)
    {
        if (random_bernoulli(p) == "Succès")
        {
            successes++;
        }
    }
    return successes;
}

bool bonus_turn(int m, int n, double p)
{
    return random_binomial(n, p) >= m;
}

// Si on obtient 1 ou plus, le roi est bloqué pendant un tour
int random_poisson(double lambda)
{
    int    count = 0;
    double L     = std::exp(-lambda);
    double p     = 1.0;
    while (p > L)
    {
        count++;
        p *= random_uniform_01();
    }
    return count - 1;
}

bool king_block(double p)
{
    return random_poisson(p) >= 1;
}

// Chaque joueur a un pion spécial dont la portée est définie par la loi de cauchy
double random_cauchy(double median, double gamma)
{
    double u = random_uniform_01();
    return median + gamma * std::tan(std::numbers::pi * (u - 0.5));
}

int crazy_pawn()
{
    int range = std::clamp(static_cast<int>(std::round(std::abs(random_cauchy(1, 2)))), 1, 8);

    return range;
}
