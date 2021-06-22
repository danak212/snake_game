#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include "GameProcess.h"
#include "GameOver.h"
#include "PauseMenu.h"

GameProcess::GameProcess(std::shared_ptr<Context>& context)
    : context(context), score(0), snakeCourse({ 16.f, 0.f }), elapsedTime(sf::Time::Zero), isPaused(false)
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
            for (auto& wall : walls)
            {
                if (Csnake.IsOn(wall))
                {
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            if (Csnake.IsOn(apple))
            {
                Csnake.Grow(snakeCourse);

                int x = 0, y = 0;
                x = std::clamp<int>(rand() % context->window->getSize().x, 16, context->window->getSize().x - 2 * 16);
                y = std::clamp<int>(rand() % context->window->getSize().y, 16, context->window->getSize().y - 2 * 16);

                apple.setPosition(x, y);
                score += 1;
                scoreCaption.setString("Score : " + std::to_string(score));
            }
            else { Csnake.Move(snakeCourse); }

            if (Csnake.isOwnHit()) { context->states->Add(std::make_unique<GameOver>(context), true); }

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
