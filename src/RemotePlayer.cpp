#include "RemotePlayer.h"
#include "Parchis.h"

void RemotePlayer::perceive(Parchis &p){
    //Call to super
    Player::perceive(p);

    if(actual->getTurn() > 1){
        int turn = actual->getTurn();
        tuple <color, int, int> last_action = actual->getLastAction();
        color c = get<0>(last_action);
        int id = get<1>(last_action);
        int dice = get<2>(last_action);
        controller->sendParchisMove(turn, c, id, dice);
    }
}

bool RemotePlayer::move(){
    bool moved = false;

    while(!moved){
        Packet packet;
        cout << "Esperando movimiento del oponente..." << endl;
        MessageKind msgkind = controller->receive(packet);
        
        switch(msgkind){
            case MOVED:
                int turn;
                color c_piece;
                int id_piece;
                int dice;
                controller->packet2move(packet, turn, c_piece, id_piece, dice);

                if(turn <= actual->getTurn()){
                    cout << "Old move received. Already up to date." << endl;
                    break;
                }
                else if(turn > actual->getTurn() + 1){
                    cout << "WTF move too new. Some turns have been missed." << endl;
                    break;
                }
                else{
                    cout << "Current move received. Moving..." << endl;
                    actual->movePiece(c_piece, id_piece, dice);
                    moved = true;
                    return true;
                }
                

            default:
                cout << "Error: Unexpected " << msgkind << " received." << endl;
                return false;
        
        }
    }
    return true;
}