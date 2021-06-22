#include "MainMenu.h"

GameRunner::GameRunner() : context(std::make_shared<Context>())
{
    context->window->create(sf::VideoMode(800, 600), "Snake Game", sf::Style::Close);
    context->states->Add(std::make_unique<MainMenu>(context));
}

GameRunner::~GameRunner() {}

void GameRunner::Run()
{
    sf::Clock clock;
    sf::Time SinceLast = sf::Time::Zero;

    while (context->window->isOpen())
    {
        SinceLast += clock.restart();

        while (SinceLast > TimeFrame)
        {
            SinceLast -= TimeFrame;

            context->states->ProcessChange();
            context->states->CurrentState()->StartingProcess();
            context->states->CurrentState()->Update(TimeFrame);
            context->states->CurrentState()->Draw();
        }
    }
}
