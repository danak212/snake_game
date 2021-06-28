#include <SFML/Window/Event.hpp>
#include "GameOver.h"
#include "GameProcess.h"

GameOver::GameOver(std::shared_ptr<Context>& context)
    : Engine::State(Engine::StateType::GAMEOVER), context(context), isRetryButtonSelected(true),
    isRetryButtonPressed(false), isExitButtonSelected(false),
    isExitButtonPressed(false) {}

GameOver::~GameOver() {}

void GameOver::Initial()
{
    gameOverCaption.setFont(context->assets->FontGetter(FONT));
    gameOverCaption.setString("Game Over");
    gameOverCaption.setOrigin(gameOverCaption.getLocalBounds().width / 2, gameOverCaption.getLocalBounds().height / 2);
    gameOverCaption.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 150.f);

    retryButton.setFont(context->assets->FontGetter(FONT));
    retryButton.setString("Retry");
    retryButton.setOrigin(retryButton.getLocalBounds().width / 2, retryButton.getLocalBounds().height / 2);
    retryButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 15.f);
    retryButton.setCharacterSize(25);

    exitButton.setFont(context->assets->FontGetter(FONT));
    exitButton.setString("Exit");
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2, exitButton.getLocalBounds().height / 2);
    exitButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 + 25.f);
    exitButton.setCharacterSize(25);
}

void GameOver::StartingProcess()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { context->window->close(); }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
            {
                if (!isRetryButtonSelected)
                {
                    isRetryButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::S:
            {
                if (!isExitButtonSelected)
                {
                    isExitButtonSelected = true;
                    isRetryButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                isRetryButtonPressed = false;
                isExitButtonPressed = false;

                if (isRetryButtonSelected) { isRetryButtonPressed = true; }
                else { isExitButtonPressed = true; }
                break;
            }
            default: { break; }
            }
        }
    }
}

void GameOver::Update(sf::Time incTime)
{
    if (isExitButtonSelected)
    {
        retryButton.setFillColor(sf::Color::Red);
        exitButton.setFillColor(sf::Color::Green);
    }
    else
    {
        retryButton.setFillColor(sf::Color::Green);
        exitButton.setFillColor(sf::Color::Red);
    }

    if (isRetryButtonPressed) { context->states->Add(std::make_unique<GameProcess>(context), true); }
    else if (isExitButtonPressed) { context->window->close(); }
}

void GameOver::Draw()
{
    context->window->clear(sf::Color::Black);
    context->window->draw(gameOverCaption);
    context->window->draw(retryButton);
    context->window->draw(exitButton);
    context->window->display();
}
