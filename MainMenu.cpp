#include <SFML/Window/Event.hpp>
#include "MainMenu.h"
#include "GameProcess.h"

MainMenu::MainMenu(std::shared_ptr<Context>& ctx)
    : Engine::State(Engine::StateType::MAINMENU),
    context(ctx), isPlayButtonSelected(true),
    isPlayButtonPressed(false), isExitButtonSelected(false),
    isExitButtonPressed(false) {}

MainMenu::~MainMenu() {}

void MainMenu::Update(sf::Time incTime)
{
    if (isExitButtonSelected)
    {
        playButton.setFillColor(sf::Color::Red);
        exitButton.setFillColor(sf::Color::Green);
    }
    else
    {
        playButton.setFillColor(sf::Color::Green);
        exitButton.setFillColor(sf::Color::Red);
    }

    if (isPlayButtonPressed) { context->states->Add(std::make_unique<GameProcess>(context), true); }
    else if (isExitButtonPressed) { context->window->close(); }
}

void MainMenu::Draw()
{
    context->window->clear(sf::Color::Black);
    context->window->draw(gameCaption);
    context->window->draw(playButton);
    context->window->draw(exitButton);
    context->window->display();
}

void MainMenu::Initial()
{
    context->assets->FontAdder(FONT, "assets/fonts/Pacifico-Regular.ttf");

    gameCaption.setFont(context->assets->FontGetter(FONT));
    gameCaption.setString("Snake Game");
    gameCaption.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2 - 150.f);
    gameCaption.setOrigin(gameCaption.getLocalBounds().width / 2,
        gameCaption.getLocalBounds().height / 2);

    playButton.setFont(context->assets->FontGetter(FONT));
    playButton.setString("Play");
    playButton.setCharacterSize(25);
    playButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2 - 25.f);
    playButton.setOrigin(playButton.getLocalBounds().width / 2,
        playButton.getLocalBounds().height / 2);

    exitButton.setFont(context->assets->FontGetter(FONT));
    exitButton.setString("Exit");
    exitButton.setCharacterSize(25);
    exitButton.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2 + 25.f);
    exitButton.setOrigin(exitButton.getLocalBounds().width / 2,
        exitButton.getLocalBounds().height / 2);
}

void MainMenu::StartingProcess()
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
                if (!isPlayButtonSelected)
                {
                    isPlayButtonSelected = true;
                    isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::S:
            {
                if (!isExitButtonSelected)
                {
                    isPlayButtonSelected = false;
                    isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                isPlayButtonPressed = false;
                isExitButtonPressed = false;

                if (isPlayButtonSelected) { isPlayButtonPressed = true; }
                else { isExitButtonPressed = true; }
                break;
            }
            default: { break; }
            }
        }
    }
}
