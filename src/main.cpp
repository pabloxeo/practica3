# include "ParchisGUI.h"
# include "Parchis.h"
# include "Connection.h"
# include "GUIPlayer.h"
# include "RemotePlayer.h"
# include "AIPlayer.h"
# include "Ninja.h"
# include "IncludesSFML.h"

#include <cstring>
#include <memory>

using namespace sf;
using namespace std;

int main(int argc, char const *argv[]){
    //ParchisGUI parchis;
    //parchis.display();
    //parchis.moveFichas();
    if(argc == 1){
        //J1 con GUI
        GUIPlayer p1 = GUIPlayer("J1");
        //J2 con AI
        //AIPlayer p2 = AIPlayer("J2");
        //J2 con GUI
        GUIPlayer p2 = GUIPlayer("J2");

        Parchis parchis(DEBUG7, p1, p2);
        ParchisGUI parchis_gui(parchis);

        // Set the GUI for GUIPlayers.
        p1.setGUI(parchis_gui);
        p2.setGUI(parchis_gui);

        // Start the game.
        parchis_gui.run();

        return 0;
    }
    else if (argc == 2 and strcmp(argv[1], "--no-gui") == 0)
    {
        // J1 con GUI
        AIPlayer p1 = AIPlayer("J1");
        // J2 con AI
        AIPlayer p2 = AIPlayer("J2");
        // J2 con GUI
        // GUIPlayer p2 = GUIPlayer("J2");

        Parchis parchis(GROUPED, p1, p2);

        // Start the game.
        parchis.gameLoop();

        return 0;
    }
    else if(argc == 4 and strcmp(argv[1], "--client") == 0){
        ParchisClient client;
        client.startClientConnection("127.0.0.1", 8889);

        Packet packet;
        MessageKind message_kind;
        client.sendGameParameters(atoi(argv[2]), (string) argv[3], GROUPED);
        
        //J1 con GUI.
        GUIPlayer p1 = GUIPlayer("J1");
        //J2 remoto.
        RemotePlayer p2 = RemotePlayer("J2", client);

        //Inciar juego y GUI.
        Parchis parchis(GROUPED, p1, p2);
        ParchisGUI parchis_gui(parchis);

        // Set the GUI for GUIPlayers.
        p1.setGUI(parchis_gui);

        // Start the game.
        parchis_gui.run();

        return 0;
    }
    else if(argc == 2 and strcmp(argv[1], "--server") == 0){
        ParchisServer server;
        server.startListening(8889);
        server.acceptConnection();

        Packet packet;
        MessageKind message_kind;
        do{
            message_kind = server.receive(packet);
            sleep(milliseconds(10));
        }while(message_kind != GAME_PARAMETERS);

        int player;
        string name;
        BoardConfig init_board;
        server.packet2gameParameters(packet, player, name, init_board);

        if (player == 0){
            //J1 remoto.
            RemotePlayer p1 = RemotePlayer("J1", server);
            //J2 con GUI.
            GUIPlayer p2 = GUIPlayer("J2");
            //Inciar juego y GUI.
            Parchis parchis(init_board, p1, p2);
            ParchisGUI parchis_gui(parchis);

            // Set the GUI for GUIPlayers.
            p2.setGUI(parchis_gui);

            // Start the game.
            parchis_gui.run();
        }
        else{
            //J1 con GUI.
            GUIPlayer p1 = GUIPlayer("J1");
            //J2 remoto.
            RemotePlayer p2 = RemotePlayer("J2", server);

            //Inciar juego y GUI.
            Parchis parchis(init_board, p1, p2);
            ParchisGUI parchis_gui(parchis);

            // Set the GUI for GUIPlayers.
            p1.setGUI(parchis_gui);

            // Start the game.
            parchis_gui.run();
        }
        return 0;
    }
    else if(argc == 2 and strcmp(argv[1], "--ninja-server") == 0){
        ParchisServer server;
        server.startListening(8889);
        while(true){
            cout << "CCCCCCCCCCCCCCCCCCCC" << endl;
            server.acceptConnection();

            Packet packet;
            MessageKind message_kind;
            do{
                message_kind = server.receive(packet);
                sleep(milliseconds(10));
            }while(message_kind != GAME_PARAMETERS);



            int player;
            string name;
            BoardConfig init_board;
            server.packet2gameParameters(packet, player, name, init_board);

            vector<unique_ptr<Thread>> partidas;
            vector<unique_ptr<RemotePlayer>> p1s;
            vector<unique_ptr<AIPlayer>> p2s;

            if (player == 0){
                //J1 remoto.
                p1s.push_back(make_unique<RemotePlayer>("J1", server));
                //J2 con AI.
                p2s.push_back(make_unique<AIPlayer>("J2"));
                //Inciar juego.
                Parchis parchis(init_board, *p1s.back(), *p2s.back());
                
                partidas.push_back(make_unique<Thread>(&Parchis::gameLoop, &parchis));
                partidas.back()->launch();
                //Thread game_thread(&Parchis::gameLoop, &parchis);
                //partidas.push_back(game_thread);
                //game_thread.launch();
                
            }
            else{
                //J1 con AI.
                AIPlayer p1 = AIPlayer("J1");
                //J2 remoto.
                RemotePlayer p2 = RemotePlayer("J2", server);
                //Inciar juego.
                Parchis parchis(init_board, p1, p2);

                Thread game_thread(&Parchis::gameLoop, &parchis);

                game_thread.launch();
            }
        }
        return 0;
        
    }
    else{
        cout << "Usage: ./Parchis [--client|--server]" << endl;
        return 1;
    }
}