# Игра "Жизнь"

Правила игры взяты из wikipedia
https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

## Установка и загрузка

Игра будет доступна в виде исходников на gitbub и в виде deb пакета на bintray.
Тестовые сборки для других ОС будут, но куда размещать ещё не знаю.

## Управление

MouseLeft   - добавить (оживить) ячейку
MouseRight  - убрать (убить) ячейку
MouseMiddle - пермещение поля мышкой
W, A, S, D  - пермещение поля вверх, налево, вниз, направо соответственно
Space       - запустить/остановить процесс
Escape      - выйти
Delete или
BackSpace   - очистить вселенную

## Зависимости

Для успешной сборки понадобится manager пакетов conan версии 1.10 и
cmake версии 3.10. На более ранних версиях тестирование не проводилось.

## Поддержка

Если у вас возникли сложности или вопросы пишите мне на e-mail: dinsul@rambler.ru

## Документация

Пользовательскую документацию можно получить по [ссылке](). TODO сделать страничку на gitbub

Документацию API можно получить из исходных кодов пакета с помощью утилиты
[Doxygen][].
