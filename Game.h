#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gift.h"
#include "Player.h"

#include <vector>
struct GameTextures {
	sf::Texture& bagTexture;
	sf::Texture& elfTexture;
	sf::Texture& giftTexture;
	sf::Texture& bgTexture;
};

struct GameSounds {
	sf::Sound& collectSound;
	sf::Sound& incorrectSound;
	sf::Sound& defeatedSound;
	sf::Music& backgroundMusic;
};

class Game : public sf::Drawable {

public:
	Game(float width, float height, const GameTextures& gameTextures, GameSounds& gameSounds, const sf::Font& font);
	void update(float dt);
private:
	const float width;
	const float height;
	bool gameRunning = true;
	sf::RectangleShape overlay;
	std::vector<Gift> gifts;
	Player player;
	sf::Text scoreText;
	sf::Text hpText;
	sf::Text restartText;
	sf::Sprite background;

	const GameTextures& gameTextures;
	GameSounds& gameSounds;

	void updateScoreText();
	void updateHpText();
	void updateRestartText();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static float scalingFactor;
};