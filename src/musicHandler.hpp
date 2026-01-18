#pragma once
#include <string>

namespace musicHandler
{
    std::string getInstPath(const std::string& songName,
                            const std::string& songVariant);

    std::string getVocalPath(const std::string& songName,
        const std::string& songVariant, const std::string& character);
}
