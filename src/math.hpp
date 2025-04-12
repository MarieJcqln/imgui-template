#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include "quick_imgui/quick_imgui.hpp"

class board_color {
    ImVec4 dark_color{0.f, 0.f, 0.f, 1.f};
    ImVec4 light_color{1.f, 1.f, 1.f, 1.f};
};
void   init_random();
double random_uniform_01();
// Fonction pour générer un nombre suivant une loi uniforme entre [a, b]
double                        random_uniform(double a, double b);
std::vector<std::vector<int>> tirage_couleur();

// Fonction pour générer un nombre suivant une loi normale (Gaussienne)
double random_normal(double mean, double stddev);
double generate_time();

// Fonction pour générer un nombre suivant une loi exponentielle
double random_exponential(double lambda);
double generate_duration_exp();

double                           center_weight(int x, int y);
std::vector<std::vector<double>> build_transition_matrix();
int                              simulate_next_position(int current_index, const std::vector<std::vector<double>>& matrix);
std::pair<int, int>              next_markov_position(int x, int y, const std::vector<std::vector<double>>& matrix);

std::string random_bernoulli(double p);

int  random_binomial(int n, double p);
bool bonus_turn();

int  random_poisson(double lambda);
bool king_block(double p);

double random_cauchy(double median, double gamma);
int    crazy_pawn();