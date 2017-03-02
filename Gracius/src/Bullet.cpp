#include "Bullet.h"
#include "Game.h"
#include "utility.h"

Bullet::Bullet(sf::Vector2f _position, int _pattern, sf::IntRect _bullet_sprite_rect, sf::Vector2f _speed) :
    GameObject(Game::i().getTexture("PLAYER"), sf::Vector2f(_bullet_sprite_rect.width, _bullet_sprite_rect.height)) {

    firstY = _position.y;
    pattern = _pattern;

    setSpeed(_speed);
    setTextureRect(_bullet_sprite_rect);
    setOrigin(sf::Vector2f(_bullet_sprite_rect.width, _bullet_sprite_rect.height)*0.5f);
    setPosition(_position);
    setScale(sf::Vector2f(1.0f, 1.0f));
}

void Bullet::update(float _dt) {
    if(pattern == 0) { } // Default shoot, nothing extra.
    else if(pattern == 1 || pattern == 2){ // Sinus
        timer += _dt;
        float sin_pos = (pattern == 1 ? -1 : 1) * 50.0f*sin(timer*10.0f);
        setPosition(getPosition().x + getSpeed().x*_dt, firstY + sin_pos);
    }

    prev_pos = getPosition();

    sf::Vector2f view_size = Game::i().getViewSize();
    if(!sf::FloatRect(0.0f, 0.0f, view_size.x, view_size.y).intersects(getGlobalBounds())) die();


    setRotation(vecToAngle(getPosition() - prev_pos));
    GameObject::update(_dt);
}
