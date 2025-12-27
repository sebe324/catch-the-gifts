#include "Gift.h"
#include <random>

int random_int(int min, int max) {
	static thread_local std::mt19937 generator{ std::random_device{}() };
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}


float random_float(float min, float max) {
	static thread_local std::mt19937 generator{ std::random_device{}() };
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}


float Gift::scalingFactor = 5.f;
Gift::Gift(int type, bool isCoal, float speed, const sf::Vector2f& pos, const sf::Texture& giftTexture)
	: giftSprite(giftTexture), isCoal(isCoal), speed(speed) {
	giftSprite.setTextureRect(sf::IntRect({ type * 16,0 }, { 16,16 }));
	giftSprite.scale({scalingFactor,scalingFactor });
	giftSprite.setPosition(pos);

}

void Gift::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(giftSprite, states);
}

bool Gift::underMap(float height) {
	sf::FloatRect giftRect = giftSprite.getGlobalBounds();
	return giftRect.position.y > height;
}

void Gift::restart(float maxWidth)
{
	isCoal = false;
	int type = random_int(0, 7);
	giftSprite.setTextureRect(sf::IntRect({ type * 16,0 }, { 16,16 }));
	if (type == 6 || type == 7) isCoal = true;
	giftSprite.setPosition({ random_float(0.f,maxWidth - 200.f), -random_float(100.f,800.f) });

}