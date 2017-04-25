#ifndef OBJECT_H
#define OBJECT_H
#include "Player.h"
#include "collider.h"
#include<SFML/Graphics.hpp>
#include <iostream>
class object
{
    public:
        object(sf::Texture* texture1,sf::Texture* texture2,sf::Texture* texture3,sf::Vector2f sizee,sf::Vector2f position,int fullnumber,float timef,int first);
        virtual ~object();
        void Draw(sf::RenderWindow &window);
        collider getcollider(){return collider(body);}
        void plantorbuild(Player player,sf::Texture* texture1,sf::Texture* texture2,sf::Texture* texture3,sf::Time timep,sf::Clock clockp);

    protected:

    private:
        sf::RectangleShape body;
        float timeforplant;
        int full;

        //char nameobject[20];
        int priceobject;
        float timetofinish;
        int firsttime;
        float timedoing;


};
/*void plant(sf::RenderWindow window,int mapcheck[][],object seed)
{
    if(mapcheck[body.getPosition().x/50][body.getPosition().y/50]==0)
    {
        window.draw(body);
        mapcheck[body.getPosition().x/50][body.getPosition().y/50]==1;

    }
}*/
object::object(sf::Texture* texture1,sf::Texture* texture2,sf::Texture* texture3,sf::Vector2f sizee,sf::Vector2f position,int fullnumber,float timef,int first)//,sf::RenderWindow &window,int mapcheck[][])
{
    body.setSize(sizee);
    body.setOrigin(sizee/2.0f);
    body.setTexture(texture1);
    body.setPosition(position);
    full=fullnumber;
    timeforplant=timef;
    firsttime=first;

    //window.draw(body);


}
void object::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}
object::~object()
{
    //dtor
}
void object::plantorbuild(Player player,sf::Texture* texture1,sf::Texture* texture2,sf::Texture* texture3,sf::Time timep,sf::Clock clockp)
{
    float timecheck;
     timep=clockp.getElapsedTime();
            timecheck=timep.asSeconds();
            if(timeforplant<=(timecheck-timedoing)&&full==1)
            {
                //cout<<"YOUR FUCKING PLANT READY TO COLLECT "<<endl;
                body.setTexture(texture3);
            }
if(getcollider().checkcolliderforplant(player.getcollider()))
{

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)&&full==0)
        {
            if(firsttime==0)
            {
                timep=clockp.getElapsedTime();
                body.setTexture(texture2);
                full=1;
                cout<<"FULL = "<<full<<endl;
                timedoing=timep.asSeconds();
                cout<<"Time = "<<timep.asSeconds()<<endl;
                cout<<"YOU HAVE PLANT YOUR FUCKING SEED "<<endl;
                firsttime=1;
            }

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&full==1)
        {
            timep=clockp.getElapsedTime();
            timecheck=timep.asSeconds();
            cout<<timecheck<<endl;
            if(timeforplant<=(timecheck-timedoing))
            {
                body.setTexture(texture1);
                full=0;
                cout<<"FULL = "<<full<<endl;
                firsttime=0;
                 cout<<"Time = "<<timep.asSeconds()<<endl;
                 cout<<"CONGRATULATION YOU GOT FUCKING PLANT FOR YOU "<<endl;
            }

        }
}

}
#endif // OBJECT_H
