#include "Game.h"
#include "ResourceHolder.h"

#include <iostream>

namespace Textures //��������� � id ���������
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
	try												// ������ ����� ���������� 
	{
		textures.load(Textures::Landscape, "///"); // �������� ��������
		textures.load(Textures::Airplane, "///");
	}
	catch (std::runtime_error& e) // ��������� ���������� (runtime_error - ���������� ��� �������, ������� ����� �������� ��� ����������, �������� �� �������, ������� ������� �� ����� ��������� � �� ����� ���� ����������� ������������)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// ��������� �������� �� ������
	sf::Sprite landscape(textures.get(Textures::Landscape));
	sf::Sprite airplane(textures.get(Textures::Airplane));
	//airplane.setPosition(200.f, 200.f); //������ ������� ��������� �������

	while (window.isOpen())
	{
		//clear
		//draw
		//display		
	}
}