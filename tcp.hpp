#include <fstream>
#include <iostream>
#include <SFML/Network.hpp>
using namespace std;
class tcp
{
private:
    char data[150];
    int port;
    char ip[150];
    sf::TcpSocket socket;
    sf::Socket::Status status;
    std::size_t received;
public:
    bool con;
    tcp();
    void connect();
    void sent(char *dataa);
    void receive();
    char* getdata();
};
tcp::tcp()
{
    ifstream configfile;
    char temp[150];
    configfile.open("config.txt");
    if (configfile.is_open())
    {
        while (!configfile.eof())
        {
            configfile >>temp;
            configfile >> port;
            configfile >>temp;
            configfile >> ip;
        }
    }
    status = socket.connect(ip, port);
    configfile.close();
    if (status != sf::Socket::Done)
    {
        con=0;
    }
    else
    {
        con=1;
    }
}
void tcp::connect()
{
    //status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        con=0;
    }
    else
    {
        con=1;
    }
}
void tcp::sent(char *dataa)
{
    if (socket.send(dataa, 150) != sf::Socket::Done)
    {
        cout<<"sent error";
        con=0;
    }
}
void tcp::receive()
{
    if (socket.receive(data, 150, received) != sf::Socket::Done)
    {
        cout<<"sent receive";
    }
}
char* tcp::getdata()
{

    return data;
}
