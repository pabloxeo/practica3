#ifndef __ATTRIBUTES_H__
#define __ATTRIBUTES_H__

# include <vector>
# include <map>

using namespace std;

//Lista con los diferentes tipos de casillas
enum color {blue, red, green, yellow, none};

//Lista con los diferentes tipos de casillas
enum box_type {normal, home, final_queue, goal};

//Struct para definir las fichas: número de casilla y tipo
struct Box
{
    int num;
    box_type type;
    color col;

    inline Box(int num, box_type type, color col){
        this->num = num; this->type = type; this->col = col;
    }
};


inline bool operator <(const Box & a, const Box & b){
    return a.num > b.num or (a.num == b.num and a.type > b.type) or
           (a.num == b.num and a.type == b.type and a.col > b.col);
}



#endif