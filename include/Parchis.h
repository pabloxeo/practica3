//Lista con los diferentes tipos de casillas
enum box_type {normal, home, final_queue, goal};







//Struct para definir las fichas: número de casilla y tipo
struct Piece
{
    int num;
    box_type type; 
};
