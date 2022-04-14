#ifndef __REMOTEPLAYER_H__
#define __REMOTEPLAYER_H__

#include "Attributes.h"
#include "Player.h"
#include "Connection.h"

class RemotePlayer : public Player {
    private:
        ParchisRemote *controller;


    public:
        void perceive(Parchis &p);

        inline RemotePlayer(const string &name, ParchisRemote &controller) :Player(name) {
            this->controller = &controller;
        }

        virtual bool move();

};

#endif