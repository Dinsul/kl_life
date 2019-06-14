#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <thread>
#include <chrono>

#include <algorithm>
#include <list>

#include "game.h"
#include "settings.h"
#include "logger.h"
#include "universe.h"
#include "info.h"

Game::Game(sf::RenderWindow &window, cgl::Universe &universe)
    : _isPlaying(false),
      _isPause(true),
      _isEnd(false),
      _smiles(cgl::Settings::get().smiles),
      _window(window),
      _universe(universe),
      _settings(cgl::Settings::get()),
      _mouseState(MouseState::normal)
{
    _updateTimer    = std::make_unique<sf::Clock>();
    _drawTimer      = std::make_unique<sf::Clock>();
    _gameTime       = std::make_unique<sf::Clock>();
    _viewMain       = std::make_unique<sf::View>();
    _viewMenu       = std::make_unique<sf::View>();
    _texture        = std::make_unique<sf::Texture>();

    if (!_texture->loadFromFile(DATA_DIR"lset.png"))
    {
        _smiles = false;
        cgl::Logger::error("Can not open texture file.");
    }
    else
    {
        _texture->setSmooth(true);
    }

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

    std::list<cgl::uniqList<cgl::Position> > history;

    while (_isPlaying)
    {
        _getPlayersControl();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (!_isPause)
        {
            if (_updateTimer->getElapsedTime().asMilliseconds() >= _settings.generationPeriod)
            {
                _universe.nextGeneration();

                auto curUniverse = _universe.inhabitants();

                if (std::find(history.begin(), history.end(), curUniverse) !=  history.end())
                {
                    _isPause = true;
                    _isEnd   = true;
                }
                else
                {
                    history.push_front(curUniverse);
                }

                if (history.size() > _settings.historyDeep)
                {
                    history.pop_back();
                }

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
    quick_trace();

    _window.setView(*_viewMain);
    _window.clear();

    _drawMainScreen();

    _window.setView(*_viewMenu);

    _drawStatus();

    _window.display();

    auto now = std::chrono::steady_clock::now();
    static decltype (now) old;

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(now - old);

    old = now;

    cgl::Logger::debug(cgl::makeStr("Time of draw", elapsed_us.count(), "µs"));
}


void Game::_drawMainScreen()
{
    auto cellSize = static_cast<float>(_settings.cellSize);
    auto width    = static_cast<float>(_universe.width()) * cellSize;
    auto height   = static_cast<float>(_universe.height()) * cellSize;

    sf::RectangleShape backGround;

    backGround.setFillColor(sf::Color{_settings.backGroundColor});
    backGround.setSize(sf::Vector2f{width - cellSize * 2, height - cellSize * 2});

    backGround.setPosition(cellSize, cellSize);

    _window.draw(backGround);

    if (_smiles)
    {
        sf::Sprite inhabitant{*_texture};
        inhabitant.setColor(sf::Color{_settings.inhabitantColor});

        for (auto & cell : _universe.inhabitants())
        {
            switch (cell.second)
            {
            case 1:
                inhabitant.setTextureRect({21, 1, 39, 19});
                break;

            case 2:
                inhabitant.setTextureRect({21, 21, 39, 39});
                break;

            case 3:
            case 4:
                inhabitant.setTextureRect({1, 1, 19, 19});
                break;

            default:
                inhabitant.setTextureRect({1, 21, 19, 39});
                break;
            }

            inhabitant.setPosition({static_cast<float>(cell.first.x * cellSize),
                                static_cast<float>(cell.first.y * cellSize)});

            inhabitant.setScale({cellSize / 18.f, cellSize / 18.f});

            _window.draw(inhabitant);
        }
    }
    else
    {
        sf::RectangleShape inhabitant;

        inhabitant.setFillColor(sf::Color{_settings.inhabitantColor});
        inhabitant.setSize(sf::Vector2f{cellSize, cellSize});

        for (auto & cell : _universe.inhabitants())
        {
            inhabitant.setPosition(cell.first.x * cellSize, cell.first.y * cellSize);

            _window.draw(inhabitant);
        }
    }


    if (_settings.cellSize > 4)
    {
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
    }
}

void Game::_drawStatus()
{
    sf::Text *text = new sf::Text();
    sf::Font *font = new sf::Font();


    if (!font->loadFromFile(FONTS_DIR"Casatus.ttf"))
    {
        delete font;
        delete text;

        cgl::Logger::error("Can not load font");
        return;
    }

    text->setFont(*font);

    text->setCharacterSize(20);
    text->setPosition(10, 25);
    text->setFillColor(sf::Color::White);
    text->setString(L"Управление:");

    _window.draw(*text);

    text->setCharacterSize(15);
    text->setPosition(10, 55);
    text->setFillColor(sf::Color{0xCFCFCFFF});
    text->setString(L"MouseLeft - оживить ячейку\n"
                    "MouseRight - убить ячейку\n"
                    "MouseMiddle - тащить поле мышкой\n\n"
                    "W\t- переместить поле вверх\n"
                    "A\t- переместить поле налево\n"
                    "S\t- переместить поле вниз\n"
                    "D\t- переместить поле направо\n"
                    "+\t- увеличить размер ячейки\n"
                    "-\t- уменьшить размер ячейки\n"
                    "Space\t- запустить/остановить\n"
                    "Enter - сделать один шаг эволюции\n"
                    "Delete или BackSpace - очистить\n"
                    "Escape\t- выйти\n"
                    );

    _window.draw(*text);

    if (_isEnd)
    {
        std::wstring msg = L"Все обитатели вымерли:";
        float offset;

        if (_universe.inhabitants().empty())
        {
            text->setFillColor(sf::Color::Red);
            msg = L"Все обитатели вымерли!";
            offset = 95;
        }
        else
        {
            text->setFillColor(sf::Color::Green);
            msg = L"Вы получили замкнутую систему";
            offset = 120;
        }

        text->setCharacterSize(25);
        text->setPosition(_viewMenu->getSize().x / 2 - 35, 270);
        text->setString(L"Конец");

        _window.draw(*text);

        text->setCharacterSize(15);
        text->setPosition(_viewMenu->getSize().x / 2 - offset, 300);
        text->setString(msg);

        _window.draw(*text);

    }
    else if (_isPause)
    {
        text->setCharacterSize(25);
        text->setPosition(_viewMenu->getSize().x / 2 - 33, 280);
        text->setFillColor(sf::Color::Green);
        text->setString(L"Пауза");

        _window.draw(*text);
    }
    else
    {
        text->setCharacterSize(25);
        text->setPosition(_viewMenu->getSize().x / 2 - 50, 280);
        text->setFillColor(sf::Color{0x1FFF1FFF});
        text->setString(L"Эволюция!");

        _window.draw(*text);
    }

    text->setCharacterSize(15);
    text->setPosition(10, 310);
    text->setFillColor(sf::Color{0xCFCFCFFF});

    std::wstring wstatus;
    wstatus.append(L"\nКолличество обитателей: ");
    wstatus.append(std::to_wstring(_universe.inhabitants().size()));

    wstatus.append(L"\nРазмер поля: ");
    wstatus.append(std::to_wstring(_universe.width()));
    wstatus.append(L"×");
    wstatus.append(std::to_wstring(_universe.height()));

    if (_settings.cycled)
    {
        wstatus.append(L" замкнуто");
    }

    wstatus.append(L"\nРазмер ячейки: ");
    wstatus.append(std::to_wstring(_settings.cellSize));

    std::wstringstream evFrequency;

    evFrequency.setf(std::ios::fixed);
    evFrequency.precision(2);
    evFrequency << L"\nСкорость эволюции: " << 1000. / _settings.generationPeriod
                << L" пок-й/с";

    wstatus.append(evFrequency.str());

    text->setString(wstatus);

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

            case sf::Keyboard::Key::Enter:
                _universe.nextGeneration();
                _isPause = true;
                _universe.refresh();
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

            case sf::Keyboard::Key::PageUp:
                if (_settings.generationPeriod > 11)
                {
                    _settings.generationPeriod -= 5;
                }
                break;

            case sf::Keyboard::Key::PageDown:
                if (_settings.generationPeriod < (100000 - 10))
                {
                    _settings.generationPeriod += 5;
                }
                break;

            case sf::Keyboard::Key::Subtract:
                if (_settings.cellSize > 4)
                {
                    auto center = _viewMain->getCenter();

                    _settings.cellSize -= 1;

                    center.x = (center.x / (_settings.cellSize + 1)) * _settings.cellSize;
                    center.y = (center.y / (_settings.cellSize + 1)) * _settings.cellSize;
                    _viewMain->setCenter(center);
                }
                break;

            case sf::Keyboard::Key::Add:
                if (_settings.cellSize < 30)
                {
                    auto center = _viewMain->getCenter();

                    _settings.cellSize += 1;

                    center.x = (center.x / (_settings.cellSize - 1)) * _settings.cellSize;
                    center.y = (center.y / (_settings.cellSize - 1)) * _settings.cellSize;
                    _viewMain->setCenter(center);
                }
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Button::Left:
                _mouseState = MouseState::pushCell;
                _isEnd      = false;
                break;

            case sf::Mouse::Button::Middle:
                _mouseState = MouseState::moveMap;
                break;

            case sf::Mouse::Button::Right:
                _mouseState = MouseState::popCell;
                _isEnd      = false;
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            _mouseState = MouseState::normal;

            if (event.mouseButton.x < _viewMain->getSize().x)
            {
                auto x = static_cast<int>((_viewMain->getCenter().x + event.mouseButton.x
                                           - _window.getSize().x / 2) + _viewMenu->getSize().x / 2) / _settings.cellSize;

                auto y = static_cast<int>(_viewMain->getCenter().y + event.mouseButton.y
                                          - _window.getSize().y / 2) / _settings.cellSize;

                if ( x > 0 && y > 0 && x < _universe.width() && y < _universe.height())
                {
                    switch (event.mouseButton.button)
                    {
                    case sf::Mouse::Button::Left:
                        _universe.addCell(x, y);
                        break;

                    case sf::Mouse::Button::Right:
                        _universe.killCell(x, y);
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            static float oldX;
            static float oldY;

            if (_mouseState != MouseState::normal)
            {
                auto x = static_cast<int>((_viewMain->getCenter().x + event.mouseMove.x
                                           - _window.getSize().x / 2) + _viewMenu->getSize().x / 2) / _settings.cellSize;

                auto y = static_cast<int>(_viewMain->getCenter().y + event.mouseMove.y
                                          - _window.getSize().y / 2) / _settings.cellSize;

                if (event.mouseMove.x < _viewMain->getSize().x &&
                        x > 0 && y > 0 && x < _universe.width() && y < _universe.height())
                {
                    switch (_mouseState)
                    {
                    case MouseState::pushCell:
                        _universe.addCell(x, y);
                        break;

                    case MouseState::popCell:
                        _universe.killCell(x, y);
                        break;

                    case MouseState::moveMap:
                        _viewMain->move(oldX - event.mouseMove.x, oldY - event.mouseMove.y);
                        break;

                    default:
                        break;
                    }
                }
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

