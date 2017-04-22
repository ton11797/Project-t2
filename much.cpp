#include <iostream>
#include <string.h>
#include "split.h"
#include <SFML/Graphics.hpp>
#include "animetion.h"
using namespace std;

int main()
{
    /*ll a;
    node *t;
    char wordtest[100]={'s','u','g',',','k','u','y',',','s','c','c',',','s','c',',','s','h',',','f','y','p',',','t','y','u'},data[100];
    split(wordtest);*/
    sf::RenderWindow window;
     sf::Texture playertexture,bg;
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
                case sf::Event::Resized:
                    cout<<"New window width="<<Event.size.width<< "New window height="<<Event.size.height<<endl;
                    break;
                case sf::Event::TextEntered:
                    if(Event.text.unicode<128)
                    {
                        printf("%c",Event.text.unicode);
                    }
            }

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player.move(-movespeed,0.0f);
            animation.update(1,deltatime);
            player.setTextureRect(animation.uvRect);
            //player.getPoint.x();
            //position=player.getPosition().x;
            //cout<<player.getPosition();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player.move(0.0f,+movespeed);
            animation.update(0,deltatime);
            player.setTextureRect(animation.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player.move(movespeed,0.0f);
            animation.update(2,deltatime);
            player.setTextureRect(animation.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player.move(0.0f,-movespeed);
            animation.update(3,deltatime);
            player.setTextureRect(animation.uvRect);
        } //keyboard input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            cout<<"X = "<<static_cast<int>(player.getPosition().x/50)<<" Y = "<<static_cast<int>(player.getPosition().y/50)<<endl;
            //เดี่ยวมีปลูกผักนะ
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
        }
        window.clear(sf::Color(150,150,150));
        window.draw(bgg);
        window.draw(player);
        window.display();

    }
	return 0;
}
