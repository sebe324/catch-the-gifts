#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include "Game.h"
int main()
{
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Catch The Gifts!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    std::cout << shape.getOrigin().x;
    sf::Clock myClock;


    sf::Texture bagTexture("bag.png");
    sf::Texture elfTexture("elf.png");
    sf::Texture bgTexture("bg.png");
    sf::Texture giftTexture("texture.png");
    sf::SoundBuffer buffer("collect.wav");
    sf::Sound collectSound(buffer);
    sf::SoundBuffer buffer2("incorrect.wav");
    sf::Sound incorrectSound(buffer2);
    sf::SoundBuffer buffer3("defeated.wav");
    sf::Sound defeatedSound(buffer3);

    sf::Music music("theme.ogg");

    music.setVolume(10);
    music.setLooping(true);
    //https://commons.wikimedia.org/wiki/File:Merrychristmas-neuro.ogg
    GameTextures gameTextures = {
        bagTexture,
        elfTexture,
        giftTexture,
        bgTexture
    };
    GameSounds gameSounds = {
        collectSound,incorrectSound,defeatedSound,music
    };
    sf::Font font("font.ttf");
    Game game(WINDOW_WIDTH, WINDOW_HEIGHT, gameTextures, gameSounds, font);
    sf::Sprite background(bgTexture);
    background.scale({ 10.f,10.f });
    float dt = 0.016f;
    myClock.start();
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        game.update(dt);
        window.clear();
        window.draw(shape);
        window.draw(background);
        window.draw(game);
        window.display();
        dt = myClock.restart().asSeconds();

    }
}