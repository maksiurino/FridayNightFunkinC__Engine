#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "musicHandler.hpp"
#include "spriteHandler.hpp"

using namespace sf; using namespace std; using namespace musicHandler;

int main()
{
    RenderWindow window(VideoMode({1280u, 720u}), "Friday Night Funkin' PlusPlus Engine");
    window.setFramerateLimit(60);

    int volume = 75;

    string currentSong = "bopeebo";
    string currentSongVariant = "";

    Music inst(getInstPath(currentSong, currentSongVariant));
    inst.setVolume(static_cast<float>(volume));

    std::map<std::string, sf::SoundBuffer> vocalBuffers;
    std::map<std::string, Sound> vocals;

    vocalBuffers["bf"] = sf::SoundBuffer(musicHandler::getVocalPath(currentSong, currentSongVariant, "bf"));
    vocalBuffers["dad"] = sf::SoundBuffer(musicHandler::getVocalPath(currentSong, currentSongVariant, "dad"));

    vocals.emplace("bf", sf::Sound(vocalBuffers["bf"]));
    vocals.emplace("dad", sf::Sound(vocalBuffers["dad"]));

    vocals.at("bf").setVolume(static_cast<float>(volume));
    vocals.at("dad").setVolume(static_cast<float>(volume));

    inst.play();
    vocals.at("bf").play();
    vocals.at("dad").play();

    string currentAnim = "BF idle dance";

    sf::Texture texture = spriteHandler::getAnimationFromCharacter("BOYFRIEND", currentAnim, 0);

    sf::Sprite character(texture);
    character.setScale(sf::Vector2f{0.5, 0.5});

    bool song_playing = true;

    int pause_press_counter = 0;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::FocusLost>())
            {
                if (song_playing)
                {
                    inst.pause();
                    vocals.at("bf").pause();
                    vocals.at("dad").pause();
                }
            }
            if (event->is<sf::Event::FocusGained>())
            {
                if (song_playing)
                {
                    inst.play();
                    vocals.at("bf").play();
                    vocals.at("dad").play();
                }
            }
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)))
        {
            if (pause_press_counter == 0)
            {
                song_playing = !song_playing;
                if (!song_playing)
                {
                    inst.pause();
                    vocals.at("bf").pause();
                    vocals.at("dad").pause();
                } else
                {
                    inst.play();
                    vocals.at("bf").play();
                    vocals.at("dad").play();
                }
            }
            pause_press_counter += 1;
        } else
        {
            pause_press_counter = 0;
        }

        window.clear();

        window.draw(character);

        window.display();
    }
}