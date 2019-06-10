#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <thread>
#include <chrono>

#include "game.h"
#include "settings.h"
#include "logger.h"
#include "universe.h"

Game::Game(sf::RenderWindow &window, cgl::Universe &universe)
    : _isPlaying(false),
      _isPause(true),
      _window(window),
      _universe(universe),
      _settings(cgl::Settings::get()),
      _holdToDraw(false),
      _holdToErase(false),
      _holdToMove(false)
{
    _updateTimer    = std::make_unique<sf::Clock>();
    _drawTimer      = std::make_unique<sf::Clock>();
    _gameTime       = std::make_unique<sf::Clock>();
    _viewMain       = std::make_unique<sf::View>();
    _viewMenu       = std::make_unique<sf::View>();

    _viewSetup();
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
    _window.setView(*_viewMain);
    _window.clear();

    _drawMainScreen();

    _window.setView(*_viewMenu);

    _drawStatus();

    _window.display();
}


void Game::_drawMainScreen()
{
    quick_trace();
    auto begin = std::chrono::steady_clock::now();

    auto cellSize = static_cast<float>(_settings.cellSize);
    auto width    = static_cast<float>(_universe.width()) * cellSize;
    auto height   = static_cast<float>(_universe.height()) * cellSize;

    sf::RectangleShape backGround;

    backGround.setFillColor(sf::Color{_settings.backGroundColor});
    backGround.setSize(sf::Vector2f{width - cellSize * 2, height - cellSize * 2});

    backGround.setPosition(cellSize, cellSize);

    _window.draw(backGround);

    sf::RectangleShape inhabitant;

    inhabitant.setFillColor(sf::Color{_settings.inhabitantColor});
    inhabitant.setSize(sf::Vector2f{cellSize, cellSize});

    for (auto & cell : _universe.inhabitants())
    {
        inhabitant.setPosition(cell.first.x * cellSize, cell.first.y * cellSize);

        _window.draw(inhabitant);
    }

    sf::RectangleShape line;
    line.setFillColor(sf::Color{_settings.gridColor});

    line.setSize(sf::Vector2f{width, 1.f});
    for (float y = cellSize; y < height; y += cellSize) {
        line.setPosition(0.f, y);

        _window.draw(line);
    }

    line.setSize(sf::Vector2f{1.f, height});
    for (float x = cellSize; x < width; x += cellSize) {
        line.setPosition(x, 0.f);

        _window.draw(line);
    }
    auto end = std::chrono::steady_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

    cgl::Logger::debug(cgl::makeStr("Time of draw", elapsed_us.count(), "µs"));
}

void Game::_drawStatus()
{
//    sf::RectangleShape backGround;

//    backGround.setFillColor(sf::Color{_settings.backGroundColor});
//    backGround.setSize(sf::Vector2f{300, 300});
//    backGround.setPosition(0,0);
//    _window.draw(backGround);

    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();

    float linePos = 25;

    if (!font->loadFromFile("/home/denis/projects/life/data/Casatus.ttf"))
    {
        delete font;
        delete text;

        cgl::Logger::error("Can not load font");
        return;
    }

    text->setFont(*font);

    text->setCharacterSize(20);
    text->setPosition(10, linePos);
    text->setFillColor(sf::Color::White);
    text->setString(L"Управление:");

    _window.draw(*text);

    linePos += 30;
    text->setCharacterSize(15);
    text->setPosition(10, linePos);
    text->setFillColor(sf::Color{0xCFCFCFFF});
    text->setString(L"MouseLeft - оживить ячейку\n"
                     "MouseRight - убить ячейку\n"
                     "MouseMiddle - тащить поле мышкой\n\n"
                     "W\t- переместить поле вверх\n"
                     "A\t- переместить поле налево\n"
                     "S\t- переместить поле вниз\n"
                     "D\t- переместить поле направо\n"
                     "Space\t- запустить/остановить\n"
                     "Escape\t- выйти\n"
                     "Delete или\n"
                     "BackSpace\t- очистить\n");

    _window.draw(*text);

    delete font;
    delete text;
}



