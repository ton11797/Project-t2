
#include <SFML/Network.hpp>
#include<iostream>
using namespace std;
int main()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done)
    {
        cout<<"error";
    }else{
        cout<<"ok";
    }

    return 0;
}
