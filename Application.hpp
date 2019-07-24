#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Board.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ResourceHolder.hpp"

namespace sf{
    class Time;
}

class Application
{
    public:
        explicit Application();
    public:
        void run();
    private:
        void processInput();
        void update(sf::Time dt);
        void render();
    private:
        sf::RenderWindow mWindow;
        TextureHolder mTextureHolder;
        Board mBoard;
};

#endif