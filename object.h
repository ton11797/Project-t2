#ifndef OBJECT_H
#define OBJECT_H
#include "Player.h"
#include "collider.h"
#include<SFML/Graphics.hpp>
#include <iostream>
class object
{
    public:
        object(sf::Texture* texture1,sf::Texture* texture2,sf::Vector2f sizee,sf::Vector2f position,int fullnumber);
        virtual ~object();
        void Draw(sf::RenderWindow &window);
        collider getcollider(){return collider(body);}
        void plantorbuild(Player player,sf::Texture* texture1,sf::Texture* texture2);

    protected:

    private:
        sf::RectangleShape body;
        //sf::Time timeobject;
        int full;
        //char nameobject[20];
        int priceobject;
        float timetofinish;


};
/*void plant(sf::RenderWindow window,int mapcheck[][],object seed)
{
    if(mapcheck[body.getPosition().x/50][body.getPosition().y/50]==0)
    {
        window.draw(body);
        mapcheck[body.getPosition().x/50][body.getPosition().y/50]==1;

    }
}*/
object::object(sf::Texture* texture1,sf::Texture* texture2,sf::Vector2f sizee,sf::Vector2f position,int fullnumber)//,sf::RenderWindow &window,int mapcheck[][])
{
    body.setSize(sizee);
    body.setOrigin(sizee/2.0f);
    body.setTexture(texture1);
    body.setPosition(position);
    full=fullnumber;
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
void object::plantorbuild(Player player,sf::Texture* texture1,sf::Texture* texture2)
{

if(getcollider().checkcolliderforplant(player.getcollider()))
{
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)&&full==0)
        {
            //if(getcollider().checkcolliderforplant(player.getcollider()))
            //{

                body.setTexture(texture2);
                full=1;
                cout<<"FULL = "<<full<<endl;
            //}
            //if(full==1)
            //{
              //  body.setTexture(texture1);
                //full=0;
            //}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&full==1)
        {
            body.setTexture(texture1);
                full=0;
                cout<<"FULL = "<<full<<endl;
        }
}

}
#endif // OBJECT_H
