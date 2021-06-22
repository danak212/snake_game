#ifndef GAMEOVER_H
#define GAMEOVER_H
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "GameRunner.h"

class GameOver : public Engine::States
{
public:
    GameOver(std::shared_ptr<Context>& context);
    ~GameOver();

    void StartingProcess() override;
    void Update(sf::Time incTime) override;
    void Draw() override;
    void Initial() override;

private:
    sf::Text gameOverCaption;
    sf::Text retryButton;
    sf::Text exitButton;
    std::shared_ptr<Context> context;

    bool isRetryButtonSelected;
    bool isRetryButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;
};

#endif // GAMEOVER_H
