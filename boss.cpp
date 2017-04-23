#include "SFML/Graphics.hpp"
#include <iostream>
#include <string.h>
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
    sf::Text username;
    username.setFont(menu.font);
    username.setCharacterSize(24);
    username.setFillColor(sf::Color::Red);
    username.setStyle(sf::Text::Bold | sf::Text::Underlined);
    sf::String sentence;
    sf::Text usernamein;
    int n=0;
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
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
                        n=0;
                        while (window.isOpen()&&n==0)
                        {
                            // check all the window's events that were triggered since the last iteration of the loop
                            sf::Event eventrg;
                            while (window.pollEvent(eventrg))
                            {
                                switch(eventrg.type){
                                case sf::Event::Closed:
                                    window.close();
                                    break;
                                case sf::Event::KeyPressed:
                                    if(eventrg.key.code == sf::Keyboard::Return){
                                        n++;
                                        break;
                                    }
                                case sf::Event::TextEntered:
                                    if(eventrg.text.unicode == 59 && sentence.getSize()>0){
                                        sentence.erase(sentence.getSize()-1,sentence.getSize());
                                    }else if((eventrg.text.unicode >= 48 && eventrg.text.unicode <= 57)||(eventrg.text.unicode >= 65 && eventrg.text.unicode <= 90)||(eventrg.text.unicode >= 97 && eventrg.text.unicode <= 122)){
                                        sentence += static_cast<char>(eventrg.text.unicode);
                                    }
                                    username.setString(sentence);
                                }
                                window.clear();
                                window.draw(username);
                                window.display();
                                // "close requested" event: we close the window
                            }

                        }
                        char data[100];
                        strcpy(data,sentence.toAnsiString().c_str());
                        cout<<data;
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
