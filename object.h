#ifndef OBJECT_H
#define OBJECT_H
#include "Player.h"
#include "collider.h"
#include<SFML/Graphics.hpp>
#include <iostream>
#include "select.h"
class object
{
    public:
        object(sf::Texture* textarrayin,sf::Vector2f sizee,sf::Vector2f position);
        object(sf::Texture* texture1,sf::Vector2f sizee,int money);
        virtual ~object();
        void Draw(sf::RenderWindow &window);
        void Draw(sf::RenderWindow &window,int money);
        collider getcollider(){return collider(body);}
    protected:
        sf::RectangleShape body;
    private:

        //char nameobject[20];
        sf::Text text1;
        sf::Font font;
        bool ismoney;


};
/*void plant(sf::RenderWindow window,int mapcheck[][],object seed)
{
    if(mapcheck[body.getPosition().x/50][body.getPosition().y/50]==0)
    {
        window.draw(body);
        mapcheck[body.getPosition().x/50][body.getPosition().y/50]==1;

    }
}*/
object:: object(sf::Texture *textarrayin,sf::Vector2f sizee,sf::Vector2f position){
    ismoney=0;
    body.setSize(sizee);
    body.setOrigin(sizee/2.0f);
    body.setTexture(&textarrayin[0]);
    body.setPosition(position);
}
object:: object(sf::Texture* texture1,sf::Vector2f sizee,int money)
{
    ismoney=1;
    char moneyy[20];
    sprintf(moneyy,"%s%d","Money $ ",money);
        if(!font.loadFromFile("arial.ttf"))
        {
        }
        text1.setFont(font);
        text1.setCharacterSize(30);
        text1.setString(moneyy);
        text1.setColor(sf::Color::Black);
        text1.setPosition(sf::Vector2f(40.0f,45.0f));

    body.setSize(sizee);
    body.setPosition(sf::Vector2f(200.0f,50.0f));
    body.setOrigin(sizee/2.0f);
    body.setTexture(texture1);

}
void object::Draw(sf::RenderWindow &window,int money){
    char moneyy[20];
    sprintf(moneyy,"%s%d","Money $ ",money);
    text1.setString(moneyy);
    window.draw(body);
    window.draw(text1);
}
void object::Draw(sf::RenderWindow &window)
{
   window.draw(body);
}
object::~object()
{
    //dtor
}


class plantob:public object{
private:
    float *timeforplant;
    int full;
    int type;
    int firsttime;
    float timedoing;
    int *priceobjecttoplant;
    int *priceobjecttosell;
    char data[100];
    float timecheck;
public:
    char* getdata();
    plantob(sf::Texture *textarrayin,sf::Vector2f sizee,sf::Vector2f position,int fullnumber,int first,float *timef,int *priceplant,int *pricesell);
    void plantorbuild(Player player,sf::Texture *textarrayin,sf::Time timep,sf::Clock clockp,int *money,int *inv);
    void loaddata(int typein,sf::Time timep,sf::Clock clockp,sf::Texture *textarrayin);
};
void plantob::loaddata(int typein,sf::Time timep,sf::Clock clockp,sf::Texture *textarrayin){
    if(typein!=-1){
    full=1;
    type=typein;
    firsttime=1;
    timep=clockp.getElapsedTime();
    body.setTexture(&textarrayin[1+type*2]);
    timedoing=timep.asSeconds();
    }
}
plantob::plantob(sf::Texture *textarrayin,sf::Vector2f sizee,sf::Vector2f position,int fullnumber,int first,float *timef,int *priceplant,int *pricesell):object(textarrayin,sizee,position){
    type=-1;
    timecheck=0;
    full=fullnumber;
    timeforplant=timef;
    firsttime=first;
    priceobjecttoplant=priceplant;
    priceobjecttosell=pricesell;
}
void plantob::plantorbuild(Player player,sf::Texture *textarrayin,sf::Time timep,sf::Clock clockp,int *money,int *inv)
{
    if(type!=-1){
     timep=clockp.getElapsedTime();
            timecheck=timep.asSeconds();
            if(timeforplant[type]<=(timecheck-timedoing)&&full==1)
            {
                body.setTexture(&textarrayin[2+type*2]);
            }
    }
if(getcollider().checkcolliderforplant(player.getcollider()))
{
        int ped=0;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)&&full==0)
    {
        type=0;
        ped++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)&&full==0)
    {
        type=1;
        ped++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)&&full==0)
    {
        type=2;
        ped++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)&&full==0)
    {
        type=3;
        ped++;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)&&full==0)
    {
        type=4;
        ped++;
    }
        if(ped!=0&&full==0)
        {
            if(firsttime==0&&((*money-priceobjecttoplant[type])>=0))
            {
                timep=clockp.getElapsedTime();
                body.setTexture(&textarrayin[1+type*2]);
                full=1;
                timedoing=timep.asSeconds();
                firsttime=1;
               *money-=priceobjecttoplant[type];
            }

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&full==1)
        {
            timep=clockp.getElapsedTime();
            timecheck=timep.asSeconds();
            if(timeforplant[type]<=(timecheck-timedoing))
            {
                body.setTexture(&textarrayin[0]);
                full=0;
                firsttime=0;
                 *money+=priceobjecttosell[type];
                 inv[type]+=1;
                type=-1;
            }

        }
}
}

char* plantob::getdata(){
    sprintf(data, "/%d",type);
    return data;
}

#endif // OBJECT_H
