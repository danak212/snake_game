#include "CSnake.h"

CSnake::CSnake() : body(std::list<sf::Sprite>(5))
{
    head = --body.end();
    scut = body.begin();
}

CSnake::~CSnake() {}

void CSnake::draw(sf::RenderTarget& target, sf::RenderStates states) const{ for (auto& part : body) { target.draw(part); } }

void CSnake::Grow(const sf::Vector2f& course)
{
    sf::Sprite newPart;
    newPart.setTexture(*(body.begin()->getTexture()));
    newPart.setPosition(head->getPosition() + course);

    head = body.insert(++head, newPart);
}

bool CSnake::IsOn(const sf::Sprite& other) const { return other.getGlobalBounds().intersects(head->getGlobalBounds()); }

void CSnake::Move(const sf::Vector2f& course)
{
    scut->setPosition(head->getPosition() + course);
    head = scut;
    ++scut;
    if (scut == body.end()) { scut = body.begin(); }
}

void CSnake::Initial(const sf::Texture& texture)
{
    float x = 16.f;
    for (auto& part : body)
    {
        part.setTexture(texture);
        part.setPosition({ x, 16.f });
        x += 16.f;
    }
}

bool CSnake::isOwnHit() const
{
    bool hit = false;

    for (auto part = body.begin(); part != body.end(); ++part)
    {
        if (head != part)
        {
            hit = IsOn(*part);
            if (hit) break;
        }
    }
    return hit;
}
