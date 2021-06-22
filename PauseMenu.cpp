#include <SFML/Window/Event.hpp>
#include "PauseMenu.h"

PauseMenu::PauseMenu(std::shared_ptr<Context>& context)
    : context(context) {}

PauseMenu::~PauseMenu() {}

void PauseMenu::Update(sf::Time incTime) {}

void PauseMenu::Draw()
{
    context->window->draw(pauseCaption);
    context->window->display();
}

void PauseMenu::StartingProcess()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { context->window->close(); }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                context->states->PopCurrent();
                break;
            }
            default: { break; }
            }
        }
    }
}

void PauseMenu::Initial()
{
    pauseCaption.setFont(context->assets->FontGetter(FONT));
    pauseCaption.setString("Paused");
    pauseCaption.setPosition(context->window->getSize().x / 2,
        context->window->getSize().y / 2);
    pauseCaption.setOrigin(pauseCaption.getLocalBounds().width / 2,
        pauseCaption.getLocalBounds().height / 2);
}
