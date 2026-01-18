#include "musicHandler.hpp"

namespace musicHandler
{
    std::string getInstPath(const std::string& songName,
                            const std::string& songVariant)
    {
        std::string mainPath =
            "resources/assets/songs/" + songName + "/Inst";

        if (!songVariant.empty())
        {
            mainPath += "-" + songVariant;
        }

        return mainPath + ".ogg";
    }

    std::string getVocalPath(const std::string& songName,
        const std::string& songVariant, const std::string& character)
    {
        std::string mainPath =
            "resources/assets/songs/" + songName + "/Voices";

        if (!character.empty())
        {
            mainPath += "-" + character;
        }
        if (!songVariant.empty())
        {
            mainPath += "-" + songVariant;
        }
        return mainPath + ".ogg";
    }
}
