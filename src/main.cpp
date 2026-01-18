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

    window.clear(Color::Green);

    Font font(R"(C:\Windows\Fonts\Arial.ttf)");
    Text text(font);

    text.setString("Loading...");
    text.setFillColor(Color::White);
    text.setOutlineColor(Color::Black);
    text.setOutlineThickness(5);
    text.setCharacterSize(50);

    window.draw(text);

    window.display();

    auto bfSprites = spriteHandler::getTexturesFromCharacterPath("BOYFRIEND");

    string currentSong = "bopeebo";
    string currentSongVariant = "";

    Music inst(getInstPath(currentSong, currentSongVariant));
    inst.setVolume(static_cast<float>(volume));

    std::map<std::string, SoundBuffer> vocalBuffers;
    std::map<std::string, Sound> vocals;

    vocalBuffers["bf"] = SoundBuffer(getVocalPath(currentSong, currentSongVariant, "bf"));
    vocalBuffers["dad"] = SoundBuffer(getVocalPath(currentSong, currentSongVariant, "dad"));

    vocals.emplace("bf", Sound(vocalBuffers["bf"]));
    vocals.emplace("dad", Sound(vocalBuffers["dad"]));

    vocals.at("bf").setVolume(static_cast<float>(volume));
    vocals.at("dad").setVolume(static_cast<float>(volume));

    string currentAnim = "BF idle dance";

    std::map<std::string, std::map<std::string, int>> textures = spriteHandler::getTextureDefinitionsFromCharacter("BOYFRIEND");

    float currentAnimationFrame = 0;

    Sprite character(bfSprites.at(currentAnim + spriteHandler::toFourDigits(static_cast<int>(currentAnimationFrame))));
    character.setScale(Vector2f{0.5, 0.5});

    inst.play();
    vocals.at("bf").play();
    vocals.at("dad").play();

    bool song_playing = true;

    int pause_press_counter = 0;

    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
            {
                window.close();
            }
            if (event->is<Event::FocusLost>())
            {
                if (song_playing)
                {
                    inst.pause();
                    vocals.at("bf").pause();
                    vocals.at("dad").pause();
                }
            }
            if (event->is<Event::FocusGained>())
            {
                if (song_playing)
                {
                    inst.play();
                    vocals.at("bf").play();
                    vocals.at("dad").play();
                }
            }
        }

        if ((Keyboard::isKeyPressed(Keyboard::Key::Enter) || Keyboard::isKeyPressed(Keyboard::Key::Escape)))
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

        window.clear(Color::White);

        character.setTexture(bfSprites.at(currentAnim + spriteHandler::toFourDigits(static_cast<int>(currentAnimationFrame))));

        window.draw(character);

        window.display();

        currentAnimationFrame += 0.5f;
        if (currentAnimationFrame > 13)
        {
            currentAnimationFrame = 0;
        }
    }
}