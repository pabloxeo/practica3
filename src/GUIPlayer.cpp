# include "GUIPlayer.h"
# include "Parchis.h"

bool GUIPlayer::move(){
    cout << "auto_think: " << auto_think << endl;
    if(auto_think){
        return AIPlayer::move();
    }
    else return false;
    
}