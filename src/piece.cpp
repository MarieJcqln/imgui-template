#include "piece.hpp"
#include "echequier.hpp"
#include "utils.hpp"

void moves_straight(position piece_position, std::vector<position>& list_moves, Echequier& echequier)
{
    int x = piece_position.x;
    int y = piece_position.y;

    // Vérifier que la case initiale contient bien une pièce
    if (echequier.tab_piece[y][x] == nullptr)
        return;

    // Récupération de la couleur de la pièce actuelle
    Color piece_color = echequier.tab_piece[x][y]->m_color;

    // Déplacements en ligne droite : {dx, dy}
    int directions[4][2] = {
        {0, 1},  // Haut
        {0, -1}, // Bas
        {1, 0},  // Droite
        {-1, 0}  // Gauche
    };

    // Parcours des 4 directions
    for (auto& dir : directions)
    {
        int dx   = dir[0];
        int dy   = dir[1];
        int newX = x + dx;
        int newY = y + dy;

        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            if (echequier.tab_piece[newY][newX] != nullptr)
            {
                // Si c'est une pièce adverse, on peut capturer
                if (echequier.tab_piece[newY][newX]->m_color != piece_color)
                {
                    list_moves.emplace_back(newX, newY);
                }
                break; // On stoppe la boucle après avoir rencontré une pièce
            }

            // Si la case est vide, on peut y aller
            list_moves.emplace_back(newX, newY);

            // Avancer dans la direction
            newX += dx;
            newY += dy;
        }
    }
}

void moves_diagonal(position piece_position, std::vector<position>& list_moves, Echequier& echequier)
{
    int x = piece_position.x;
    int y = piece_position.y;

    // Vérifier que la case initiale contient bien une pièce
    if (echequier.tab_piece[y][x] == nullptr)
        return;

    // Récupération de la couleur de la pièce actuelle
    Color piece_color = echequier.tab_piece[y][x]->m_color;

    // Déplacements diagonaux : {dx, dy}
    int directions[4][2] = {
        {1, 1},  // Haut-Droite
        {-1, 1}, // Haut-Gauche
        {1, -1}, // Bas-Droite
        {-1, -1} // Bas-Gauche
    };

    // Parcours des 4 directions diagonales
    for (auto& dir : directions)
    {
        int dx   = dir[0];
        int dy   = dir[1];
        int newX = x + dx;
        int newY = y + dy;

        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
        {
            if (echequier.tab_piece[newY][newX] != nullptr)
            {
                // Si c'est une pièce adverse, on peut capturer
                if (echequier.tab_piece[newY][newX]->m_color != piece_color)
                {
                    list_moves.emplace_back(newX, newY);
                }
                break; // On stoppe la boucle après avoir rencontré une pièce
            }

            // Si la case est vide, on peut y aller
            list_moves.emplace_back(newX, newY);

            // Avancer en diagonale
            newX += dx;
            newY += dy;
        }
    }
}

std::vector<position> Pawn::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};
    int                   direction = (m_color == white) ? -1 : 1; // Blancs montent (-1), Noirs descendent (+1)

    int x = piece_position.x;
    int y = piece_position.y;

    // Déplacement simple
    if ((y + direction) >= 0 && (y + direction) < 8 && echequier.tab_piece[y + direction][x] == nullptr)
    {
        list_moves.emplace_back(x, y + direction);

        // Déplacement double depuis la position initiale
        if ((m_color == white && y == 6) || (m_color == black && y == 1))
        {
            if (echequier.tab_piece[y + 2 * direction][x] == nullptr)
            {
                list_moves.emplace_back(x, y + 2 * direction);
            }
        }
    }

    // Captures diagonales
    for (int dx = -1; dx <= 1; dx += 2) // -1 et +1
    {
        int new_x = x + dx;
        int new_y = y + direction;

        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8)
        {
            if (echequier.tab_piece[new_y][new_x] != nullptr && echequier.tab_piece[new_y][new_x]->m_color != m_color)
            {
                list_moves.emplace_back(new_x, new_y); // Capture possible
            }
        }
    }

    return list_moves;
}

std::vector<position> Tower::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};
    moves_straight(piece_position, list_moves, echequier);
    return list_moves;
}

std::vector<position> Bishop::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};
    moves_diagonal(piece_position, list_moves, echequier);
    return list_moves;
}

std::vector<position> Horse::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};

    // Définir tous les déplacements possibles d'un cavalier (8 directions)
    const int moves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, // Déplacements de 2 cases en x et 1 en y
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2} // Déplacements de 2 cases en y et 1 en x
    };

    // Vérifier tous les déplacements possibles
    for (const auto& move : moves)
    {
        int new_x = piece_position.x + move[0];
        int new_y = piece_position.y + move[1];

        // Vérifier que les nouveaux indices sont dans les bornes de l'échiquier
        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8)
        {
            // Vérifier si la case cible est vide
            if (echequier.tab_piece[new_y][new_x] == nullptr || echequier.tab_piece[new_y][new_x]->m_color != m_color)
            {
                list_moves.emplace_back(new_x, new_y);
            }
        }
    }

    return list_moves;
}

std::vector<position> Queen::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};

    // Avance en ligne et diagonale
    moves_diagonal(piece_position, list_moves, echequier);
    moves_straight(piece_position, list_moves, echequier);

    return list_moves;
}

std::vector<position> King::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};

    const int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    };

    for (const auto& dir : directions)
    {
        int new_x = piece_position.x + dir[0];
        int new_y = piece_position.y + dir[1];

        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8)
        {
            if (echequier.tab_piece[new_y][new_x] == nullptr || echequier.tab_piece[new_y][new_x]->m_color != m_color)
            {
                list_moves.emplace_back(new_x, new_y);
            }
        }
    }

    /*     // Avance de 1 dans toutes les directions
        // on vérifie si les cases sont vides et dans l'échequier
        if ((piece_position.x + 1) < 8 && (piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.y + 1][piece_position.x + 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x + 1, piece_position.y + 1);
        }
        if ((piece_position.x - 1) >= 0 && (piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.y - 1][piece_position.x - 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x - 1, piece_position.y - 1);
        }
        if ((piece_position.x + 1) < 8 && (piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.y - 1][piece_position.x + 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x + 1, piece_position.y - 1);
        }
        if ((piece_position.x - 1) >= 0 && (piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.y + 1][piece_position.x - 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x - 1, piece_position.y + 1);
        }

        if ((piece_position.x + 1) < 8 && echequier.tab_piece[piece_position.y][piece_position.x + 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x + 1, piece_position.y);
        }
        if ((piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.y + 1][piece_position.x] == nullptr)
        {
            list_moves.emplace_back(piece_position.x, piece_position.y + 1);
        }
        if ((piece_position.x - 1) >= 0 && echequier.tab_piece[piece_position.y][piece_position.x - 1] == nullptr)
        {
            list_moves.emplace_back(piece_position.x - 1, piece_position.y);
        }
        if ((piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.y - 1][piece_position.x] == nullptr)
        {
            list_moves.emplace_back(piece_position.x, piece_position.y - 1);
        } */

    return list_moves;
}

void afficher_moves_possible(const std::vector<position>& list_moves, int x, int y)
{
    position current{x, y};

    for (const auto& move : list_moves)
    {
        if (move.x == current.x && move.y == current.y)
        {
            ImGui::PopStyleColor();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 0.f, 0.f, 1.f}); // Rouge
            break;                                                              // Sortir dès qu'on trouve un move valide
        }
    }
}
