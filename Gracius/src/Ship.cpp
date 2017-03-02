#include "Ship.h"
#include "utility.h"

Ship::Ship(sf::Texture& _texture, std::vector<std::shared_ptr<Bullet>>* _bullet_container, sf::Vector2f _cb_size, float _fire_cd, float _bullet_speed) :
    GameObject(_texture, _cb_size),
    m_fire_cd(_fire_cd),
    m_bullet_speed(_bullet_speed),
    m_shoot_timer(0.0f),
    m_weapon(0),
    m_bullet_container(_bullet_container) {

}

sf::IntRect GREEN_SMALL_RECT(164, 55, 7, 4);
sf::IntRect GREEN_MEDIUM_RECT(180, 54, 9, 6);
sf::IntRect GREEN_BIG_RECT(203, 51, 18, 10);
sf::IntRect FLAME_RECT(243, 55, 12, 8);
sf::IntRect PINK_LINE_RECT(80, 53, 16, 6);

bool Ship::shoot(int _weapon) {
    if(canShoot) {
        if(_weapon == -1) _weapon = getWeapon();

        m_shoot_timer = 0.0f;
        canShoot = false;

        // 3 SHOTS
        if(_weapon == 0) {
            m_bullet_container->push_back(std::make_shared<Bullet>(sf::Vector2f(getCollisionBox().left + getCollisionBox().width, getPosition().y), 0, PINK_LINE_RECT, m_bullet_speed*angleToVec(90)));
        }
        else if(_weapon == 1) {
            for(int i = 75; i <= 105; i += 15){
                m_bullet_container->push_back(std::make_shared<Bullet>(sf::Vector2f(getCollisionBox().left + getCollisionBox().width, getPosition().y), 0, GREEN_BIG_RECT, m_bullet_speed*angleToVec(i)));
            }
        }
        // SPIRAL
        else if(_weapon == 2){
            m_bullet_container->push_back(std::make_shared<Bullet>(sf::Vector2f(getCollisionBox().left + getCollisionBox().width, getPosition().y), 1, FLAME_RECT, sf::Vector2f(m_bullet_speed, 0.0f)));
            m_bullet_container->push_back(std::make_shared<Bullet>(sf::Vector2f(getCollisionBox().left + getCollisionBox().width, getPosition().y), 2, FLAME_RECT, sf::Vector2f(m_bullet_speed, 0.0f)));
        }
        else if(_weapon == 3){
            for(int i = 75; i <= 105; ++i){
                m_bullet_container->push_back(std::make_shared<Bullet>(sf::Vector2f(getCollisionBox().left + getCollisionBox().width, getPosition().y), 0, GREEN_MEDIUM_RECT, m_bullet_speed*angleToVec(i)));
            }
        }
        return true;
    }
    return false;
}

void Ship::update(float _dt) {
    // Update canShoot
    if((m_shoot_timer += _dt) > m_fire_cd) canShoot = true;

    // Update the object
    GameObject::update(_dt);
}

void Ship::render(sf::RenderWindow& _window) {
    if(!isDead()) GameObject::render(_window);
}

int Ship::getWeapon() { return m_weapon; }

void Ship::setWeapon(int _weapon) {
    if(_weapon == 1) m_fire_cd = 0.2f;
    if(_weapon == 2) m_fire_cd = 0.15f;
    m_weapon = _weapon;
}

float Ship::getBulletSpeed() { return m_bullet_speed; }

void Ship::setBulletSpeed(float _bullet_speed) { m_bullet_speed = _bullet_speed; }

bool Ship::checkIfHit(GameObject& o) {
    if(!o.isDead()) {
        if(!isDead() && o.getCollisionBox().intersects(getCollisionBox())){
            o.die();
            die();
            return true;
        }
    }
    return false;
}
