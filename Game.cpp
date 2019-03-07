#include "Game.h"
#include "ToStringManager.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(800, 600), "Akke the Game", sf::Style::Close) // ��������� ������ ������ ������������� ��� ������������
, mTexture() //������������� ���������� � ������� ������������ ����������� (��������� Other.h 1.1)
, mPlayer()
, mFont()
, mStatText()
, mStatUpdateTime()
, mStatNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
{
	if (!mTexture.loadFromFile("///"))
	{
		//load error(����������� � ������� ImGui
	}

	mPlayer.setTexture(mTexture); //��������� �������� ������
	mPlayer.setPosition(100.f, 100.f); //������ ��������� ������� ������

	mFont.loadFromFile("///"); //��������� ������
	mStatText.setFont(mFont); //������������� ����� ��� �����
	mStatText.setPosition(5.f, 5.f); //������� ������
	mStatText.setCharacterSize(10); //������ ����
}

void Game::run()
{
	sf::Clock clock; //���������� �������
	sf::Time timeSinceLastUpdate = sf::Time::Zero; //����� ����� ������������ �������
	
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart(); //������� �����
		timeSinceLastUpdate += elapsedTime; //������������ �� ���������� ������� � �����
		while (timeSinceLastUpdate > TimePerFrame) //TimePerFrame - ����� �� � �� ����� �����(�����)
		{
			timeSinceLastUpdate -= TimePerFrame;
															//���������
			processEvents();
			update(TimePerFrame);
		}

		updateStat(elapsedTime); //����� �� ��������� �����
		render();
	}
}

void Game::processEvents() 
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:						//���� ������� ������, �������� �� �������� � ������ �������� ���������� isPressed
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:							//���� ���� �������, �������� ���� �-��� ��������
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);	//OX: ���� ���� �������� � �����. �����������, �� �� ��� ������� ����� ������� �������� ������											
	if (mIsMovingUp)					//OY: ���� ���� �������� � �����. �����������, �� ������� ����� �������
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * elapsedTime.asSeconds()); //���������� ��������� �������� ������������ ������� � ��������
}

void Game::render()
{
	mWindow.clear(); //������� ����
	mWindow.draw(mPlayer); //������������ ��������
	mWindow.draw(mStatText); //������������� ����� �� ������
	mWindow.display(); //���������
}

void Game::updateStat(sf::Time elapsedTime)
{
	mStatUpdateTime += elapsedTime;
	mStatNumFrames += 1; //������ ����

	if (mStatUpdateTime >= sf::seconds(1.0f))
	{
		//������ ������ ������������� ������ ������ ������ ������, toStirng - ��������� � ������
		mStatText.setString("Frames / Second = " + toStirng(mStatNumFrames) + '\n' +
			"Time / Update = " + toString(mStatUpdateTime.asMicroseconds() / mStatNumFrames) + "us");

		mStatUpdateTime -= sf::seconds(1.0f);
		mStatNumFrames = 0; //�������� �������� ����� setString
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed; //���� ������ �������, �������� �� ��������, ������� isPressed
	if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}