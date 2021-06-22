#include "Assets.h"

Engine::AssetS::AssetS() {}

Engine::AssetS::~AssetS() {}

void Engine::AssetS::FontAdder(int x, const std::string& fpath)
{
    auto font = std::make_unique<sf::Font>();
    if (font->loadFromFile(fpath)) { fonts[x] = std::move(font); }
}

void Engine::AssetS::TextureAdder(int x, const std::string& fpath, bool repeat)
{
    auto texture = std::make_unique<sf::Texture>();

    if (texture->loadFromFile(fpath))
    {
        texture->setRepeated(repeat);
        textures[x] = std::move(texture);
    }
}

const sf::Font& Engine::AssetS::FontGetter(int x) const { return *(fonts.at(x).get()); }

const sf::Texture& Engine::AssetS::TextureGetter(int x) const { return *(textures.at(x).get()); }
