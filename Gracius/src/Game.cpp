#include "Game.h"
#include "EffectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "utility.h"
#include <iostream>
Game Game::m_instance;

void Game::init(float _dt) {
    setDeltaTime(_dt);
    m_view_size = sf::Vector2f(1280, 720);

    m_textures["PLAYER"].loadFromFile("resources/spritesheet.png");
    m_textures["PLAYER"].setSmooth(true);
    m_font.loadFromFile("resources/visitor2.ttf");

    m_player = std::make_shared<Player>(m_textures["PLAYER"]);

    EffectManager::i().init();
}

void Game::restart() {
    m_first_launch = m_game_over = false;
    m_player->spawn();

    m_enemies.clear();
    m_bullets.clear();

    if(m_score > m_highscore) m_highscore = m_score;
    m_score = 0;
    m_enemy_spawn_cd = 1.0f;
}

void Game::run() {
    sf::ContextSettings window_settings;
    window_settings.antialiasingLevel = 4;
    m_window.create(sf::VideoMode(m_view_size.x, m_view_size.y), "Gracius", sf::Style::Default, window_settings);
    sf::Clock clock;

    while(m_window.isOpen()){
        // Check events
        sf::Event event;
        while(m_window.pollEvent(event)){
            if(event.type == sf::Event::Closed) m_window.close();
        }

        // Update
        m_accumulator += clock.restart().asSeconds();
        while(m_accumulator > m_dt){
            m_accumulator -= m_dt;

            update();
        }

        // Render
        render();
    }
}

void Game::update() {
    m_global_timer += m_dt;
    EffectManager::i().update(m_dt);

    if(m_game_over) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) restart();
    }
    else{
        if(m_player->isDead()){
            m_game_over = true;
        }
    }

    checkCollisions();

    m_player->update(m_dt);

    // Update enemies
    if(!m_first_launch) {
        m_enemy_spawn_timer += m_dt;
        if(m_enemy_spawn_timer > m_enemy_spawn_cd) {
            if(m_enemy_spawn_cd > 0.175f) m_enemy_spawn_cd *= 0.99f;
            m_enemy_spawn_timer = 0.0f;
            m_enemies.push_back(std::make_shared<Enemy>(m_textures["PLAYER"], &m_bullets, sf::Vector2f(m_view_size.x + 10.0f, random_float(50.0f, m_view_size.y - 50.0f))));
        }
    }

    for(unsigned i = 0; i < m_enemies.size(); ++i) {
        m_enemies[i]->update(m_dt);
        if(m_enemies[i]->isDead()) m_enemies.erase(m_enemies.begin() + i--);
    }

    // Update bullets
    for(unsigned i = 0; i < m_bullets.size(); ++i){
        m_bullets[i]->update(m_dt);
        if(m_bullets[i]->isDead()) m_bullets.erase(m_bullets.begin() + i--);
    }
}

void Game::checkCollisions() {
    for(auto& e : m_enemies) {
        m_player->checkIfHit(*e);
    }

    for(auto& b : m_bullets) {
        if(!b->isDead() && b->getCollisionBox().intersects(m_player->getCollisionBox())) {
            b->die();
            m_player->die();
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color(0, 0, 0));


    EffectManager::i().render(m_window);
    m_player->render(m_window);
    for(auto& e : m_enemies) e->render(m_window);
    for(auto& b : m_bullets) b->render(m_window);

    if(m_game_over){
        sf::Text helper_text;
        helper_text.setFont(m_font);
        helper_text.setString("<Space> - Shoot         <1, 2> - Change Weapon         <G> - Use Swiper");
        helper_text.setOrigin(sf::Vector2f(helper_text.getLocalBounds().width, helper_text.getLocalBounds().height)*0.5f);
        helper_text.setPosition(m_view_size.x*0.5f, m_view_size.y*0.5f - 60.0f);
        m_window.draw(helper_text);

        sf::Text game_over_text;
        game_over_text.setFont(m_font);
        game_over_text.setString(m_first_launch ? std::string("Press <ENTER> to Start") : std::string("GAME OVER --- Press <ENTER> to Continue"));
        game_over_text.setOrigin(sf::Vector2f(game_over_text.getLocalBounds().width, game_over_text.getLocalBounds().height)*0.5f);
        game_over_text.setPosition(m_view_size.x*0.5f, m_view_size.y*0.5f + 60.0f);
        m_window.draw(game_over_text);
    }

    sf::Text score_text;
    score_text.setFont(m_font);
    score_text.setString(std::string("Score: ") + std::to_string(m_score));
    score_text.setPosition(15.0f, 15.0f);
    m_window.draw(score_text);

    sf::Text high_score_text;
    high_score_text.setFont(m_font);
    high_score_text.setString(std::string("High Score: ") + std::to_string(m_highscore));
    high_score_text.setPosition(500.0f, 15.0f);
    m_window.draw(high_score_text);

    sf::Text weapon_text;
    weapon_text.setFont(m_font);
    weapon_text.setString(std::string("Weapon: ") +
                         (m_player->getWeapon() == 1 ? "Trippler" :
                          m_player->getWeapon() == 2 ? "Sinusser" : "?"));
    weapon_text.setPosition(15.0f, m_view_size.y - 75.0f);
    m_window.draw(weapon_text);

    sf::Text swiper_count_text;
    swiper_count_text.setFont(m_font);
    swiper_count_text.setString(std::string("Swiper ( ") + std::to_string(m_player->getSwiperCount()) + " )");
    swiper_count_text.setPosition(500.0f, m_view_size.y - 75.0f);
    m_window.draw(swiper_count_text);

    m_window.display();
}


float Game::getDeltaTime() { return m_dt; }
void Game::setDeltaTime(float _dt) { m_dt = _dt; }
float Game::getTime() { return m_global_timer; }
sf::Vector2f Game::getViewSize() { return m_view_size; }

sf::Texture& Game::getTexture(std::string name) {
    return m_textures[name];
}

void Game::addScore(int _amount) { if(!m_game_over) m_score += _amount; }
