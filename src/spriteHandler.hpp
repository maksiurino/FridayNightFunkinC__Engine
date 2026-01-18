#pragma once
#include <map>

#include "includes.hpp"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace spriteHandler
{
    std::map<std::string, sf::Texture> getTexturesFromCharacterPath(const std::string& characterName);
    std::string getImagePathFromCharacter(const std::string& characterName);
    std::map<std::string, std::map<std::string, int>> getTextureDefinitionsFromCharacter(const std::string& characterName);
    sf::Texture getAnimationFromCharacter(const std::string& characterName, const std::string& animationName, const int& animationFrame, std::map<std::string, std::map<std::string, int>>& textures);

    std::string toFourDigits(const int& value);
}
