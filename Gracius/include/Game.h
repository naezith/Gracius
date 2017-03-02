#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Enemy.h"
#include <memory>

class Game {
        static Game m_instance;
    public:
        static Game& i() { return m_instance; }

        void init(float _dt);
        void run();
        void restart();
        void update();
        void checkCollisions();
        void render();
        void addScore(int _amount);

        float getDeltaTime();
        void setDeltaTime(float _dt);
        sf::Texture& getTexture(std::string name);
        float getTime();
        sf::Vector2f getViewSize();

    private:
        int m_score;
        int m_highscore = 0;
        float m_accumulator = 0.0f;
        float m_dt = 1 / 125.0f;
        sf::RenderWindow m_window;
        sf::Vector2f m_view_size;
        float m_global_timer = 0.0f;

        std::shared_ptr<Player> m_player;
        std::vector<std::shared_ptr<Enemy>> m_enemies;
        std::vector<std::shared_ptr<Bullet>> m_bullets;
        float m_enemy_spawn_cd;
        float m_enemy_spawn_timer = 0.0f;

        bool m_first_launch = true;
        bool m_game_over = true;

        sf::Font m_font;
        std::map<std::string, sf::Texture> m_textures;
};

#endif // GAME_H
