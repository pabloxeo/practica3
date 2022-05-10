# include "ParchisGUI.h"
# include "Parchis.h"
# include "Connection.h"
# include "GUIPlayer.h"
# include "RemotePlayer.h"
# include "AIPlayer.h"
# include "Ninja.h"
# include "IncludesSFML.h"
# include "cout_colors.h"
# include "GameSelector.h"

#include <cstring>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#define ALLOWED_NINJAS_FILE "config/allowed_ninjas.txt"
#define MASTER_ADDRESSES_FILE "config/master_addresses.txt"

using namespace sf;
using namespace std;

void readAllowedMasters(string file_name, vector<string> &ips, vector<int> &ports)
{
    // Read file_name. Each line has a string with an ip address and a port. Add each line to the returned vector.
    ifstream file(file_name);
    string line;
    while (getline(file, line))
    {
        string ip;
        int port;
        stringstream ss(line);
        ss >> ip;
        ss >> port;
        ips.push_back(ip);
        ports.push_back(port);
    }
}

void clientMasterHandshake(string & ip_addr, int & port){
    vector<string> ips;
    vector<int> ports;
    readAllowedMasters(MASTER_ADDRESSES_FILE, ips, ports);
    int i;
    for(i = 0; i < ips.size(); i++){
        try{
            cout << "Trying " << ips[i] << ":" << ports[i] << endl;
            shared_ptr<ParchisClient> client_master = make_shared<ParchisClient>();
            client_master->startClientConnection(ips[i], ports[i]);
            Packet packet;
            MessageKind message_kind;
            client_master->sendHello();
            do
            {
                message_kind = client_master->receive(packet);
                if (message_kind > 400)
                {
                    throw runtime_error("Could not connect to master server: " + to_string(message_kind));
                }
                else if (message_kind == QUEUED)
                {
                    cout << "Lo sentimos. El servidor está completo en este momento. Se te ha puesto en cola." << endl;
                    int queue_pos = client_master->packet2queuePos(packet);
                    cout << "Tu posición en la cola es: #" << queue_pos << endl;
                }
            } while (message_kind != ACCEPTED);
            client_master->packet2acceptedIp(packet, ip_addr, port);
            break;
        }
        catch(...){
            cout << COUT_RED_BOLD << "Could not connect to master server: " << ips[i] << ":" << ports[i] << COUT_NOCOLOR << endl;
        }
    }
    if(i == ips.size()){
        cout << COUT_RED_BOLD << "No se ha podido conectar a ningún servidor. Avisa a tus profesores cuanto antes." << COUT_NOCOLOR << endl;
    }
}

