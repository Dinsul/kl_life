#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include <chrono>

#include "game.h"
#include "settings.h"
#include "logger.h"
#include "universe.h"

Game::Game(sf::RenderWindow &window, CGL::Universe &universe)
    : _isPlaying(false),
      _isPause(true),
      _window(window),
      _universe(universe),
      _settings(CGL::Settings::get())
{
    _updateTimer    = std::make_unique<sf::Clock>();
    _drawTimer      = std::make_unique<sf::Clock>();
    _gameTime       = std::make_unique<sf::Clock>();
}

Game::~Game()
{
}

void Game::run()
{
    _updateTimer->restart();
    _drawTimer->restart();
    _gameTime->restart();

    _isPlaying = true;

    while (_isPlaying)
    {
        _getPlayersControl();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (!_isPause)
        {
            if (_updateTimer->getElapsedTime().asMilliseconds() >= _settings.generationPeriod)
            {
                _universe.nextGeneration();

                _updateTimer->restart();
            }
        }


        if (_drawTimer->getElapsedTime().asMilliseconds() >= _settings.drawPeriod)
        {
            _doDraw();
            _drawTimer->restart();
        }
    }
}


void Game::stop()
{
    _isPlaying = false;
}

void Game::_doDraw()
{
    _window.clear();

    _drawMainScreen();
    _drawStatus();

    _window.display();
}


void Game::_drawMainScreen()
{
//    sf::Text text;
//    sf::Font font;
//    sf::RectangleShape rect(static_cast<sf::Vector2f>(_window.getSize()));

//    rect.setFillColor(sf::Color(0, 0, 0, 100));

//    char string[] = "pause";

////    font.loadFromFile(FONT_PATH);

//    text.setFont(font);
//    text.setCharacterSize(25);
//    text.setFillColor(sf::Color::White);
//    text.setPosition(2, 2);
//    text.setString(string);

//    _window.draw(rect);
//    _window.draw(text);
    sf::RectangleShape backGround;

    backGround.setFillColor(sf::Color{240, 240, 255});
    backGround.setSize(sf::Vector2f{780,580});

    backGround.setPosition(_settings.cellSize, _settings.cellSize);

    _window.draw(backGround);

    _universe.draw(_window);
}

void Game::_drawStatus()
{
    sf::RectangleShape line;

    line.setFillColor(sf::Color{0,0,255});
    line.setOutlineColor(sf::Color{0,0,255});

    line.setSize(sf::Vector2f{800.f, 1.f});
    for (int y = 10; y < 600; y += 10) {
        line.setPosition(0.f, y);

        _window.draw(line);
    }

    line.setSize(sf::Vector2f{1.f, 600.f});
    for (int x = 10; x < 800; x += 10) {
        line.setPosition(x, 0.f);

        _window.draw(line);
    }
}



void Game::_getPlayersControl()
{
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            stop();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if      (event.key.code == sf::Keyboard::Key::Space)
            {
                _isPause = !_isPause;
                _universe.refresh();
            }
            else if (event.key.code == sf::Keyboard::Key::Escape)
            {
                stop();
            }
            else if (event.key.code == sf::Keyboard::Key::Delete ||
                     event.key.code == sf::Keyboard::Key::BackSpace)
            {
                _universe.clear();
                _universe.refresh();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {

            if      (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                _holdToDraw = true;
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                _holdToErase = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            _holdToDraw  = false;
            _holdToErase = false;

            if      (event.mouseButton.button == sf::Mouse::Button::Left&&
                     event.mouseButton.x > 0 &&
                     event.mouseButton.y > 0 &&
                     event.mouseButton.x < _universe.width() * _settings.cellSize &&
                     event.mouseButton.y < _universe.height() * _settings.cellSize )
            {
                _universe.addCell(event.mouseButton.x / _settings.cellSize,
                                  event.mouseButton.y / _settings.cellSize);
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right&&
                     event.mouseButton.x > 0 &&
                     event.mouseButton.y > 0 &&
                     event.mouseButton.x < _universe.width() * _settings.cellSize &&
                     event.mouseButton.y < _universe.height() * _settings.cellSize )
            {
                _universe.killCell(event.mouseButton.x / _settings.cellSize,
                                   event.mouseButton.y / _settings.cellSize);
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            if      (_holdToDraw &&
                     event.mouseMove.x > 0 &&
                     event.mouseMove.y > 0 &&
                     event.mouseMove.x < _universe.width() * _settings.cellSize &&
                     event.mouseMove.y < _universe.height() * _settings.cellSize )
            {
                _universe.addCell(event.mouseMove.x / _settings.cellSize,
                                  event.mouseMove.y / _settings.cellSize);
            }
            else if (_holdToErase &&
                     event.mouseMove.x > 0 &&
                     event.mouseMove.y > 0 &&
                     event.mouseMove.x < _universe.width() * _settings.cellSize &&
                     event.mouseMove.y < _universe.height() * _settings.cellSize )
            {
                _universe.killCell(event.mouseMove.x / _settings.cellSize,
                                   event.mouseMove.y / _settings.cellSize);
            }
        }
    }
}

