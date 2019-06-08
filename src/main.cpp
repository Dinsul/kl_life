#include <iostream>
#include <SFML/Graphics.hpp>

#include "info.h"
#include "logger.h"
#include "settings.h"

#include <thread>
#include <chrono>


#include "life_types.hpp"
#include "simpleuniverse.h"

int main(/*int argc, char* argv[]*/)
{
    auto &settings       = CGL::Settings::get();
    settings.logLevel    = CGL::Settings::LogLevel::debug;
    settings.logToStdout = true;

    CGL::Logger::info(CGL::makeStr(PRJ_NAME, "Version", PRJ_VERSION));

    sf::RenderWindow App(sf::VideoMode(800, 600), PRJ_NAME);

    CGL::SimpleUniverse univ;

    univ.addCell({34,21});
    univ.addCell({34,22});
    univ.addCell({34,23});

    univ.addCell({34,23});
    univ.addCell({35,23});
    univ.addCell({36,23});
    univ.addCell({37,23});
    univ.addCell({38,23});

    univ.addCell({39,22});
    univ.addCell({39,20});
    univ.addCell({37,19});
    univ.addCell({35,20});


    while (App.isOpen()) {
        sf::Event Event;
        while (App.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed)
                App.close();
        }

        App.clear();


        sf::RectangleShape rect;

        rect.setFillColor(sf::Color{255, 255, 255});
        rect.setSize(sf::Vector2f{780,580});

        rect.setPosition(10, 10);

        App.draw(rect);

        univ.draw(App);

        sf::RectangleShape line;

        line.setFillColor(sf::Color{0,0,255});
        line.setOutlineColor(sf::Color{0,0,255});

        line.setSize(sf::Vector2f{800.f, 1.f});
        for (int y = 10; y < 600; y += 10) {
            line.setPosition(0.f, y);

            App.draw(line);
        }

        line.setSize(sf::Vector2f{1.f, 600.f});
        for (int x = 10; x < 800; x += 10) {
            line.setPosition(x, 0.f);

            App.draw(line);
        }

        App.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        univ.nextGeneration();
    }

    settings.save();
}
