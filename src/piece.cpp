#include "piece.hpp"
#include "echequier.hpp"
#include "utils.hpp"

// On va passer en paramètre un board (class) qui contient info du board
void moves_straight(position piece_position, std::vector<position>& list_moves, Echequier& echequier)
{
    // Avance en ligne jusqu'à rencontrer une piece
    int i{0};

    while (((echequier.selected_piece_position.y) + i) < 8 && echequier.tab_piece[echequier.selected_piece_position.x][(echequier.selected_piece_position.y) + i] == nullptr) // et sur le plateu
    {
        // pas de pièce au dessus
        // on ajoute à la liste la case disponible
        list_moves.emplace_back(piece_position.x, piece_position.y + i);
        i++;
    }
    while (((echequier.selected_piece_position.y) - i) >= 0 && echequier.tab_piece[echequier.selected_piece_position.x][(echequier.selected_piece_position.y) - i] == nullptr)
    {
        // pas de pièce en dessous
        list_moves.emplace_back(piece_position.x, piece_position.y - i);
        i++;
    }
    while (((echequier.selected_piece_position.x) + i) < 8 && echequier.tab_piece[(echequier.selected_piece_position.x) + i][echequier.selected_piece_position.y] == nullptr)
    {
        // pas de pièce à droite
        list_moves.emplace_back(piece_position.x + i, piece_position.y);
        i++;
    }
    while (((echequier.selected_piece_position.x) - i) >= 0 && echequier.tab_piece[(echequier.selected_piece_position.x) - i][echequier.selected_piece_position.y] == nullptr)
    {
        // pas de pièce à gauche
        list_moves.emplace_back(piece_position.x - i, piece_position.y);
        i++;
    }

    // la list_moves est modifié et peut être utilisée par la suite
}

void moves_diagonal(position piece_position, std::vector<position>& list_moves, Echequier& echequier)
{
    int x = piece_position.x;
    int y = piece_position.y;

    // Haut-Droite
    for (int i = 1; x + i < 8 && y + i < 8; i++)
    {
        if (echequier.tab_piece[x + i][y + i] != nullptr)
        {
            if (echequier.tab_piece[x + i][y + i]->m_color != echequier.tab_piece[x][y]->m_color)
                list_moves.emplace_back(x + i, y + i);
            break;
        }
        list_moves.emplace_back(x + i, y + i);
    }

    // Haut-Gauche
    for (int i = 1; x - i >= 0 && y + i < 8; i++)
    {
        if (echequier.tab_piece[x - i][y + i] != nullptr)
        {
            if (echequier.tab_piece[x - i][y + i]->m_color != echequier.tab_piece[x][y]->m_color)
                list_moves.emplace_back(x - i, y + i);
            break;
        }
        list_moves.emplace_back(x - i, y + i);
    }

    // Bas-Droite
    for (int i = 1; x + i < 8 && y - i >= 0; i++)
    {
        if (echequier.tab_piece[x + i][y - i] != nullptr)
        {
            if (echequier.tab_piece[x + i][y - i]->m_color != echequier.tab_piece[x][y]->m_color)
                list_moves.emplace_back(x + i, y - i);
            break;
        }
        list_moves.emplace_back(x + i, y - i);
    }

    // Bas-Gauche
    for (int i = 1; x - i >= 0 && y - i >= 0; i++)
    {
        if (echequier.tab_piece[x - i][y - i] != nullptr)
        {
            if (echequier.tab_piece[x - i][y - i]->m_color != echequier.tab_piece[x][y]->m_color)
                list_moves.emplace_back(x - i, y - i);
            break;
        }
        list_moves.emplace_back(x - i, y - i);
    }
}

std::vector<position> Pawn::moves_possible(position piece_position, Echequier& echequier)
{
    std::vector<position> list_moves{};
    // vérifier si la case est vide et sa couleur pour avancer dans le bon sens
    // on vérifie aussi si on reste sur l'échequier
    if ((piece_position.y - 1) >= 0 && m_color == white && echequier.tab_piece[piece_position.x][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x, piece_position.y - 1); // emplace back = pushback
    }
    else if ((piece_position.y + 1) >= 0 && m_color == black && echequier.tab_piece[piece_position.x][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x, piece_position.y + 1);
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

    // Avance en L
    // on vérifie si les cases sont vides et pas en dehors de l'echequier
    if ((piece_position.y + 1) < 8 && (piece_position.x + 3) < 8 && echequier.tab_piece[piece_position.x + 3][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 3, piece_position.y + 1);
    }
    if ((piece_position.y - 1) >= 0 && (piece_position.x + 3) < 8 && echequier.tab_piece[piece_position.x + 3][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 3, piece_position.y - 1);
    }
    if ((piece_position.y + 1) < 9 && (piece_position.x - 3) >= 0 && echequier.tab_piece[piece_position.x - 3][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 3, piece_position.y + 1);
    }
    if ((piece_position.y - 1) >= 0 && (piece_position.x - 3) >= 0 && echequier.tab_piece[piece_position.x - 3][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 3, piece_position.y - 1);
    }

    if ((piece_position.x + 1) < 8 && (piece_position.y + 3) < 8 && echequier.tab_piece[piece_position.x + 1][piece_position.y + 3] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 1, piece_position.y + 3);
    }
    if ((piece_position.x - 1) >= 0 && (piece_position.y + 3) < 8 && echequier.tab_piece[piece_position.x - 1][piece_position.y + 3] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 1, piece_position.y + 3);
    }
    if ((piece_position.x + 1) < 8 && (piece_position.y - 3) >= 0 && echequier.tab_piece[piece_position.x + 1][piece_position.y - 3] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 1, piece_position.y - 3);
    }
    if ((piece_position.x - 1) >= 0 && (piece_position.y - 3) >= 0 && echequier.tab_piece[piece_position.x - 1][piece_position.y - 3] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 1, piece_position.y - 3);
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

    // Avance de 1 dans toutes les directions
    // on vérifie si les cases sont vides et dans l'échequier
    if ((piece_position.x + 1) < 8 && (piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.x + 1][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 1, piece_position.y + 1);
    }
    if ((piece_position.x - 1) >= 0 && (piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.x - 1][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 1, piece_position.y - 1);
    }
    if ((piece_position.x + 1) < 8 && (piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.x + 1][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 1, piece_position.y - 1);
    }
    if ((piece_position.x - 1) >= 0 && (piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.x - 1][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 1, piece_position.y + 1);
    }

    if ((piece_position.x + 1) < 8 && echequier.tab_piece[piece_position.x + 1][piece_position.y] == nullptr)
    {
        list_moves.emplace_back(piece_position.x + 1, piece_position.y);
    }
    if ((piece_position.y + 1) < 8 && echequier.tab_piece[piece_position.x][piece_position.y + 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x, piece_position.y + 1);
    }
    if ((piece_position.x - 1) >= 0 && echequier.tab_piece[piece_position.x - 1][piece_position.y] == nullptr)
    {
        list_moves.emplace_back(piece_position.x - 1, piece_position.y);
    }
    if ((piece_position.y - 1) >= 0 && echequier.tab_piece[piece_position.x][piece_position.y - 1] == nullptr)
    {
        list_moves.emplace_back(piece_position.x, piece_position.y - 1);
    }

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
