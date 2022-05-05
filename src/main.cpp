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
    string type_j1 = "GUI", type_j2 = "GUI";
    int id_j1 = 0, id_j2 = 0;
    int port = 8888;
    string ip = "localhost";
    string name_j1 = "J1", name_j2 = "J2";
    bool gui = true;
    bool ninja_server = false;

    /* Parse the command line arguments in the following way:
     * --p1 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J1)
     * --p2 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J2)
     * --ip <ip>  [Optional]
     * --port <port>  [Optional]
     * --board <config=GROUPED>
     * --no-gui  [Optional]
     * --ninja-server [Optional]
     *
     * Default parameters:
     * --p1 GUI 0 J1 --p2 GUI 0 J2 
     */
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "--p1") == 0){
            i++;
            type_j1 = argv[i];
            i++;
            id_j1 = atoi(argv[i]);
            i++;
            name_j1 = argv[i];
        }
        else if(strcmp(argv[i], "--p2") == 0){
            i++;
            type_j2 = argv[i];
            i++;
            id_j2 = atoi(argv[i]);
            i++;
            name_j2 = argv[i];
        }
        else if(strcmp(argv[i], "--ip") == 0){
            i++;
            ip = argv[i];
        }
        else if(strcmp(argv[i], "--port") == 0){
            i++;
            port = atoi(argv[i]);
        }
        else if(strcmp(argv[i], "--board") == 0){
            i++;
            BoardConfig config = BoardConfig::GROUPED;
            if(strcmp(argv[i], "GROUPED") == 0){
                config = BoardConfig::GROUPED;
            }
            if(strcmp(argv[i], "ALTERNED") == 0){
                config = BoardConfig::ALTERNED;
            }
        }
        else if(strcmp(argv[i], "--no-gui") == 0){
            gui = false;
        }
        else{
            cout << "Error parsing command line arguments" << endl;
            cout << "Usage: " << argv[0] << " --p1 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J1) --p2 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J2) --ip <ip>  [Optional] --port <port>  [Optional] --board <config=GROUPED> --no-gui  [Optional]" << endl;
            return -1;
        }
    }

    bool is_remote = (type_j1 == "Client" || type_j1 == "Server" || type_j1 == "Ninja") or (type_j2 == "Client" || type_j2 == "Server" || type_j2 == "Ninja");
    

    if(argc == 1){
        //J1 con GUI
        GUIPlayer p1 = GUIPlayer("J1");
        //J2 con AI
        //AIPlayer p2 = AIPlayer("J2");
        //J2 con GUI
        GUIPlayer p2 = GUIPlayer("J2");

        Parchis parchis(GROUPED, p1, p2);
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
        
        if (atoi(argv[2]) == 0){
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
        }else if(atoi(argv[2]) == 1){
            //J2 con GUI.
            GUIPlayer p2 = GUIPlayer("J2");
            //J1 remoto.
            RemotePlayer p1 = RemotePlayer("J1", client);

            //Inciar juego y GUI.
            Parchis parchis(GROUPED, p1, p2);
            ParchisGUI parchis_gui(parchis);

            // Set the GUI for GUIPlayers.
            p2.setGUI(parchis_gui);

            // Start the game.
            parchis_gui.run();
        }
        

        return 0;
    }
    else if(argc == 2 and strcmp(argv[1], "--ninja-server") == 0){
        //ParchisServer server;
        //server.startListening(8889);
        TcpListener listener;
        if(listener.listen(8889) != Socket::Done){
            throw runtime_error("Could not listen to port");
        }

        cout << "Listening on port " << 8889 << endl;
        
        //Crear lista de ParchisServer
        //Gracias Mario :)
        list<shared_ptr<ParchisServer>> servers;
        list<shared_ptr<Thread>> threads;

        //Comprobar conexiones y cerrar hebras.
        auto reviseThreads = [&threads, &servers](){
            while(true){
                cout << "Checking threads..." << endl;
                auto it_threads = threads.begin();
                auto it_servers = servers.begin();

                for(; it_threads != threads.end() && it_servers != servers.end(); ++it_threads, ++it_servers){
                    if(!(*it_servers)->isConnected()){
                        (*it_threads)->wait();
                        it_threads = threads.erase(it_threads);
                        it_servers = servers.erase(it_servers);
                        //delete (*it_threads);
                        //delete (*it_servers);       
                    }
                }
                sleep(seconds(60));
            }
        };

        Thread thread_revise(reviseThreads);
        thread_revise.launch();

        
        while(true){
            auto server = make_shared<ParchisServer>();

            auto initGame = [server] (){
                Packet packet;
                MessageKind message_kind;
                do{
                    message_kind = server->receive(packet);
                    sleep(milliseconds(10));
                }while(message_kind != GAME_PARAMETERS);

                int player;
                string name;
                BoardConfig init_board;
                server->packet2gameParameters(packet, player, name, init_board);

                if (player == 0){
                    //J1 remoto.
                    RemotePlayer p1 = RemotePlayer("J1", *server);
                    //J2 con GUI.
                    AIPlayer p2 = AIPlayer("J2");
                    //Inciar juego.
                    Parchis parchis(init_board, p1, p2);
              
                    parchis.gameLoop();
                }
                else{
                    //J1 con GUI.
                    AIPlayer p1 = AIPlayer("J1");
                    //J2 remoto.
                    RemotePlayer p2 = RemotePlayer("J2", *server);

                    //Inciar juego 
                    Parchis parchis(init_board, p1, p2);
                    parchis.gameLoop();
                }
            };

            server->acceptConnection(listener);
            servers.push_back(server);
            //Thread *thread = new Thread(initGame);
            //Thread thread(initGame);
            threads.push_back(make_shared<Thread>(initGame));
            threads.back()->launch();
        }
        
        return 0;

        }
        else if(argc == 2 and strcmp(argv[1], "--server") == 0){
            TcpListener listener;
            if(listener.listen(8889) != Socket::Done){
                throw runtime_error("Could not listen to port");
            }

            cout << "Listening on port " << 8889 << endl;

            ParchisServer server;
            server.acceptConnection(listener);
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
    else{
        cout << "Usage: ./Parchis [--client|--server]" << endl;
        return 1;
    }
}