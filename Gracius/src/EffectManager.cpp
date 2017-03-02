#include "EffectManager.h"
#include "utility.h"

EffectManager EffectManager::m_instance;

void EffectManager::init() {
    initStars();
}

void EffectManager::update(float _dt) {
    updateStars(_dt);
}

void EffectManager::render(sf::RenderWindow& _window) {
    renderStars(_window);
}


// Stars
void EffectManager::initStars() {
    sf::Vector2f view_size = Game::i().getViewSize();
    for(unsigned i = 0; i < 100; ++i) {
        m_stars[i].setSize(sf::Vector2f(1.0f, 1.0f));
        m_stars[i].setPosition(random_float(0.0f, view_size.x), random_float(0.0f, view_size.y));
    }
}


void EffectManager::updateStars(float _dt) {
    sf::Vector2f view_size = Game::i().getViewSize();
    for(unsigned i = 0; i < 100; ++i) {
        m_stars[i].move(sf::Vector2f(-250.0f, 0.0f) * _dt);
        if(m_stars[i].getPosition().x < 0.0f) m_stars[i].setPosition(view_size.x, m_stars[i].getPosition().y);
        else if(m_stars[i].getPosition().x > view_size.x) m_stars[i].setPosition(0.0f, m_stars[i].getPosition().y);
        if(m_stars[i].getPosition().y < 0.0f) m_stars[i].setPosition(m_stars[i].getPosition().x, view_size.y);
        else if(m_stars[i].getPosition().y > view_size.y) m_stars[i].setPosition(m_stars[i].getPosition().x, 0.0f);
    }
}


void EffectManager::renderStars(sf::RenderWindow& _window) {
    for(unsigned i = 0; i < 100; ++i) _window.draw(m_stars[i]);
}
