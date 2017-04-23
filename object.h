#ifndef OBJECT_H
#define OBJECT_H
#include "Player.h"
#include "collider.h"
#include<SFML/Graphics.hpp>
#include <iostream>
class object
{
    public:
        object(sf::Texture* texture,sf::Vector2f sizee,sf::Vector2f position);
        virtual ~object();
        void Draw(sf::RenderWindow &window);
        collider getcollider(){return collider(body);}
        //void plantorbuild();

    protected:

    private:
        sf::RectangleShape body;
        //sf::Time timeobject;
        int typeobject;
        char nameobject[20];
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
object::object(sf::Texture* texture,sf::Vector2f sizee,sf::Vector2f position)//,sf::RenderWindow &window,int mapcheck[][])
{
    body.setSize(sizee);
    body.setOrigin(sizee/2.0f);
    body.setTexture(texture);
    body.setPosition(position);
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
void plant(sf::RenderWindow window,object seed,int mapcheck[][19])
{
   /* if(mapcheck[seed.getPosition().x/50][body.getPosition().y/50]==0)
    {
        window.draw(body);
        mapcheck[seed.getPosition().x/50][body.getPosition().y/50]==1;

    }*/
}
#endif // OBJECT_H
