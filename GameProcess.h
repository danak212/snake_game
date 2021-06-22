#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <memory>
#include "GameRunner.h"
#include "CSnake.h"

class GameProcess : public Engine::States
{
public:
    GameProcess(std::shared_ptr<Context>& context);
    ~GameProcess();

    void Update(sf::Time incTime) override;
    void Draw() override;
    void Start() override;
    void Pause() override;
    void Initial() override;
    void StartingProcess() override;

private:
    std::shared_ptr<Context> context;
    std::array<sf::Sprite, 4> walls;
    sf::Sprite grass;
    CSnake Csnake;
    sf::Sprite apple;

    int score;
    sf::Text scoreCaption;

    sf::Vector2f snakeCourse;
    sf::Time elapsedTime;

    bool isPaused;
};

#endif // GAMEPROCESS_H
