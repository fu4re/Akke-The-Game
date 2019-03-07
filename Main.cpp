#include "Game.h"
#include "ResourceHolder.h"

#include <iostream>

namespace Textures //неймспейс с id текстурок
{
	enum ID
	{
		Landscape, 
		Airplane, 
	};
}

int main()
{
	Game Game;
	Game.run();

	ResourceHolder<sf::Texture, Textures::ID> textures;
	try												// начало блока исключения 
	{
		textures.load(Textures::Landscape, "///"); // загрузка текстуры
		textures.load(Textures::Airplane, "///");
	}
	catch (std::runtime_error& e) // обработка исключений (runtime_error - определяет тип объекта, который будет выброшен как исключение, сообщает об ошибках, которые выходят за рамки программы и не могут быть предсказаны компилятором)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// применяем текстуру на спрайт
	sf::Sprite landscape(textures.get(Textures::Landscape));
	sf::Sprite airplane(textures.get(Textures::Airplane));
	//airplane.setPosition(200.f, 200.f); //задаем позицию основному объекту

	while (window.isOpen())
	{
		//clear
		//draw
		//display		
	}
}