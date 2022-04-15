# include "Connection.h"
# include <iostream>
# include <string>

using namespace std;
using namespace sf;


void ParchisRemote::sendTestMessage(string message)
{
    Packet packet;
    packet << TEST_MESSAGE;
    packet << message;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
         throw runtime_error("Error sending message");
    }
    cout << "TEST_MESSAGE sent" << endl;
    cout << "Message: " << message << endl;
}

void ParchisRemote::sendParchisMove(int turn, color c_piece, int id_piece, int dice){
    Packet packet;
    packet << MOVED;
    packet << turn;
    packet << c_piece;
    packet << id_piece;
    packet << dice;
    Socket::Status status = socket.send(packet);
    if(status != Socket::Done)
    {
         throw runtime_error("Error sending message");
    }
    cout << "301 MOVED sent" << endl;
    cout << "Move: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
}

MessageKind ParchisRemote::receive(Packet & packet)
{
    packet.clear();
    Socket::Status status = socket.receive(packet);

    if(status != Socket::Done)
    {
         throw runtime_error("Error receiving message");
    }
    
    int type;
    packet >> type;

    Packet p2(packet);
    switch(type)
    {
        case TEST_MESSAGE:
        {
            cout << "300 TEST_MESSAGE received" << endl;
            break;
        }
        case MOVED:
        {
            cout << "301 MOVED received" << endl;
            break;
        }
        default:
        {
            cout << "Received unknown message" << endl;
        }
    }

    return (MessageKind)type;

}

void ParchisRemote::analyzePacket(Packet & packet, const MessageKind & kind)
{
   switch(kind)
    {
        case TEST_MESSAGE:
        {
            string message = ParchisRemote::packet2message(packet);
            cout << "300 TEST_MESSAGE received: " << message << endl;
            break;
        }
        case MOVED:
        {
            color c_piece;
            int id_piece;
            int dice;
            int turn;
            
            ParchisRemote::packet2move(packet, turn, c_piece, id_piece, dice);
            cout << "301 MOVED received: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
            break;
        }
        default:
        {
            cout << "Received unknown message" << endl;
        }
    }
}


string ParchisRemote::packet2message(Packet & packet)
{
    string message;
    packet >> message;
    cout << "Message: " << message << endl;
    return message;
}

void ParchisRemote::packet2move(Packet & packet, int & turn, color & c_piece, int & id_piece, int & dice)
{
    packet >> turn;
    int cint_piece;
    packet >> cint_piece;
    c_piece = (color)cint_piece;
    packet >> id_piece;
    packet >> dice;
    cout << "Move: " << turn << " " << str(c_piece) << " " << id_piece << " " << dice << endl;
}



void ParchisClient::startClientConnection(const string & ip_addr, const int & port){
    Socket::Status status = socket.connect(ip_addr, port);

    if(status != Socket::Done){
        throw runtime_error("Could not connect to server");
    }

    cout << "Connected to server " << ip_addr << ":" << port << endl;

}

void ParchisServer::startListening(const int & port){
    if(listener.listen(port) != Socket::Done){
        throw runtime_error("Could not listen to port");
    }

    cout << "Listening on port " << port << endl;

    if(listener.accept(socket) != Socket::Done){
        throw runtime_error("Could not accept connection");
    }

    cout << "Accepted connection from " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << endl;
}

