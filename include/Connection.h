#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <SFML/Network.hpp>
#include "Attributes.h"
#include "Board.h"

using namespace sf;
using namespace std;

enum MessageKind{
    NOP = 0,
    //1xx - Connection messages.
    HELLO = 100,
    GAME_PARAMETERS = 101,
    TEST_ALIVE = 102,

    //2xx - OK messages.
    OK = 200,

    //3xx - Game messages.
    TEST_MESSAGE = 300,
    MOVED = 301,

    //4xx - Error messages.
    ERROR_DISCONNECTED = 400,

};

class ParchisRemote{
    protected:
        TcpSocket *socket;

        ParchisRemote();
        inline ~ParchisRemote(){socket->disconnect();  delete socket;}

    public:
        bool isConnected();

        void sendGameParameters(int player, string name, BoardConfig init_board);

        void sendTestMessage(string message);

        void sendParchisMove(int turn, color c_piece, int id_piece, int dice);

        MessageKind receive(Packet & packet);

        static void analyzePacket(Packet & packet, const MessageKind & kind);

        static string packet2message(Packet & packet);

        static void packet2move(Packet & packet, int & turn, color & c_piece, int & id_piece, int & dice);

        static void packet2gameParameters(Packet & packet, int & player, string & name, BoardConfig & init_board);
};

class ParchisClient: public ParchisRemote{
    public:
        ParchisClient();
        /**
         * @brief Inicia una conexión con el servidor remoto indicado.
         * 
         * @param ip_addr Dirección IP o nombre del servidor.
         * @param port Puerto de conexión.
         */
        void startClientConnection(const string & ip_addr, const int & port);

};


class ParchisServer: public ParchisRemote{
    private:
        //TcpListener listener;

    public:
        ParchisServer();

        //void startListening(const int & port);

        void acceptConnection(TcpListener & listener);

};




#endif