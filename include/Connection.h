#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <SFML/Network.hpp>
#include "Attributes.h"
#include "Board.h"
#include <list>
#include <memory>
#include <set>

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
        TcpSocket socket;

        ParchisRemote();
        inline ~ParchisRemote(){socket.disconnect();}

    public:
        bool isConnected();

        void sendGameParameters(int player, string name, BoardConfig init_board, int ai_id = 0);

        void sendTestAlive();

        void sendTestMessage(string message);

        void sendParchisMove(int turn, color c_piece, int id_piece, int dice);


        MessageKind receive(Packet & packet);

        static void analyzePacket(Packet & packet, const MessageKind & kind);

        static string packet2message(Packet & packet);

        static void packet2move(Packet & packet, int & turn, color & c_piece, int & id_piece, int & dice);

        static void packet2gameParameters(Packet & packet, int & player, string & name, BoardConfig & init_board, int & ai_id);
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


class NinjaServer{
    private:
        // Para partidas contra los ninjas.
        struct ninja_game{
            shared_ptr<ParchisServer> connection; // Gracias Mario :)
            shared_ptr<Thread> thread;
        };
        list<ninja_game> ninja_games;

        // Para partidas "aleatorias".
        struct random_match_game{
            shared_ptr<ParchisServer> connection_p1;
            shared_ptr<ParchisServer> connection_p2;
            shared_ptr<Thread> thread;
        };
        list<random_match_game> random_match_games;

        // Para partidas privadas.
        struct private_room_game{
            string room_id;
            shared_ptr<ParchisServer> connection_p1;
            shared_ptr<ParchisServer> connection_p2;
            shared_ptr<Thread> thread;

            inline bool operator<(const private_room_game &b)
            {
                return this->room_id < b.room_id;
            }
        };

        // Hebras sin asignar.
        vector<shared_ptr<Thread>> idle_threads;

        set<private_room_game> private_room_games;
        
        Thread reviser;

        Thread master_thread;
        ParchisClient master_connection;


        Thread console_reader_thread            ;

        TcpListener listener;
        int listener_port;

        bool is_running;

        Mutex ninja_games_mutex;

        void reviseNinjaThreadsStep();
        void reviseNinjaThreadsLoop();

        void reviseRandomMatchThreadsStep();
        void reviseRandomMatchThreadsLoop();

        void revisePrivateRoomThreadsStep();
        void revisePrivateRoomThreadsLoop();

        void reviserLoop();

        void consoleReader();

        void masterReceiver();

        void acceptationLoop();
        void acceptationStep(shared_ptr<ParchisServer> server);


        void newNinjaGame(int player, string name, BoardConfig init_board, int ai_id);
        void queueRandomMatchGame(string player_name);
        void queuePrivateRoomGame(string room_id, string player_name);
        

    public:

        NinjaServer(const int & port);

        void startServer();

        void stopServer();

        void printStatus();


        

};




#endif