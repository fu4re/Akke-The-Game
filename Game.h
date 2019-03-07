#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable //NonCopyable - класс Game не полежит копированию, отключает его конструктор копирования и оператор присваивания
{
public:
	Game(); 
	void run(); //запуск окна и рестарт часов

private:
	void processEvents(); // отвечает за каждый процесс в окне
	void update(sf::Time elapsedTime); // апдейт текстуры модельки, ее перемещение
	void render(); //рендер статы и модельки

	void updateStat(sf::Time elapsedTime); //setString для переменной статы и ее обновление
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); //инпут клавиш игрока

private:
	static const float PlayerSpeed;
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;
	sf::Texture mTexture;
	sf::Sprite mPlayer;
	sf::Font mFont;
	sf::Text mStatText;
	sf::Time mStatUpdateTime;

	std::size_t mStatNumFrames;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
};
#endif // GAME_H

