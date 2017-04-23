#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
using namespace std;

class collider
{
    public:
        void Move(float dx,float dy){player.move(dx,dy);}
        collider(sf::RectangleShape &player);
        bool checkcollider(collider player,float push);
        sf::Vector2f Getposition(){return player.getPosition();}
        sf::Vector2f Gethalfsize(){return player.getSize()/2.0f;}
        virtual ~collider();


    protected:

    private:sf::RectangleShape &player;
};
bool  collider::checkcollider(collider player,float push)
{
    sf::Vector2f otherposition=player.Getposition();
    sf::Vector2f otherhalfsize=player.Gethalfsize();
    sf::Vector2f currentposition=Getposition();
    sf::Vector2f currenthalfsize=Gethalfsize();
    float checkx=otherposition.x-currentposition.x;
    float checky=otherposition.y-currentposition.y;
    float intersecx,intersecy;
    if(checkx<0)
    {
        intersecx= -(checkx)-(otherhalfsize.x+currenthalfsize.x);
    }
    if(checkx>=0) intersecx= (checkx)-(otherhalfsize.x+currenthalfsize.x);
    if(checky<0)
    {
        intersecy= -(checky)-(otherhalfsize.y+currenthalfsize.y);
    }
    if(checky>=0) intersecy= (checky)-(otherhalfsize.y+currenthalfsize.y);

    if(intersecx<0.0f&&intersecy<0.0f)
    {

        if(intersecx>intersecy)
        {
            if(checkx>0.0f)
            {
                Move(intersecx*(1.0f-push),0.0f);
                player.Move(-(intersecx*push),0.0f);
            }
            else
            {
                Move(-intersecx*(1.0f-push),0.0f);
                 player.Move(intersecx*push,0.0f);
            }
        }
        else
        {
             if(checky>0.0f)
            {
                Move(0.0f,intersecy*(1.0f-push));
                 player.Move(0.0f,-(intersecy*push));
            }
            else
            {
                Move(0.0f,-intersecy*(1.0f-push));
                 player.Move(0.0f,intersecy*push);
            }
        }
            return true;



    }
     return false;
}
collider::collider(sf::RectangleShape &player):
    player(player)
{

}

collider::~collider()
{
    //dtor
}
#endif // COLLIDER_H
