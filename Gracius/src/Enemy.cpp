#include "Enemy.h"
#include "Game.h"
#include "utility.h"

static const float ENEMY_SPEED = 100.0f;
static const sf::IntRect NORMAL_STANCE_RECT(50, 48, 12, 15);

Enemy::Enemy(sf::Texture& _texture, std::vector<std::shared_ptr<Bullet>>* _bullets, sf::Vector2f _position) : Ship(_texture, _bullets, sf::Vector2f(12, 15), 3.0f, -150.0f){
    setTextureRect(NORMAL_STANCE_RECT);

    float scale = 1.0f;
    setScale(scale, scale);
    setOrigin(scale*sf::Vector2f(NORMAL_STANCE_RECT.width, NORMAL_STANCE_RECT.height)*0.5f);
    setPosition(_position);
    setWeapon(0);
}

void Enemy::update(float _dt) {
    // Movement
    sf::Vector2f input(-1.0f, 0.0f);
    setSpeed(ENEMY_SPEED*normalize(input));

    // Attack
    shoot();

    if(getCollisionBox().left < 0.0f) {
        Game::i().addScore(-10);
        die();
    }

    Ship::update(_dt);
}
