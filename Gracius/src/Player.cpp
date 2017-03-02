#include "Player.h"
#include "utility.h"

static const float PLAYER_SPEED = 400.0f;

static const sf::IntRect NORMAL_STANCE_RECT(200, 8, 32, 35);

Player::Player(sf::Texture& _texture) : Ship(_texture, &m_bullets, sf::Vector2f(22, 8), 0.25f){
    float player_scale = 1.0f;
    setScale(player_scale, player_scale);
    setOrigin(player_scale*sf::Vector2f(NORMAL_STANCE_RECT.width, NORMAL_STANCE_RECT.height)*0.5f);

    spawn();
}

void Player::spawn() {
    setTextureRect(NORMAL_STANCE_RECT);
    sf::Vector2f view_size = Game::i().getViewSize();
    setPosition(100.0f, view_size.y*0.5f);
    m_bullets.clear();
    GameObject::spawn();
    setWeapon(1);
    m_swiper_count = 10;
}

void Player::update(float _dt) {
    if(!isDead()) {
    // Inputs
        // Movement
        sf::Vector2f input(0.0f, 0.0f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) input.y += -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input.y += 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input.x += -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input.x += 1;
        setSpeed(PLAYER_SPEED*normalize(input));

        // Weapon
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) setWeapon(1);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) setWeapon(2);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G) && m_swiper_count > 0) {
            if(shoot(3)) --m_swiper_count;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) shoot();

        Ship::update(_dt);

    // Limit the borders
        sf::Vector2f view_size = Game::i().getViewSize();
        if(getCollisionBox().left < 0.0f) setPosition(getCollisionBox().width*0.5f, getPosition().y);
        else if(getCollisionBox().left + getCollisionBox().width > view_size.x*0.5f) setPosition(view_size.x*0.5f - getCollisionBox().width*0.5f, getPosition().y);
        if(getPosition().y < 0.0f)        setPosition(getPosition().x, getCollisionBox().height*0.5f);
        else if(getPosition().y > view_size.y) setPosition(getPosition().x, view_size.y - getCollisionBox().height*0.5f);
    }

    // Update bullets
    for(unsigned i = 0; i < m_bullets.size(); ++i){
        m_bullets[i]->update(_dt);
        if(m_bullets[i]->isDead()) m_bullets.erase(m_bullets.begin() + i--);
    }
}

bool Player::checkIfHit(GameObject& o) {
    if(!o.isDead()) {
        for(auto& b : m_bullets) {
            if(!b->isDead() && b->getCollisionBox().intersects(o.getCollisionBox())) {
                b->die();
                o.die();
                Game::i().addScore(10);
                return true;
            }
        }
        return Ship::checkIfHit(o);
    }
    return false;
}

void Player::render(sf::RenderWindow& _window) {
    for(auto& b : m_bullets) _window.draw(*b);

    Ship::render(_window);
}

int Player::getSwiperCount() { return m_swiper_count; }
