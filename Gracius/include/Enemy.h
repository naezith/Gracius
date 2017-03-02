#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include "Ship.h"

class Enemy : public Ship {
    public:
        Enemy(sf::Texture& _texture, std::vector<std::shared_ptr<Bullet>>* _bullets, sf::Vector2f _position);

        void update(float _dt);
};

#endif // ENEMY_H
