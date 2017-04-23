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

    protected:

    private:
        sf::RectangleShape body;
};
object::object(sf::Texture* texture,sf::Vector2f sizee,sf::Vector2f position)
{
    body.setSize(sizee);
    body.setOrigin(sizee/2.0f);
    body.setTexture(texture);
    body.setPosition(position);


}
void object::Draw(sf::RenderWindow &window)
{
    window.draw(body);
}
object::~object()
{
    //dtor
}

#endif // OBJECT_H
