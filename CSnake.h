#ifndef CSNAKE_H
#define CSNAKE_H
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <list>

class CSnake : public sf::Drawable
{
public:
    CSnake();
    ~CSnake();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void Grow(const sf::Vector2f& course);
    bool IsOn(const sf::Sprite& other) const;
    void Move(const sf::Vector2f& course);
    void Initial(const sf::Texture& texture);
    bool isOwnHit() const;

private:
    std::list<sf::Sprite>::iterator head;
    std::list<sf::Sprite> body;
    std::list<sf::Sprite>::iterator scut;
};

#endif // CSNAKE_H
