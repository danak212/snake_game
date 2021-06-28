#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "GameRunner.h"

class PauseMenu : public Engine::State
{
public:
    PauseMenu(std::shared_ptr<Context>& context);
    ~PauseMenu();

    void Draw() override;
    void StartingProcess() override;
    void Initial() override;

private:
    std::shared_ptr<Context> context;
    sf::Text pauseCaption;
};

#endif // PAUSEMENU_H
