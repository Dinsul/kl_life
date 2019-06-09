#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include <memory>

namespace sf {
class RenderWindow;
class Clock;
}

namespace CGL {
class Universe;
class Settings;
}

class Game
{
private:
    bool _isPlaying;
    bool _isPause;

    sf::RenderWindow &_window;
    CGL::Universe    &_universe;
    CGL::Settings    &_settings;

    std::unique_ptr<sf::Clock> _updateTimer;
    std::unique_ptr<sf::Clock> _drawTimer;
    std::unique_ptr<sf::Clock> _gameTime;

    void _doDraw(void);

    void _drawMainScreen();
    void _drawStatus();

    void _getPlayersControl();


    bool _holdToDraw;
    bool _holdToErase;

public:
    Game(sf::RenderWindow &window, CGL::Universe &universe);
    ~Game();

    void run();
    void stop();
};

#endif // GAME_H
