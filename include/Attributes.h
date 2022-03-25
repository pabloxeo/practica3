#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

# include <vector>
# include <map>

using namespace std;

//Lista con los diferentes tipos de casillas
enum color {blue, red, green, yellow, none};

inline string str(color c){
    switch(c){
        case blue: return "Azul";
        case red: return "Rojo";
        case green: return "Verde";
        case yellow: return "Amarillo";
        case none: default: return "???";
    }
}


//Lista con los diferentes tipos de casillas
enum box_type {normal, home, final_queue, goal};

//Struct para definir las casillas: número de casilla y tipo
struct Box
{
    int num;
    box_type type;
    color col;

    inline Box(int num, box_type type, color col){
        this->num = num; this->type = type; this->col = col;
    }

    inline Box(){};
};


inline bool operator <(const Box & a, const Box & b){
    return a.num > b.num or (a.num == b.num and a.type > b.type) or
           (a.num == b.num and a.type == b.type and a.col > b.col);
}


inline bool operator ==(const Box & a, const Box & b){
    return a.num == b.num && a.type == b.type && a.col == b.col;
}



#endif