#include <iostream>
#include <SFML/Graphics.hpp>

#include "info.h"
#include "logger.h"

#include <thread>
#include <chrono>

int main(int argc, char* argv[])
{
    std::cout << PRJ_NAME << " Version " << PRJ_VERSION << std::endl;

    sf::RenderWindow App(sf::VideoMode(800, 600), PRJ_NAME);

    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }
        App.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        App.clear();
    }
}
