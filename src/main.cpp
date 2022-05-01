# include "ParchisGUI.h"
# include "Parchis.h"
# include "Connection.h"
# include "GUIPlayer.h"
# include "RemotePlayer.h"
# include "AIPlayer.h"

#include <cstring>

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
        AIPlayer p2 = AIPlayer("J2");
        //J2 con GUI
        //GUIPlayer p2 = GUIPlayer("J2");

        Parchis parchis(GROUPED, p1, p2);
        ParchisGUI parchis_gui(parchis);

        // Set the GUI for GUIPlayers.
        p1.setGUI(parchis_gui);
        //p2.setGUI(parchis_gui);

        // Start the game.
        parchis_gui.run();

        return 0;
    }
    else if(argc == 2 and strcmp(argv[1], "--client") == 0){
        ParchisClient client;
        client.startClientConnection("127.0.0.1", 8889);
        
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

        //J1 remoto.
        RemotePlayer p1 = RemotePlayer("J1", server);

        //J2 con GUI.
        GUIPlayer p2 = GUIPlayer("J2");

        //Inciar juego y GUI.
        Parchis parchis(GROUPED, p1, p2);
        ParchisGUI parchis_gui(parchis);

        // Set the GUI for GUIPlayers.
        p2.setGUI(parchis_gui);

        // Start the game.
        parchis_gui.run();
        

        return 0;
    }
    else{
        cout << "Usage: ./Parchis [--client|--server]" << endl;
        return 1;
    }
}