void Game::_getPlayersControl()
{
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Resized)
        {
            _viewSetup();
        }

        if (event.type == sf::Event::Closed)
        {
            stop();
        }

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            cgl::Settings::get().cellSize += event.mouseWheel.delta;
        }

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Key::Space:
                _isPause = !_isPause;
                _universe.refresh();
                break;

            case sf::Keyboard::Key::Escape:
                stop();
                break;

            case sf::Keyboard::Key::Delete:
            case sf::Keyboard::Key::BackSpace:
                _universe.clear();
                _universe.refresh();
                break;

            case sf::Keyboard::Key::W:
                _viewMain->move(0, 5.f);
                break;

            case sf::Keyboard::Key::S:
                _viewMain->move(0, -5.f);
                break;

            case sf::Keyboard::Key::A:
                _viewMain->move(5.f, 0);
                break;

            case sf::Keyboard::Key::D:
                _viewMain->move(-5.f, 0);
                break;

            default:
                break;
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
            else if (event.mouseButton.button == sf::Mouse::Button::Middle)
            {
                _holdToMove = true;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            _holdToDraw  = false;
            _holdToErase = false;
            _holdToMove  = false;

            auto x = static_cast<int>(_viewMain->getCenter().x + event.mouseButton.x
                                      - _window.getSize().x / 2) / _settings.cellSize;

            auto y = static_cast<int>(_viewMain->getCenter().y + event.mouseButton.y
                                      - _window.getSize().y / 2) / _settings.cellSize;

            if      (event.mouseButton.button == sf::Mouse::Button::Left &&
                     x > 0 && y > 0 &&
                     x < _universe.width() * _settings.cellSize &&
                     y < _universe.height() * _settings.cellSize )
            {
                _universe.addCell(x, y);
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right
                     && x > 0 && y > 0 &&
                     x < _universe.width() * _settings.cellSize &&
                     y < _universe.height() * _settings.cellSize)
            {
                _universe.killCell(x, y);
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            static float oldX;
            static float oldY;

            auto x = static_cast<int>(_viewMain->getCenter().x + event.mouseMove.x
                                      - _window.getSize().x / 2) / _settings.cellSize;

            auto y = static_cast<int>(_viewMain->getCenter().y + event.mouseMove.y
                                      - _window.getSize().y / 2) / _settings.cellSize;

            if      (_holdToDraw && x > 0 && y > 0 &&
                     x < _universe.width() * _settings.cellSize &&
                     y < _universe.height() * _settings.cellSize )
            {
                _universe.addCell(x, y);
            }
            else if (_holdToErase && x > 0 && y > 0 &&
                     x < _universe.width() * _settings.cellSize &&
                     y < _universe.height() * _settings.cellSize)
            {
                _universe.killCell(x, y);
            }
            else if (_holdToMove)
            {
                _viewMain->move(oldX - event.mouseMove.x, oldY - event.mouseMove.y);
            }

            oldX = event.mouseMove.x;
            oldY = event.mouseMove.y;
        }
    }
}

void Game::_viewSetup()
{

    float width  = static_cast<float>(_window.getSize().x);
    float height = static_cast<float>(_window.getSize().y);

    float mainFramePart = 0.7f;

    _viewMain->reset({0.f, 0.f, width * mainFramePart, height});
    _viewMenu->reset({0.f, 0.f, width - width * mainFramePart, height});

    _viewMain->setViewport({0.f, 0.f, mainFramePart, 1.f});
    _viewMenu->setViewport({mainFramePart, 0.f, 1.f - mainFramePart, 1.f});


    // Выставляем поле поцентру
    _viewMain->setCenter(_universe.width()  / 2 * _settings.cellSize,
                         _universe.height() / 2 * _settings.cellSize);
}

