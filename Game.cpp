#include "Game.h"

float Game::scalingFactor = 10.f;
Game::Game(float width, float height, const GameTextures& gameTextures, GameSounds& gameSounds, const sf::Font& font)
	:
    player(5,0.f,height-32.f*scalingFactor, gameTextures.bagTexture, gameTextures.elfTexture),
    width(width), height(height), scoreText(font), hpText(font), restartText(font), gameTextures(gameTextures), gameSounds(gameSounds), background(gameTextures.bgTexture)
{

    gifts.push_back(Gift(0, false, 200.f, { 100.f,700.f }, gameTextures.giftTexture));
    gifts.push_back(Gift(1, false, 200.f, { 400.f,800.f }, gameTextures.giftTexture));
    gifts.push_back(Gift(2, false, 200.f, { 200.f,200.f }, gameTextures.giftTexture));
    gifts.push_back(Gift(3, false, 200.f, { 700.f,400.f }, gameTextures.giftTexture));
    gifts.push_back(Gift(4, false, 200.f, { 100.f,100.f }, gameTextures.giftTexture));
    gifts.push_back(Gift(4, false, 200.f, { 100.f,100.f }, gameTextures.giftTexture));

    for (Gift& gift : gifts) {
        gift.restart(width);
    }
    scoreText.setCharacterSize(64);
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({ 16.f,0.f });
    updateScoreText();

    hpText.setCharacterSize(64);
    hpText.setStyle(sf::Text::Bold);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition({ 16.f,48.f });
    updateHpText();
    restartText.setCharacterSize(128);
    restartText.setStyle(sf::Text::Bold);
    restartText.setFillColor(sf::Color(200, 200, 50));
    restartText.setPosition({ 16.f,48.f });
    updateRestartText();

    background.scale({ scalingFactor,scalingFactor });
    gameSounds.backgroundMusic.play();

    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    overlay.setOrigin({ 0.f,0.f });
    overlay.setSize({ width,height });
}

void Game::updateScoreText() {
    scoreText.setString("Score: " + std::to_string(player.getScore()));
}

void Game::updateHpText() {
    hpText.setString("Lives: " + std::to_string(player.getHp()));
}

void Game::updateRestartText()
{
    restartText.setString("GAME OVER!\nPress R to\nrestart.\nFINAL SCORE: " + std::to_string(player.getScore()));
}
void Game::update(float dt) {

    if (!gameRunning && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        gameRunning = true;
        player.restart();
        updateScoreText();
        updateHpText();
        for (Gift& gift : gifts) gift.restart(width);
        gameSounds.backgroundMusic.play();
    }
    if (!gameRunning) return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) player.velocity = -player.speed * 2;
        else player.velocity = -player.speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) player.velocity = player.speed * 2;
        else player.velocity = player.speed;
    }
    player.update(dt, width);
    if (player.isDefeated()) {
        gameSounds.backgroundMusic.stop();
        if (player.getDefeatedAnimationCooldown() < 0.f) {
            gameRunning = false;
            updateRestartText();
        }
        return;
    }
    for (Gift& gift : gifts) {
        gift.giftSprite.move({ 0.f,gift.speed * dt });

        if(player.inBag(gift)) {
            if (gift.isCoal) {
                player.loseHp();
                if (player.isDefeated()) gameSounds.defeatedSound.play();
                else gameSounds.incorrectSound.play();
                updateHpText();
            }
            else {
                player.increaseScore();
                gameSounds.collectSound.play();
                updateScoreText();
            }
            gift.restart(width);

        }
        else if (gift.underMap(height)) {
            if (!gift.isCoal) {
                player.loseHp();
                if (player.isDefeated()) gameSounds.defeatedSound.play();
                else gameSounds.incorrectSound.play();
                updateHpText();
            }
            gift.restart(width);
        }
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background);
    target.draw(player);
    for (const Gift& gift : gifts) {
        target.draw(gift);
    }
    if (!gameRunning) {
        target.draw(overlay);
        target.draw(restartText);
    }
    if (gameRunning) {
        target.draw(hpText);
        target.draw(scoreText);
    }
}
