#include "Player.h"

float Player::scalingFactor = 10.f;
Player::Player(int hp, float x, float y, const sf::Texture& bagTexture, const sf::Texture& elfTexture)
	: bagS(bagTexture), elfS(elfTexture), velocity(0.f), score(0), hp(hp), maxHp(hp), yPos(y)
{
	bagS.move({ x,y + 16.f * scalingFactor });
	elfS.move({ x,y });

	bagS.scale({ scalingFactor,scalingFactor });
	elfS.setTextureRect(sf::IntRect({ 2 * 16,0 }, { 16,48 }));
	elfS.scale({ scalingFactor,scalingFactor });
	elfS.move({ 32.f * scalingFactor / 2,0.f });
}

void Player::move(float x, float y, float maxWidth)
{
	sf::FloatRect elfBounds = elfS.getGlobalBounds();
	sf::FloatRect bagBounds = bagS.getGlobalBounds();

	if (bagBounds.position.x > maxWidth) {
		bagS.setPosition({ -32.f * scalingFactor / 2.f, yPos + 16.f * scalingFactor });
		elfS.setPosition({ 0.f,yPos });
	}
	else if(bagBounds.position.x + bagBounds.size.x < 0){
		bagS.setPosition({ maxWidth - 32.f * scalingFactor / 2.f, yPos + 16.f * scalingFactor });
		elfS.setPosition({ maxWidth,yPos });
	}
	bagS.move({ x,y });
	elfS.move({ x,y });
	if (lockMovementAnimationCooldown < 0.f) {
		if (x > 0.f) {
			elfS.setTextureRect(sf::IntRect({ 1 * 16,0 }, { 16,48 }));
		}
		else if (x < 0.f) {
			elfS.setTextureRect(sf::IntRect({ 0 * 16,0 }, { 16,48 }));
		}
		else {
			elfS.setTextureRect(sf::IntRect({ 2 * 16,0 }, { 16,48 }));
		}
	}
}

void Player::update(float dt, float maxWidth)
{

	if (defeated)
	{
		if (defeatedAnimationCooldown > 0.f) {
			move(0.f, 50.f * dt, maxWidth);
		}
		defeatedAnimationCooldown -= dt;
	}
	else {
		move(velocity * dt, 0, maxWidth);
		if (velocity > 100.f * dt) {
			velocity -= 100.f * dt;
		}
		else if (velocity < -100.f * dt) {
			velocity += 100.0f * dt;
		}
		else {
			velocity = 0.f;
		}
		upAndDownCooldown -= dt;
		if (upAndDownCooldown < 0.0f) {
			elfS.move({ 0.f,dir * scalingFactor });
			upAndDownCooldown = 0.5f;
			dir = -dir;
		}
	}
	lockMovementAnimationCooldown -= dt;

}

bool Player::inBag(const Gift& gift)
{
	sf::FloatRect bagRect = bagS.getGlobalBounds();
	sf::FloatRect giftRect = gift.giftSprite.getGlobalBounds();
	return giftRect.position.x > bagRect.position.x &&
		giftRect.position.x + giftRect.size.x < bagRect.position.x + bagRect.size.x &&
		giftRect.position.y + giftRect.size.y / 2.f > bagRect.position.y;

}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(bagS);
	target.draw(elfS);
}


int Player::getScore()
{
	return score;
}

void Player::increaseScore()
{
	score++;
	elfS.setTextureRect(sf::IntRect({ 3 * 16,0 }, { 16,48 }));
	lockMovementAnimationCooldown = 1.0f;

}

int Player::getHp() {
	return hp;
}

void Player::loseHp()
{
	hp--;
	elfS.setTextureRect(sf::IntRect({ 4 * 16,0 }, { 16,48 }));
	lockMovementAnimationCooldown = 1.0f;

	if (hp <= 0) {
		defeated = true;
		elfS.setTextureRect(sf::IntRect({ 5 * 16,0 }, { 16,48 }));
		lockMovementAnimationCooldown = 5.0f;
	}
}

void Player::restart()
{
	hp = maxHp;
	bagS.setPosition({ 0.f,yPos + 16.f * scalingFactor });
	elfS.setPosition({ 32.f * scalingFactor / 2.f, yPos });
	upAndDownCooldown = 0.5f;
	defeatedAnimationCooldown = 3.0f;
	lockMovementAnimationCooldown = 0.0f;
	score = 0;
	defeated = false;
}

bool Player::isDefeated() {
	return hp <= 0;
}

float Player::getDefeatedAnimationCooldown()
{
	return defeatedAnimationCooldown;
}
