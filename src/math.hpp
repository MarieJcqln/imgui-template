#pragma once
#include <imgui.h>
#include <algorithm>
#include <iostream>
#include <list>
#include "quick_imgui/quick_imgui.hpp"

class board_color {
    ImVec4 dark_color{0.f, 0.f, 0.f, 1.f};
    ImVec4 light_color{1.f, 1.f, 1.f, 1.f};
};