#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game : private sf::NonCopyable //NonCopyable - ����� Game �� ������� �����������, ��������� ��� ����������� ����������� � �������� ������������
{
public:
	Game(); 
	void run(); //������ ���� � ������� �����

private:
	void processEvents(); // �������� �� ������ ������� � ����
	void update(sf::Time elapsedTime); // ������ �������� ��������, �� �����������
	void render(); //������ ����� � ��������

	void updateStat(sf::Time elapsedTime); //setString ��� ���������� ����� � �� ����������
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed); //����� ������ ������

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

