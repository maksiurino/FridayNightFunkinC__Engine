#include "spriteHandler.hpp"

namespace spriteHandler
{
    std::map<std::string, sf::Texture>
    getTexturesFromCharacterPath(const std::string& characterName)
    {
        XMLDocument doc;
        std::map<std::string, sf::Texture> textures;

        const std::string basePath =
            "resources/assets/shared/images/characters/" + characterName;

        if (doc.LoadFile((basePath + ".xml").c_str()) != XML_SUCCESS)
            return textures;

        XMLElement* atlas = doc.FirstChildElement("TextureAtlas");
        if (!atlas)
            return textures;

        const char* imagePath = atlas->Attribute("imagePath");
        if (!imagePath)
            return textures;

        const std::string fullImagePath =
            std::filesystem::path(basePath).parent_path().string() +
            "/" + imagePath;

        sf::Image image;
        if (!image.loadFromFile(fullImagePath))
            return textures;

        for (XMLElement* sub = atlas->FirstChildElement("SubTexture");
             sub;
             sub = sub->NextSiblingElement("SubTexture"))
        {
            const char* name = sub->Attribute("name");
            if (!name)
                continue;

            int x = sub->IntAttribute("x");
            int y = sub->IntAttribute("y");
            int w = sub->IntAttribute("width");
            int h = sub->IntAttribute("height");

            sf::Texture tex(image, false, sf::IntRect({x, y}, {w, h}));
            tex.setSmooth(true);

            textures.emplace(name, std::move(tex));
        }

        return textures;
    }

    std::string getImagePathFromCharacter(const std::string& characterName)
    {
        XMLDocument doc;
        std::map<std::string, std::map<std::string, int>> textures;

        const std::string basePath =
            "resources/assets/shared/images/characters/" + characterName;
        doc.LoadFile((basePath + ".xml").c_str());

        const XMLElement* atlas = doc.FirstChildElement("TextureAtlas");

        const char* imagePath = atlas->Attribute("imagePath");

        return imagePath;
    }

    std::map<std::string, std::map<std::string, int>>
    getTextureDefinitionsFromCharacter(const std::string& characterName)
    {
        XMLDocument doc;
        std::map<std::string, std::map<std::string, int>> textures;

        const std::string basePath =
            "resources/assets/shared/images/characters/" + characterName;

        if (doc.LoadFile((basePath + ".xml").c_str()) != XML_SUCCESS)
            return textures;

        XMLElement* atlas = doc.FirstChildElement("TextureAtlas");
        if (!atlas)
            return textures;

        const char* imagePath = atlas->Attribute("imagePath");
        if (!imagePath)
            return textures;

        const std::string fullImagePath =
            std::filesystem::path(basePath).parent_path().string() +
            "/" + imagePath;

        sf::Image image;
        if (!image.loadFromFile(fullImagePath))
            return textures;

        for (XMLElement* sub = atlas->FirstChildElement("SubTexture");
             sub;
             sub = sub->NextSiblingElement("SubTexture"))
        {
            const char* name = sub->Attribute("name");
            if (!name)
                continue;

            int x = sub->IntAttribute("x");
            int y = sub->IntAttribute("y");
            int w = sub->IntAttribute("width");
            int h = sub->IntAttribute("height");

            std::map<std::string, int> map = {
                {"x", x},
                {"y", y},
                {"width", w},
                {"height", h}
            };

            textures.emplace(name, std::move(map));
        }

        return textures;
    }

    sf::Texture getAnimationFromCharacter(const std::string& characterName, const std::string& animationName, const int& animationFrame)
    {
        std::string imagePath;
        std::map<std::string, std::map<std::string, int>> textures = spriteHandler::getTextureDefinitionsFromCharacter(characterName);
        const std::string fullAnimationName = animationName + toFourDigits(animationFrame);
        std::cout << fullAnimationName << std::endl;
        const auto animIt = textures.find(fullAnimationName);
        if (animIt == textures.end())
            throw std::runtime_error("Animation not found: " + fullAnimationName);

        const std::string textureFilename = "resources/assets/shared/images/characters/" + getImagePathFromCharacter(fullAnimationName);

        if (sf::Image image; !image.loadFromFile(textureFilename))
        {
            std::cerr << "Cannot load texture from: " << textureFilename << std::endl;
        }

        auto& anim = animIt->second;
        sf::Texture texture(
            imagePath,
            false,
            sf::IntRect({
                anim.at("x"),
                anim.at("y")
            }, {
                anim.at("width"),
                anim.at("height")
            })
        );
        texture.setSmooth(true);
        return texture;
    }

    std::string toFourDigits(const int& value) {
        std::ostringstream ss;
        ss << std::setw(4) << std::setfill('0') << value;
        return ss.str();
    }
}
