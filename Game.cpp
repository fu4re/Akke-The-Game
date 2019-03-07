#include "Game.h"
#include "ToStringManager.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() : mWindow(sf::VideoMode(800, 600), "Akke the Game", sf::Style::Close) // двоеточие задает список инициализации для конструктора
, mTexture() //инициализация переменных с помощью конструктора копирования (пояснение Other.h 1.1)
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
		//load error(реализовать с помощью ImGui
	}

	mPlayer.setTexture(mTexture); //загружаем текстуру модели
	mPlayer.setPosition(100.f, 100.f); //задаем начальную позицию игрока

	mFont.loadFromFile("///"); //установка шрифта
	mStatText.setFont(mFont); //устанавливаем шрифт для статы
	mStatText.setPosition(5.f, 5.f); //позиция текста
	mStatText.setCharacterSize(10); //размер букв
}

void Game::run()
{
	sf::Clock clock; //переменная времени
	sf::Time timeSinceLastUpdate = sf::Time::Zero; //время между обновлениями ивентов
	
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart(); //рестарт часов
		timeSinceLastUpdate += elapsedTime; //складывается из прошедшего времени в общем
		while (timeSinceLastUpdate > TimePerFrame) //TimePerFrame - время от и до смены кадра(ивент)
		{
			timeSinceLastUpdate -= TimePerFrame;
															//РАЗОБРАТЬ
			processEvents();
			update(TimePerFrame);
		}

		updateStat(elapsedTime); //стата за прошедшее время
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
		case sf::Event::KeyPressed:						//если клавиша нажата, получаем ее бинарник и меняем значение переменной isPressed
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:							//если окно закрыто, передаем окну ф-цию закрытия
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);	//OX: Если тело движется в отриц. направлении, то от его вектора нужно ВЫЧЕСТЬ скорость модели											
	if (mIsMovingUp)					//OY: Если тело движется в отриц. направлении, то вектора нужно СЛОЖИТЬ
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * elapsedTime.asSeconds()); //заставляем двигаться модельку относительно времени в секундах
}

void Game::render()
{
	mWindow.clear(); //очищаем окно
	mWindow.draw(mPlayer); //отрисовываем модельку
	mWindow.draw(mStatText); //отрисовывваем текст со статой
	mWindow.display(); //отображем
}

void Game::updateStat(sf::Time elapsedTime)
{
	mStatUpdateTime += elapsedTime;
	mStatNumFrames += 1; //первый кадр

	if (mStatUpdateTime >= sf::seconds(1.0f))
	{
		//Задаем строку отрисованному тексту каждый апдейт фрейма, toStirng - конвертер в строку
		mStatText.setString("Frames / Second = " + toStirng(mStatNumFrames) + '\n' +
			"Time / Update = " + toString(mStatUpdateTime.asMicroseconds() / mStatNumFrames) + "us");

		mStatUpdateTime -= sf::seconds(1.0f);
		mStatNumFrames = 0; //обнуляем значения после setString
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed; //Если нажата клавиша, передаем то значение, которое isPressed
	if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}