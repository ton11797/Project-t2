#include "animetion.h"
#include<iostream>
#include<SFML/Graphics.hpp>

animetion::animetion(sf::Texture *texture,sf::Vector2u imagecount,float switchtime)
{
    this->imagecount=imagecount;
    this->switchtime=switchtime;
    totaltime=10.0f;
    currentimage.x=0;
    uvRect.width=texture->getSize().x / float(imagecount.x);
    uvRect.height=texture->getSize().y/ float(imagecount.y);
}

animetion::~animetion()
{
    //dtor
}
void animetion::update(int row,float deltatime)
{
    currentimage.y=row;
    totaltime+=deltatime;
    if(totaltime >= switchtime)
    {
        totaltime-=switchtime;
        currentimage.x++;
        if(currentimage.x>=imagecount.x)
        {
            currentimage.x=0;
        }
    }
    uvRect.left=currentimage.x*uvRect.width;
    uvRect.top=currentimage.y*uvRect.height;
}
