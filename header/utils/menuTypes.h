#pragma once

#include <string>
#include <vector>
#include <functional>

enum class MenuItemType { 
    MENU,
    ACTION,
    TOGGLE,
    SLIDER,
    CAROUSEL
};

struct MenuItem
{
    std::string name = "null";
    MenuItemType type = MenuItemType::MENU;
    std::vector<MenuItemType> children;
    std::function<void()> func = nullptr;
};
