#include <iostream>
#include <string.h>
#include "split.h"
#include <SFML/Graphics.hpp>
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
using namespace std;

int main()
{
    /*ll a;
    node *t;
    char wordtest[100]={'s','u','g',',','k','u','y',',','s','c','c',',','s','c',',','s','h',',','f','y','p',',','t','y','u'},data[100];
    split(wordtest);*/
    //coliider col(&player1);
    sf::RenderWindow window;
     sf::Texture playertexture,bg,cat;
     sf::Vector2i position;
    window.create(sf::VideoMode(1900,950)," FARM EIEI ",sf::Style::Resize|sf::Style::Close);//Style คือ รูปแบบของดด้านบนที่เราต้องการ close จะมีปุ่มปิด
    sf::Vector2u size(640,480);
    float movespeed=1;
    //window.setSize(sf::Vector2u(600,600));//set ขนาดหน้าจอที่เราต้องการให้ขึ้น ต้องใช้ Vector2u
    window.setTitle("MUCHU");//set ชื่อข้างบนที่เราจะให้ขึ้น
    window.setPosition(sf::Vector2i(0,0));//set ตำเเหน่งที่หน้าต่างวินโดจะเปิดมา ต้องใช้ vector2i
    sf::RectangleShape player(sf::Vector2f(50.0f,70.0f));
    //player.setFillColor(sf::Color::Red);
    player.setOrigin(50.0f,50.0f);
    player.setPosition(500.0f,500.0f);
    bg.loadFromFile("map.jpg");
    sf::Sprite bgg(bg);
    bgg.setTexture(bg);
    //bgg.scale(2,2);
    bgg.setPosition(0,0);
    playertexture.loadFromFile("she.png");
    player.setTexture(&playertexture);
    sf::Vector2u texturesize = playertexture.getSize();
    texturesize.x /=4;
    texturesize.y /=4;
    player.setTextureRect(sf::IntRect(texturesize.x *0,texturesize.y *0,texturesize.x,texturesize.y));
    animetion animation(&playertexture,sf::Vector2u(4,4),0.3f);
    float deltatime=0.0f;
    sf::Clock clock;
    sf::Time time;
    int turn=0;
    cat.loadFromFile("cat.jpg");
    object ob1(&cat,sf::Vector2f(100.0f,200.0f),sf::Vector2f(900.0f,250.0f));
    object ob2(&cat,sf::Vector2f(100.0f,200.0f),sf::Vector2f(1100.0f,500.0f));
    Player player1(&playertexture,sf::Vector2u(4,4),0.3f,sf::Vector2f(500.0f,600.0f));
    Player player2(&playertexture,sf::Vector2u(4,4),0.3f,sf::Vector2f(500.0f,500.0f));
    while (window.isOpen())
    {
       deltatime=clock.restart().asSeconds();
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch(Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::TextEntered:
                    if(Event.text.unicode<128)
                    {
                        printf("%c",Event.text.unicode);
                    }
            }

        }
        player1.update(deltatime,movespeed,turn);
        ob1.getcollider().checkcollider(player1.getcollider(),1.0f);
        ob2.getcollider().checkcollider(player1.getcollider(),0.9f);
        window.clear(sf::Color(150,150,150));
        window.draw(bgg);
        ob1.Draw(window);
        ob2.Draw(window);
        player1.Draw(window);
        window.display();
        turn++;

    }
	return 0;
}
