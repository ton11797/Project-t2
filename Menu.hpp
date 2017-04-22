#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }
    sf::Font font;
private:
	int selectedItemIndex;

	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

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

void getuserinput(sf::RenderWindow &window,char *out,sf::Texture &texture)
{
    int n=0;
    sf::String sentence;
    sf::Text username;
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Sprite background(texture);
    username.setFont(font);
    username.setCharacterSize(24);
    username.setFillColor(sf::Color::White);
    while (window.isOpen()&&n==0)
    {
        sf::Event eventrg;
        while (window.pollEvent(eventrg))
        {
            switch(eventrg.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(eventrg.key.code == sf::Keyboard::Return)
                {
                    n++;
                    break;
                }
            case sf::Event::TextEntered:
                if(eventrg.text.unicode == 59 && sentence.getSize()>0)
                {
                    sentence.erase(sentence.getSize()-1,sentence.getSize());
                }
                else if((eventrg.text.unicode >= 48 && eventrg.text.unicode <= 57)||(eventrg.text.unicode >= 65 && eventrg.text.unicode <= 90)||(eventrg.text.unicode >= 97 && eventrg.text.unicode <= 122))
                {
                    sentence += static_cast<char>(eventrg.text.unicode);
                }
                username.setString(sentence);
            }
            window.clear();
            window.draw(background);
            username.setPosition(600,280);
            window.draw(username);
            window.display();
        }

    }
    strcpy(out,sentence.toAnsiString().c_str());
}
