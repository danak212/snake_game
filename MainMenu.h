#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "GameRunner.h"

class MainMenu : public Engine::State
{
public:
    MainMenu(std::shared_ptr<Context>& ctx);
    ~MainMenu();

    void Update(sf::Time incTime);
    void Draw() override;
    void Initial() override;
    void StartingProcess() override;

private:
    std::shared_ptr<Context> context;
    sf::Text playButton;
    sf::Text exitButton;
    sf::Text gameCaption;

    bool isPlayButtonSelected;
    bool isPlayButtonPressed;
    bool isExitButtonSelected;
    bool isExitButtonPressed;
};

#endif // MAINMENU_H
