#ifndef PLAYER_H
#define PLAYER_H
#define OBJECT_H
#include<SFML/Graphics.hpp>
#include "animetion.h"
#include "collider.h"
#include <iostream>
#include "object.h"
#include "Player.h"
//class object;
class Player
{
    public:
        Player(sf::Texture* texture,sf::Vector2u imagecount,float switchtime,sf::Vector2f position);
        virtual ~Player();
        void update(float deltatime,float movespeed,int start,int &money);
        void Draw(sf::RenderWindow &window){window.draw(body);}
        sf::Vector2f Getposition(){return body.getPosition();}
        collider getcollider(){return collider(body);}
        //collider Getcolider(){return collider(body)}

    protected:

    private:sf::RectangleShape body;
                animetion anima;

};
Player::Player(sf::Texture* texture,sf::Vector2u imagecount,float switchtime,sf::Vector2f position):
    anima(texture,imagecount,switchtime)
{
    body.setSize(sf::Vector2f(50.0f,70.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(position);
    body.setTexture(texture);
}

Player::~Player()
{
    //dtor
}
void Player::update(float deltatime,float movespeed,int start,int &money)
{
    if(start==0)body.setTextureRect(anima.uvRect);
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            //if(body.getPosition().x/50>=0.5f)
            body.move(-movespeed,0.0f);
            anima.update(1,deltatime);
            body.setTextureRect(anima.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
           //if (body.getPosition().y/50<=18.8f)
            body.move(0.0f,+movespeed);
            anima.update(0,deltatime);
            body.setTextureRect(anima.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            //if(body.getPosition().x/50<=37.8f)
            body.move(movespeed,0.0f);
            anima.update(2,deltatime);
            body.setTextureRect(anima.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
           // if (body.getPosition().y/50>=0.6f)
            body.move(0.0f,-movespeed);
            anima.update(3,deltatime);
            body.setTextureRect(anima.uvRect);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            //plant(window,mapcheck[][19],weed);
            cout<<"X = "<<static_cast<int>(body.getPosition().x/50)<<" Y = "<<static_cast<int>(body.getPosition().y/50)<<endl;
            cout<<"YOUR FUCKING MONEY = "<<money<<endl;

        }
        //window.draw(texture);
        /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            body.setPosition(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
        }*/
}
#endif  // PLAYER_H
