#pragma once
#include <SFML/Graphics.hpp>
#include "Gift.h"

class Player : public sf::Drawable {

public:
	float speed = 200.f;
	float velocity;

	Player(int hp, float x, float y, const sf::Texture& bagTexture, const sf::Texture& elfTexture);

	void move(float x, float y, float maxWidth);
	void update(float dt, float maxWidth);
	bool inBag(const Gift& gift);

	int getScore();
	void increaseScore();

	int getHp();
	void loseHp();
	void restart();
	bool isDefeated();
	float getDefeatedAnimationCooldown();

private:
	int score;
	int hp;
	int maxHp;
	float yPos;
	sf::Sprite bagS;
	sf::Sprite elfS;

	float upAndDownCooldown = 0.5f;
	float dir = -1.0f;
	float lockMovementAnimationCooldown = 1.0f;
	float defeatedAnimationCooldown = 3.0f;
	bool defeated = false;
	static float scalingFactor;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};