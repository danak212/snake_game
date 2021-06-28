#ifndef ASSETS_H
#define ASSETS_H
#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <map>
#include <memory>

namespace Engine
{
    class AssetS
    {
    public:
        AssetS();
        ~AssetS();

        void FontAdder(int id, const std::string& fpath);
        void TextureAdder(int id, const std::string& fpath, bool repeat = false);

        const sf::Font& FontGetter(int id) const;
        const sf::Texture& TextureGetter(int id) const;

    private:
        std::map<int, std::unique_ptr<sf::Font>> fonts;
        std::map<int, std::unique_ptr<sf::Texture>> textures;
    };
} // namespace Engine

#endif // ASSETS_H
