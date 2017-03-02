#ifndef BULLET_H
#define BULLET_H

#include "SFML/Graphics.hpp"
#include "GameObject.h"

class Bullet : public GameObject {
    public:
        Bullet(sf::Vector2f _position, int _pattern, sf::IntRect _bullet_sprite_rect, sf::Vector2f _speed = sf::Vector2f(0, 0));

        void update(float _dt);

    private:
        float timer = 0.0f;
        int pattern = 0;
        float firstY;

        sf::Vector2f prev_pos;
};

#endif // BULLET_H