vector<string> readAllowedNinjas(string file_name){
    // Read file_name. Each line has a string with an ip address. Add each line to the returned vector.
    vector<string> ips;
    ifstream file(file_name);
    string line;
    while (getline(file, line))
    {
        ips.push_back(line);
    }
    return ips;
}



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
    bool server = false;
    bool ninja_server = false;
    bool master_server = false;
    BoardConfig config = BoardConfig::GROUPED;

    /* Parse the command line arguments in the following way:
     * --p1 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J1)
     * --p2 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J2)
     * --ip <ip>  [Optional]
     * --port <port>  [Optional]
     * --board <config=GROUPED>
     * --no-gui  [Optional]
     * --server  [Optional]
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
        else if(strcmp(argv[i], "--server") == 0){
            server = true;
            i++;
            type_j1 = argv[i];
            i++;
            id_j1 = atoi(argv[i]);
            i++;
            name_j1 = argv[i];
        }
        else if(strcmp(argv[i], "--ninja-server") == 0){
            ninja_server = true;
        }
        else if(strcmp(argv[i], "--master") == 0){
            master_server = true;
        }
        else{
            cout << "Error parsing command line arguments" << endl;
            cout << "Usage: " << argv[0] << " --p1 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J1) --p2 <type=GUI|AI|Client|Server|Ninja> (id=0) (name=J2) --ip <ip>  [Optional] --port <port>  [Optional] --board <config=GROUPED> --no-gui  [Optional]" << endl;
            return -1;
        }
    }

    if(argc == 1){
        // Si no se pasan argumentos se crea la ventana para la selección de modo de juego, que se encargará de asignar los parámetros del juego a las variables.
        cout << "No se pasaron argumentos, mostrando ventana de selección de juego..." << endl;
        GameSelector game_selector;
        game_selector.run();

        GameParameters params = game_selector.getGameParameters();
        type_j1 = params.type_j1;
        id_j1 = params.id_j1;
        name_j1 = params.name_j1;
        type_j2 = params.type_j2;
        id_j2 = params.id_j2;
        name_j2 = params.name_j2;
        ip = params.ip;
        port = params.port;
        config = params.config;
        gui = params.gui;
        server = params.server;
        ninja_server = params.ninja_server;
    }

    bool is_remote = (type_j1 == "Remote" || type_j1 == "Server" || type_j1 == "Ninja") or (type_j2 == "Remote" || type_j2 == "Server" || type_j2 == "Ninja");

    shared_ptr<Player> p1, p2;

    if(master_server){
        MasterServer master_server(port);
        vector<string> ips = readAllowedNinjas(ALLOWED_NINJAS_FILE);
        for(string ip : ips){
            master_server.addAllowedNinja(ip);
        }
        master_server.startServer();
    }
    else if(ninja_server){
        NinjaServer server(port);
        vector<string> ips;
        vector<int> ports;
        readAllowedMasters(MASTER_ADDRESSES_FILE, ips, ports);
        for(int i = 0; i < ips.size(); i = (i+1)%ips.size()){
            server.setMaster(ips[i], ports[i]);
            try{
                server.startServer();
                cout << COUT_RED_BOLD << "Cortado servidor ninja" << COUT_NOCOLOR << endl;
            }
            catch(...){
                cout << COUT_RED_BOLD << "No se pudo contactar con el master en " << ips[i] << ":" << ports[i] << COUT_NOCOLOR << endl;
            }
        }
        
    }
    /*
    if(ninja_server){
        TcpListener listener;
        if(listener.listen(port) != Socket::Done){
            throw runtime_error("Could not listen to port");
        }

        cout << "Listening on port " << port << endl;
        
        //Crear lista de ParchisServer
        //Gracias Mario :)
        list<shared_ptr<ParchisServer>> servers;
        list<shared_ptr<Thread>> threads;

        //Comprobar conexiones y cerrar hebras.
        auto reviseThreads = [&threads, &servers](){
            while(true){
                cout << COUT_BLUE_BOLD + "Checking threads..." + COUT_NOCOLOR << endl;
                auto it_threads = threads.begin();
                auto it_servers = servers.begin();
                int nremoves = 0;

                for(; it_threads != threads.end() && it_servers != servers.end();){
                    (*it_servers)->sendTestAlive();
                    if(!(*it_servers)->isConnected()){
                        (*it_threads)->wait();
                        it_threads = threads.erase(it_threads);
                        it_servers = servers.erase(it_servers);
                        nremoves++;
                        //delete (*it_threads);
                        //delete (*it_servers);       
                    }
                    else{
                        ++it_threads;
                        ++it_servers;
                    }
                }
                cout << COUT_BLUE_BOLD + "Current connections: " << servers.size() << " (" << nremoves << " removed)" + COUT_NOCOLOR << endl;
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
                int ai_id;
                server->packet2gameParameters(packet, player, name, init_board, ai_id);

                if (player == 0){
                    //J1 remoto.
                    shared_ptr<RemotePlayer> p1 = make_shared<RemotePlayer>("J1", server);
                    //J2 Ninja.
                    shared_ptr<Ninja> p2 = make_shared<Ninja>("J2", ai_id);
                    //Inciar juego.
                    Parchis parchis(init_board, p1, p2);
            
                    parchis.gameLoop();
                }
                else{
                    //J2 remoto.
                    shared_ptr<RemotePlayer> p2 = make_shared<RemotePlayer>("J2", server);
                    //J1 ninja.
                    shared_ptr<Ninja> p1 = make_shared<Ninja>("J1", ai_id);

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
        
    }*/
    else if(server){
        TcpListener listener;
        if(listener.listen(port) != Socket::Done){
            throw runtime_error("Could not listen to port");
        }
        cout << "Listening on port " << port << endl;
        shared_ptr<ParchisServer> server = make_shared<ParchisServer>();
        server->acceptConnection(listener);
        Packet packet;
        MessageKind message_kind;
        do{
            message_kind = server->receive(packet);
            sleep(milliseconds(10));
        }while(message_kind != GAME_PARAMETERS);

        int player;
        string name;
        BoardConfig init_board;
        int ai_id; // Ignorado por el server, lo elige él mismo su id.
        server->packet2gameParameters(packet, player, name, init_board, ai_id);

        if (player == 0){
            //J1 remoto.
            p1 = make_shared<RemotePlayer>(name, server);
            if(type_j1 == "GUI"){
                p2 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p2 = make_shared<AIPlayer>(name_j1, id_j1);
            }        
        }
        else{
            p2 = make_shared<RemotePlayer>(name, server);
            if(type_j1 == "GUI"){
                p1 = make_shared<GUIPlayer>(name_j1, id_j1);
            }
            else if(type_j1 == "AI"){
                p1 = make_shared<AIPlayer>(name_j1, id_j1);
            }
        }
    }
    else{
        if(type_j1 == "GUI"){
            p1 = make_shared<GUIPlayer>(name_j1, id_j1);
        }
        else if(type_j1 == "AI"){
            p1 = make_shared<AIPlayer>(name_j1, id_j1);
        }
        else if(type_j1 == "Remote"){
            shared_ptr<ParchisClient> client= make_shared<ParchisClient>();
            client->startClientConnection(ip, port);
            Packet packet;
            MessageKind message_kind;
            client->sendGameParameters(1, name_j1, config);
            p1 = make_shared<RemotePlayer>(name_j1, client);
            //p1 = make_shared<RemotePlayer>(id_j1, name_j1, ip, port);
        }
        else if(type_j1 == "Ninja"){
            string ip_ninja;
            int port_ninja;
            clientMasterHandshake(ip_ninja, port_ninja);
            shared_ptr<ParchisClient> client = make_shared<ParchisClient>();
            // Se conecta al servidor de ninjas que establezcamos
            //client->startClientConnection("localhost", 8888);
            client->startClientConnection(ip_ninja, port_ninja);
            Packet packet;
            MessageKind message_kind;
            client->sendGameParameters(1, name_j1, config, id_j1);
            p1 = make_shared<RemotePlayer>(name_j1, client);
        }


        if(type_j2 == "GUI"){
            p2 = make_shared<GUIPlayer>(name_j2, id_j2);
        }
        else if(type_j2 == "AI"){
            p2 = make_shared<AIPlayer>(name_j2, id_j2);
        }
        else if(type_j2 == "Remote"){
            shared_ptr<ParchisClient> client= make_shared<ParchisClient>();
            client->startClientConnection(ip, port);
            Packet packet;
            MessageKind message_kind;
            client->sendGameParameters(0, name_j2, GROUPED);
            p2 = make_shared<RemotePlayer>(name_j2, client);
            //p2 = make_shared<RemotePlayer>(id_j2, name_j2, ip, port);
        }
        else if (type_j2 == "Ninja")
        {
            string ip_ninja;
            int port_ninja;
            clientMasterHandshake(ip_ninja, port_ninja);
            shared_ptr<ParchisClient> client = make_shared<ParchisClient>();
            // Se conecta al servidor de ninjas que establezcamos
            client->startClientConnection(ip_ninja, port_ninja);
            Packet packet;
            MessageKind message_kind;
            client->sendGameParameters(0, name_j2, config, id_j2);
            p2 = make_shared<RemotePlayer>(name_j2, client);
        }
    }

    Parchis parchis(config, p1, p2);
    
    if(gui){
        ParchisGUI parchis_gui(parchis);
        shared_ptr<GUIPlayer> gui_p1 = dynamic_pointer_cast<GUIPlayer>(p1);
        if(gui_p1){
            gui_p1->setGUI(parchis_gui);
        }
        shared_ptr<GUIPlayer> gui_p2 = dynamic_pointer_cast<GUIPlayer>(p2);
        if(gui_p2){
            gui_p2->setGUI(parchis_gui);
        }
        if(type_j1 != "GUI" && type_j2 != "GUI"){
            shared_ptr<GUIPlayer> viewer = make_shared<GUIPlayer>("Viewer");  
            viewer->setGUI(parchis_gui);
            parchis.addViewer(viewer); 
        }
        parchis_gui.run();
    }
    else{
        parchis.gameLoop();
    }



    return 0;

    /*
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
    }*/
}