#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
#include "select.h"
#include "Menu.h"
#include "inventory.h"
using namespace std;

int main()
{
    sf::RenderWindow window;
    inventory inv;
    inv.setmoney(100);
    float movespeed=0.2;
    sf::Texture playertexture,bg,Barn,dismoney;
    tex texx;
    window.create(sf::VideoMode(1900,950)," FARM EIEI ",sf::Style::Resize|sf::Style::Close);//Style คือ รูปแบบของดด้านบนที่เราต้องการ close จะมีปุ่มปิด
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
    dismoney.loadFromFile("resource/money.png");
    playertexture.loadFromFile("resource/she.png");
    player.setTexture(&playertexture);
    sf::Vector2u texturesize = playertexture.getSize();
    texturesize.x /=4;
    texturesize.y /=4;
    player.setTextureRect(sf::IntRect(texturesize.x *0,texturesize.y *0,texturesize.x,texturesize.y));
    animetion animation(&playertexture,sf::Vector2u(4,4),0.3f);
    float deltatime=0.0f;
    sf::Clock clock,clockforplant;
    sf::Time time,timeplant=sf::seconds(10);
    Barn.loadFromFile("resource/Barn.png");
    int turn=0;
    object Barnn(&Barn,sf::Vector2f(112.0f,128.0f),sf::Vector2f(1350.0f,150.0f),0,0,0,0,0);
    object cooparray[6] = {object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,410.0f),0,0,5.0f,9,10),
    object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,500.0f),0,0,5.0f,4,5)
     ,object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,590.0f),0,0,5.0f,4,5)
     ,object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,680.0f),0,0,5.0f,4,5)
     ,object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,770.0f),0,0,5.0f,4,5)
     ,object(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,860.0f),0,0,5.0f,4,5)};
    object moneydisplay(&dismoney,sf::Vector2f(400.0f,100.0f),*(inv.getmoney()));
    object kop(&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(0.0f,0.0f),0,0,0,0,0);
    object kop1(&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,0.0f),0,0,0,0,0);
    object kop2(&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(1900.0f,0.0f),0,0,0,0,0);
    object kop3(&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,950.0f),0,0,0,0,0);
    Player player1(&playertexture,sf::Vector2u(4,4),0.3f,sf::Vector2f(500.0f,600.0f));
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
        kop.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop1.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop2.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop3.getcollider().checkcollider(player1.getcollider(),1.0f);
        moneydisplay.getcollider().checkcollider(player1.getcollider(),1.0f);
        for(int j=0;j<6;j++){
            cooparray[j].plantorbuild(player1,texx.textarray,timeplant,clockforplant,*(inv.getmoney()));
        }
        window.draw(bgg);
        Barnn.Draw(window);
        kop.Draw(window);
        kop1.Draw(window);
        kop2.Draw(window);
        kop3.Draw(window);
        for(int j=0;j<6;j++){
            cooparray[j].Draw(window);
        }
        player1.Draw(window);
        moneydisplay.Draw(window,*(inv.getmoney()));
        window.display();
        turn++;
    }
	return 0;
}
