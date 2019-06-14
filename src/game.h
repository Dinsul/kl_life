#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <memory>

namespace sf {
class RenderWindow;
class Clock;
class View;
class Texture;
}

namespace cgl {
class Universe;
class Settings;
}

class Game
{
private:
    bool _isPlaying;
    bool _isPause;
    bool _isEnd;
    bool _smiles;

    sf::RenderWindow &_window;
    cgl::Universe    &_universe;
    cgl::Settings    &_settings;

    enum class MouseState {
        normal,
        pushCell,
        popCell,
        moveMap
    }_mouseState;

    std::unique_ptr<sf::Clock> _updateTimer;
    std::unique_ptr<sf::Clock> _drawTimer;
    std::unique_ptr<sf::Clock> _gameTime;
    std::unique_ptr<sf::View>  _viewMain;
    std::unique_ptr<sf::View>  _viewMenu;
    std::unique_ptr<sf::Texture>  _texture;


    void _doDraw(void);

    void _drawMainScreen();
    void _drawStatus();

    void _getPlayersControl();
    void _viewSetup();

public:
    Game(sf::RenderWindow &window, cgl::Universe &universe);
    ~Game();

    void run();
    void stop();
};

#endif // GAME_H
