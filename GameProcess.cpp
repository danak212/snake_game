#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include "GameProcess.h"
#include "GameOver.h"
#include "PauseMenu.h"
#include <algorithm>

GameProcess::GameProcess(std::shared_ptr<Context>& context)
    : Engine::State(Engine::StateType::GAMEPROCESS), context(context), score(0), snakeCourse({ 16.f, 0.f }), elapsedTime(sf::Time::Zero), isPaused(false)
{
    srand(time(nullptr));
}

GameProcess::~GameProcess() {}

void GameProcess::Update(sf::Time incTime)
{
    if (!isPaused)
    {
        elapsedTime += incTime;

        if (elapsedTime.asSeconds() > 0.1)
        {
            if (Csnake.IsOn(apple))
            {
                Csnake.Grow(snakeCourse);

                int x = 0, y = 0;
                do 
                {
                    x = std::clamp<int>(rand() % context->window->getSize().x, 16, context->window->getSize().x - 2 * 16);
                    y = std::clamp<int>(rand() % context->window->getSize().y, 16, context->window->getSize().y - 2 * 16);
                } while (std::any_of(obstacles.begin(), obstacles.end(), [=](const sf::Sprite& o) { return o.getGlobalBounds().contains(sf::Vector2f(x,y)); }));
                apple.setPosition(x, y);
                score += 1;
                scoreCaption.setString("Score : " + std::to_string(score));
            }
            else { Csnake.Move(snakeCourse); }

            if (Csnake.isOwnHit()) { context->states->Add(std::make_unique<GameOver>(context), true); }

            for (auto& wall : walls)
            {
                if (Csnake.IsOn(wall))
                {
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            for (auto& obstacle : obstacles)
            {
                if (Csnake.IsOn(obstacle))
                {
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

void GameProcess::Draw()
{
    context->window->clear();
    context->window->draw(grass);
    for (auto& wall : walls) { context->window->draw(wall); }
    context->window->draw(Csnake);
    for (auto& obstacle : obstacles) { context->window->draw(obstacle); }
    context->window->draw(apple);
    context->window->draw(scoreCaption);
    context->window->display();
}

void GameProcess::Start() { isPaused = false; }

void GameProcess::Pause() { isPaused = true; }

void GameProcess::Initial()
{
    context->assets->TextureAdder(WALL, "assets/textures/wall.png", true);
    context->assets->TextureAdder(GRASS, "assets/textures/grass.png", true);
    context->assets->TextureAdder(CSNAKE, "assets/textures/snake.png");
    context->assets->TextureAdder(APPLE, "assets/textures/apple.png");
    context->assets->TextureAdder(OBSTACLE, "assets/textures/obstacle.png", true);

    for (auto& wall : walls) { wall.setTexture(context->assets->TextureGetter(WALL)); }
    walls[0].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setTextureRect({ 0, 0, (int)context->window->getSize().x, 16 });
    walls[1].setPosition(0, context->window->getSize().y - 16);
    walls[2].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setTextureRect({ 0, 0, 16, (int)context->window->getSize().y });
    walls[3].setPosition(context->window->getSize().x - 16, 0);

    grass.setTexture(context->assets->TextureGetter(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    Csnake.Initial(context->assets->TextureGetter(CSNAKE));

    apple.setTexture(context->assets->TextureGetter(APPLE));
    apple.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);

    scoreCaption.setFont(context->assets->FontGetter(FONT));
    scoreCaption.setCharacterSize(12);
    scoreCaption.setString("Score : " + std::to_string(score));

    ObstaclesGen();
}

void GameProcess::StartingProcess()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { context->window->close(); }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newCourse = snakeCourse;
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                newCourse = { 0.f, -16.f };
                break;
            case sf::Keyboard::S:
                newCourse = { 0.f, 16.f };
                break;
            case sf::Keyboard::A:
                newCourse = { -16.f, 0.f };
                break;
            case sf::Keyboard::D:
                newCourse = { 16.f, 0.f };
                break;
            case sf::Keyboard::Escape:
                context->states->Add(std::make_unique<PauseMenu>(context));
                break;

            default:
                break;
            }

            if (std::abs(snakeCourse.x) != std::abs(newCourse.x) || std::abs(snakeCourse.y) != std::abs(newCourse.y))
            {
                snakeCourse = newCourse;
            }
        }
    }
}

// dodane 4 przeszkody
void GameProcess::ObstaclesGen()
{
    sf::Sprite o1;
    o1.setTextureRect({ 0, 0, 160, 16 });
    o1.setPosition(16 * 10, 16 * 5);
    o1.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o2;
    o2.setTextureRect({ 0, 0, 160, 16 });
    o2.setPosition(16 * 15, 16 * 10);
    o2.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o3;
    o3.setTextureRect({ 0, 0, 16, 160 });
    o3.setPosition(16 * 10, 16 * 10);
    o3.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o4;
    o4.setTextureRect({ 0, 0, 16, 128 });
    o4.setPosition(16 * 20, 16 * 20);
    o4.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o5;
    o5.setTextureRect({ 0, 0, 16, 160 });
    o5.setPosition(16 * 23, 16 * 28);
    o5.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o6;
    o6.setTextureRect({ 0, 0, 16, 128 });
    o6.setPosition(16 * 28, 16 * 20);
    o6.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o7;
    o6.setTextureRect({ 0, 0, 16, 96 });
    o6.setPosition(16 * 34, 16 * 15);
    o6.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o8;
    o8.setTextureRect({ 0, 0, 16, 96 });
    o8.setPosition(16 * 42, 16 * 12);
    o8.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o9;
    o9.setTextureRect({ 0, 0, 128, 16 });
    o9.setPosition(16 * 48, 16 * 40);
    o9.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o10;
    o10.setTextureRect({ 0, 0, 16, 96 });
    o10.setPosition(16 * 32, 16 * 30);
    o10.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o11;
    o11.setTextureRect({ 0, 0, 16, 96 });
    o11.setPosition(16 * 46, 16 * 10);
    o11.setTexture(context->assets->TextureGetter(OBSTACLE));

    sf::Sprite o12;
    o12.setTextureRect({ 0, 0, 96, 16 });
    o12.setPosition(16 * 43, 16 * 15);
    o12.setTexture(context->assets->TextureGetter(OBSTACLE));

    obstacles.emplace_back(o1);
    obstacles.emplace_back(o2);
    obstacles.emplace_back(o3);
    obstacles.emplace_back(o4);
    obstacles.emplace_back(o5);
    obstacles.emplace_back(o6);
    obstacles.emplace_back(o7);
    obstacles.emplace_back(o8);
    obstacles.emplace_back(o9);
    obstacles.emplace_back(o10);
    obstacles.emplace_back(o11);
    obstacles.emplace_back(o12);
}
