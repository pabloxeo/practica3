# include "ParchisGUI.h"
# include "Parchis.h"

using namespace sf;
using namespace std;

int main(int argc, char const *argv[]){
    //ParchisGUI parchis;
    //parchis.display();
    //parchis.moveFichas();
    Parchis parchis;
    ParchisGUI parchis_gui(parchis);
    parchis_gui.run();

    return 0;
}