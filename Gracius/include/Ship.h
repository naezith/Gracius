#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"
#include "Bullet.h"
#include <memory>

class Ship : public GameObject {
    public:
        Ship(sf::Texture& _texture, std::vector<std::shared_ptr<Bullet>>* _bullet_container, sf::Vector2f _cb_size,
             float _fire_cd = 0.5f, float _bullet_speed = 500.0f);

        virtual void update(float _dt);
        virtual void render(sf::RenderWindow& _window);
        virtual bool checkIfHit(GameObject& o);
        int getWeapon();

    protected:
        void setWeapon(int _weapon);
        bool shoot(int _weapon = -1);
        float getBulletSpeed();
        void setBulletSpeed(float _bullet_speed);

    private:
        // Bullets
        bool canShoot = false;
        float m_bullet_speed;
        float m_shoot_timer;
        float m_fire_cd;
        int m_weapon;

        std::vector<std::shared_ptr<Bullet>>* m_bullet_container;
};

#endif // SHIP_H
