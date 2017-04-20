#include <SFML/Network.hpp>
#include<iostream>
using namespace std;
int main()
{
    char data[100];
    cout<<"input data :";
    cin>>data;
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done)
    {
        cout<<"not connect"<<endl;
    }
    else
    {
        if (socket.send(data, 100) != sf::Socket::Done)
        {
            // error...
        }else{
            cout<<"data send";
        }
        char databack [100];
        std::size_t received;
        if (socket.receive(databack, 100, received) != sf::Socket::Done)
        {
        }
        cout << "databack :"<< databack;
    }
}
