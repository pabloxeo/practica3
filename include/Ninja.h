#ifndef __NINJA__
#define __NINJA__

# include "Attributes.h"
# include "AIPlayer.h"


class Ninja: public AIPlayer{
    public:
        inline Ninja(const string & name):AIPlayer(name){};
        void think(color & c_piece,  int & id_piece, int & dice) const;
};
#endif