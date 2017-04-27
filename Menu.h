#pragma once
#include "SFML/Graphics.hpp"
#include "tcp.hpp"
#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int open(sf::RenderWindow &window,char *userin,char *passin,int *userdatain);
	int GetPressedItem() { return selectedItemIndex; }
    sf::Font font;
private:
	int selectedItemIndex;
    char type[200],re[200];
    int *userdata,num;
	tcp *tcpsocket;
    char *user,*pass;
    sf::Texture texture,usertx,passtx,nouser,passworng,sameuser,registered,blank,cantconnect;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Sprite background;
};

