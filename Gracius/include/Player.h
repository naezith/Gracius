#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "Ship.h"

class Player : public Ship {
    public:
        Player(sf::Texture& _texture);

        void spawn();
        void update(float _dt);
        void render(sf::RenderWindow& _window);
        bool checkIfHit(GameObject& o);
        int getSwiperCount();
    private:
        int m_swiper_count = 10;

        // Player's bullets
        std::vector<std::shared_ptr<Bullet>> m_bullets;
};

#endif // PLAYER_H
