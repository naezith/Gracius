#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"

class GameObject : public sf::Sprite {
    public:
        GameObject(sf::Texture& _texture, sf::Vector2f _cb_size);

        virtual void update(float _dt);
        virtual void render(sf::RenderWindow& _window);

        void spawn();
        void die();
        bool isDead();

        sf::Vector2f getCollisionBoxSize();
        sf::FloatRect getCollisionBox();
        sf::Vector2f getSpeed();

    protected:
        void setSpeed(sf::Vector2f _speed);

    private:
        bool m_dead = false;
        sf::Vector2f m_cb_size;
        sf::Vector2f m_speed;
};

#endif // GAMEOBJECT_H
