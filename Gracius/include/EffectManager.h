#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include "SFML/Graphics.hpp"

class EffectManager {
        static EffectManager m_instance;
    public:
        static EffectManager& i() { return m_instance; }

        void init();
        void update(float _dt);
        void render(sf::RenderWindow& _window);


        // Background stars
        sf::RectangleShape m_stars[100];
        void initStars();
        void updateStars(float _dt);
        void renderStars(sf::RenderWindow& _window);
};

#endif // EFFECTMANAGER_H
