#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include "quick_imgui/quick_imgui.hpp"

class board_color {
    ImVec4 dark_color{0.f, 0.f, 0.f, 1.f};
    ImVec4 light_color{1.f, 1.f, 1.f, 1.f};
};

// Fonction pour générer un nombre suivant une loi uniforme entre [a, b]
double random_uniform(double a, double b);

// Fonction pour générer un nombre suivant une loi normale (Gaussienne)
double random_normal(double mean, double stddev);

// Fonction pour générer un nombre suivant une loi exponentielle
double random_exponential(double lambda);

double                           center_weight(int x, int y);
std::vector<std::vector<double>> build_transition_matrix();
int                              simulate_next_position(int current_index, const std::vector<std::vector<double>>& matrix);
std::pair<int, int>              next_markov_position(int x, int y, const std::vector<std::vector<double>>& matrix);
