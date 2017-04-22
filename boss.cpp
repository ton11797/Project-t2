#include "SFML/Graphics.hpp"
#include <iostream>
#include "Menu.h"
#include <SFML/Window.hpp>

using namespace std;



Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
    menu[0].setCharacterSize(40);
	menu[0].setFont(font);
	menu[0].setStyle(sf::Text::Bold);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("Register");

	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setCharacterSize(40);
	menu[1].setFont(font);
	menu[1].setStyle(sf::Text::Bold);
	menu[1].setColor(sf::Color(232,163,12));
	menu[1].setString("Login");
	menu[1].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.1));

	menu[2].setCharacterSize(40);
	menu[2].setFont(font);
	menu[2].setStyle(sf::Text::Bold);
	menu[2].setColor(sf::Color(232,163,12));
	menu[2].setString("Ranking");
	menu[2].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.2));

	menu[3].setCharacterSize(40);
	menu[3].setFont(font);
	menu[3].setStyle(sf::Text::Bold);
	menu[3].setColor(sf::Color(232,163,12));
	menu[3].setString("Exit");
	menu[3].setPosition(sf::Vector2f(width / 2, height /(MAX_NUMBER_OF_ITEMS + 1) * 1.3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setColor(sf::Color(232,163,12));
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color(232,163,12));
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
int main()
{
    sf::Texture texture;
    if(!texture.loadFromFile("menu.jpg"));
    sf::Sprite background(texture);

	sf::RenderWindow window(sf::VideoMode(1500, 700), "Stardew walley!!");

	Menu menu(window.getSize().x, (window.getSize().y)/0.35);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					menu.MoveUp();
					break;

				case sf::Keyboard::S:
					menu.MoveDown();
					break;
                case sf::Keyboard::Down:
					menu.MoveDown();
					break;
                case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Register button has been pressed" << std::endl;
						break;
					case 1:
						std::cout << "Login button has been pressed" << std::endl;
						break;
                    case 2:
                        std::cout << "Ranking button has been pressed "<< std::endl;
                        break;
					case 3:
						window.close();
						break;
					}

					break;
				}

				break;
			case sf::Event::Closed:
				window.close();

				break;

			}
		}

		window.clear();
        window.draw(background);
		menu.draw(window);

		window.display();
	}
}
