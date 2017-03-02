#include "GameObject.h"

GameObject::GameObject(sf::Texture& _texture, sf::Vector2f _cb_size) : m_cb_size(_cb_size) { setTexture(_texture); }

void GameObject::update(float _dt) { move(m_speed*_dt); }

void GameObject::render(sf::RenderWindow& _window) { _window.draw(*this); }

sf::Vector2f GameObject::getSpeed() { return m_speed; }

void GameObject::setSpeed(sf::Vector2f _speed) { m_speed = _speed; }

sf::Vector2f GameObject::getCollisionBoxSize() { return sf::Vector2f(m_cb_size.x*getScale().x, m_cb_size.y*getScale().y); }

sf::FloatRect GameObject::getCollisionBox() {
    sf::Vector2f box_size = getCollisionBoxSize();
    return sf::FloatRect(getPosition().x - box_size.x*0.5f, getPosition().y - box_size.y*0.5f, box_size.x, box_size.y);
}

void GameObject::spawn() {
    if(m_dead) {
        m_dead = false;
    }
}

void GameObject::die() {
    if(!m_dead){
        m_dead = true;
    }
}

bool GameObject::isDead() { return m_dead; }
