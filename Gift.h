#pragma once
#include <SFML/Graphics.hpp>

class Gift : public sf::Drawable {
public:
	Gift(int type, bool isCoal, float speed, const sf::Vector2f& pos, const sf::Texture& giftTexture);
	sf::Sprite giftSprite;
	bool isCoal;
	float speed;
	bool underMap(float height);
	void restart(float maxWidth);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static float scalingFactor;
};