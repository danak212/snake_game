#include "MainMenu.h"

GameRunner::GameRunner() : context(std::make_shared<Context>())
{
    context->window->create(sf::VideoMode(800, 640), "Snake Game", sf::Style::Close);
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
            using namespace Engine;

            SinceLast -= TimeFrame;

            context->states->ProcessChange();

            context->states->CurrentState()->StartingProcess();
            State* s = context->states->CurrentState().get();
           StateType stype = s->type;

           if (stype == StateType::GAMEOVER) 
           {
               GameOver* go = static_cast<GameOver*>(s);
               go->Update(TimeFrame);
           }

           else if (stype == StateType::MAINMENU) 
           {
               MainMenu* mm = static_cast<MainMenu*>(s);
               mm->Update(TimeFrame);
           }

           else if (stype == StateType::GAMEPROCESS) 
           {
               GameProcess* gp = static_cast<GameProcess*>(s);
               gp->Update(TimeFrame);
           }
            context->states->CurrentState()->Draw();
        }
    }
}
