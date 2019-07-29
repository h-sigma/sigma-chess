#include "Application.hpp"
#include "UCI.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <iostream>

Application::Application()
: mWindow( sf::VideoMode(60*8, 60*8), "E4E5", sf::Style::Close)
, mBoard(&mWindow, &mTextureHolder, 60)
{
}

void Application::run()
{
    sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time TimePerFrame = sf::seconds(1/60.f);

	std::cout << "Starting now...";
    std::chrono::system_clock::time_point  start = std::chrono::system_clock::now();
	bool result = UCI::isReady();
	if(result == true)
		std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count() << std::endl;

	while (mWindow.isOpen())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}

		render();
	}
}

void Application::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            mWindow.close();
        mBoard.handleEvent(event);
    }
}

void Application::update(sf::Time)
{

}
void Application::render()
{
    mWindow.clear();
    mWindow.draw(mBoard);
    mWindow.display();
}