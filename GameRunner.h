#ifndef GAMERUNNER_H
#define GAMERUNNER_H
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "Assets.h"
#include "States.h"

struct Context
{
    std::unique_ptr<Engine::AssetS> assets;
    std::unique_ptr<Engine::States> states;
    std::unique_ptr<sf::RenderWindow> window;

    Context()
    {
        assets = std::make_unique<Engine::AssetS>();
        states = std::make_unique<Engine::States>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

#include "GameOver.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameProcess.h"

enum AssetID
{
    FONT = 0,
    CSNAKE,
    APPLE,
    GRASS,
    WALL,
    OBSTACLE
};

class GameRunner
{
public:
    GameRunner();
    ~GameRunner();
    void Run();

private:
    std::shared_ptr<Context> context;
    const sf::Time TimeFrame = sf::seconds(1.f / 60.f);
};

#endif // GAMERUNNER_H
