#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "animetion.h"
#include "object.h"
#include "Player.h"
#include "collider.h"
#include "select.h"
using namespace std;

int main()
{
    /*ll a;
    node *t;
    char wordtest[100]={'s','u','g',',','k','u','y',',','s','c','c',',','s','c',',','s','h',',','f','y','p',',','t','y','u'},data[100];
    split(wordtest);*/
    //coliider col(&player1);
    sf::RenderWindow window;
    int mapcheck[38][19],*moneypoint,money=100;
    moneypoint=&money;
     sf::Texture playertexture,bg,cat,Barn,coop;
     sf::Vector2i position;
     tex texx;
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
    cat.loadFromFile("cat.jpg");
    sf::Sprite bgg(bg);
    bgg.setTexture(bg);
    //bgg.scale(2,2);
    bgg.setPosition(0,0);
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
    coop.loadFromFile("resource/Coop.png");
    object Barnn(&Barn,&Barn,&Barn,sf::Vector2f(112.0f,128.0f),sf::Vector2f(1350.0f,150.0f),0,0,0,0,0);
    object Coop(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,410.0f),0,0,5.0f,9,10);
    object Coop1(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,500.0f),0,0,5.0f,4,5);
    object Coop2(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,590.0f),0,0,5.0f,4,5);
    object Coop3(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,680.0f),0,0,5.0f,4,5);
    object Coop4(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,770.0f),0,0,5.0f,4,5);
    object Coop5(texx.textarray,sf::Vector2f(80.0f,80.0f),sf::Vector2f(80.0f,860.0f),0,0,5.0f,4,5);
    object moneydisplay(&cat,&bg,&bg,sf::Vector2f(700.0f,200.0f),sf::Vector2f(0.0f,0.0f),0,0,0,0,0);
    object kop(&bg,&bg,&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(0.0f,0.0f),0,0,0,0,0);
    object kop1(&bg,&bg,&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,0.0f),0,0,0,0,0);
    object kop2(&bg,&bg,&bg,sf::Vector2f(10.0f,1950.0f),sf::Vector2f(1900.0f,0.0f),0,0,0,0,0);
    object kop3(&bg,&bg,&bg,sf::Vector2f(3950.0f,10.0f),sf::Vector2f(0.0f,950.0f),0,0,0,0,0);



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
        player1.update(deltatime,movespeed,turn,*moneypoint);
        //Barnn.getcollider().checkcollider(player1.getcollider(),1.0f);
       // Coop.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop1.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop2.getcollider().checkcollider(player1.getcollider(),1.0f);
        kop3.getcollider().checkcollider(player1.getcollider(),1.0f);
        moneydisplay.getcollider().checkcollider(player1.getcollider(),1.0f);
        Coop.getcollider().checkcolliderforplant(player1.getcollider());
        Coop.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
        Coop1.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
        Coop2.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
        Coop3.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
        Coop4.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
        Coop5.plantorbuild(player1,texx.textarray,timeplant,clockforplant,*moneypoint);
       /* if(Coop.getcollider().checkcolliderforplant(player1.getcollider()))
        {
            cout<<"true"<<endl;
        }*/
        //window.clear(sf::Color(150,150,150));
        window.draw(bgg);
        //cout<<"Time = "<<timeplant.asSeconds()<<endl;
        Barnn.Draw(window);
        //Barnn.plantorbuild(player1);
        //Coop.plantorbuild(player1);
        kop.Draw(window);
        kop1.Draw(window);
        kop2.Draw(window);
        kop3.Draw(window);
        Coop.Draw(window);
        Coop1.Draw(window);
        Coop2.Draw(window);
        Coop3.Draw(window);
        Coop4.Draw(window);
        Coop5.Draw(window);
        player1.Draw(window);
        moneydisplay.Draw(window);
        window.display();
        turn++;

    }
	return 0;
}
