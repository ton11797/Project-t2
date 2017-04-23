#include <fstream>
#include <iostream>
using namespace std;
class tcp
{
private:
    char data[100];
    int port;
    char ip[100];
    sf::TcpSocket socket;
    sf::Socket::Status status;
    std::size_t received;
public:
    tcp();
    void connect();
    void sent(char *dataa);
    void receive();
    char* getdata();
};
tcp::tcp()
{
    ifstream configfile;
    char temp[100];
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
}
void tcp::connect()
{
    //status = socket.connect(ip, port);
    if (status != sf::Socket::Done)
    {
        cout<<"connect error";
    }
}
void tcp::sent(char *dataa)
{
    if (socket.send(dataa, 100) != sf::Socket::Done)
    {
        cout<<"sent error";
    }
}
void tcp::receive()
{
    if (socket.receive(data, 100, received) != sf::Socket::Done)
    {
        cout<<"sent receive";
    }
}
char* tcp::getdata()
{
