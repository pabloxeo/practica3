# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{

    switch (id)
    {
    case 0:
        thinkAleatorio(c_piece, id_piece, dice);
        break;
    case 1:
        thinkAleatorioMasInteligente(c_piece, id_piece, dice);
        break;
    case 2:
        thinkFichaMasAdelantada(c_piece, id_piece, dice);
        break;
    case 3:
        thinkMejorOpcion(c_piece, id_piece, dice);
        break;
    case 4:
        double alpha = menosinf;
        double beta = masinf;
        Poda_AlfaBeta(*actual, actual->getCurrentPlayerId(), 2, c_piece, id_piece, dice, alpha, beta);
        break;
    }


    /*
    // El siguiente código se proporciona como sugerencia para iniciar la implementación del agente.

    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha = menosinf, beta = masinf; // Cotas iniciales de la poda AlfaBeta
    // Llamada a la función para la poda (los parámetros son solo una sugerencia, se pueden modificar).
    valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    // ----------------------------------------------------------------- //

    // Si quiero poder manejar varias heurísticas, puedo usar la variable id del agente para usar una u otra.
    switch(id){
        case 0:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, ValoracionTest);
            break;
        case 1:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion1);
            break;
        case 2:
            valor = Poda_AlfaBeta(*actual, jugador, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, alpha, beta, MiValoracion2);
            break;
    }
    cout << "Valor MiniMax: " << valor << "  Accion: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    */
}



double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}

void AIPlayer::thinkAleatorio(color & c_piece, int & id_piece, int & dice) const{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente 
    //como lo que se muestran al final de la función.
    
    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores, 
    //respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if(current_pieces.size() > 0){
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else{
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }
}

void AIPlayer::thinkAleatorioMasInteligente(color & c_piece, int & id_piece, int & dice) const{
    //El color de la ficha que se va a mover
    c_piece = actual->getCurrentColor();

    //Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    //vector que almacenará los ids de las fichas que se puede mover para el dado elegido
    vector<int> current_pieces;

    //Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);

    //Mirar que dados tienen fichas que se pueden mover
    vector<int> current_dices_que_pueden_mover_ficha;

    for(int i = 0; i < current_dices.size(); i++){

        //Se obtiene el vector de fichas que se pueden mover para el dado elegido

        current_pieces = actual->getAvailablePieces(c_piece, current_dices[i]);

        //Si se pueden mover fichas para el dado actual lo añado al vector de dados que pueden mover fichas
        if(current_pieces.size() > 0){
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }
    //Si no tengo dados que puedan mover fichas paso turno
    if(current_dices_que_pueden_mover_ficha.size() == 0){
            dice = current_dices[rand() % current_dices.size()];
            id_piece = SKIP_TURN;
    //En caso contrario elijo de forma aleatoria entre los que si puedan mover fichas
    }else{
        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];

        //Se obtiene el vector de fihcas que se pueden mover para ese dado
        current_pieces = actual->getAvailablePieces(c_piece, dice);

        //Muevo una ficha al azar
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    
}

void AIPlayer::thinkFichaMasAdelantada(color & c_piece, int & id_piece, int & dice) const{
    //Elige el dado con el metodo anterior
    thinkAleatorioMasInteligente(c_piece, id_piece, dice);
    //Buscamos la ficha mas adelantada(más cercana a la meta)

    vector<int> current_pieces = actual->getAvailablePieces(c_piece, dice);

    int id_ficha_mas_adelantada = -1,  min_distancia_meta = 9999;

    for(int i = 0; i < current_pieces.size(); i++){
        //distanceToGoal(color, id) devuelve la distancia hasta la meta
        int distancia_meta = actual->distanceToGoal(c_piece, current_pieces[i]);
        if(distancia_meta < min_distancia_meta){
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }
    }

    if(id_ficha_mas_adelantada == -1){
        id_piece = SKIP_TURN;
    }else{
        id_piece = id_ficha_mas_adelantada;
    }
}

void AIPlayer::thinkMejorOpcion(color & c_piece, int & id_piece, int & dice) const{
    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);

    bool me_quedo_con_esta_accion = false;

    while(!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion){
        if(siguiente_hijo.isEatingMove() or siguiente_hijo.isGoalMove() 
        or (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador)){
            me_quedo_con_esta_accion = true;
        }else{
            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        }
    }
    if(me_quedo_con_esta_accion){
         c_piece = last_c_piece;
         id_piece = last_id_piece;
         dice = last_dice;
    }else{
        thinkFichaMasAdelantada(c_piece, id_piece, dice);
    }
}

double AIPlayer::Poda_AlfaBeta(Parchis actual, int jugador,int PROFUNDIDAD_ALFABETA,color & c_piece,int & id_piece,int & dice,double & alpha,double & beta) const{
    color last_c_piece = none;
    int last_id_piece = -1;
    int last_dice = -1;
    double valor;
    if(PROFUNDIDAD_ALFABETA == 0 or actual.gameOver()){
        cout << "echo valo" << endl;
        return ValoracionTest(actual, jugador);
    }else{
        Parchis siguiente_hijo = actual.generateNextMove(last_c_piece, last_id_piece, last_dice);

        if(PROFUNDIDAD_ALFABETA%2==0){
            while(!(siguiente_hijo == actual)){

                valor = Poda_AlfaBeta(siguiente_hijo, jugador, PROFUNDIDAD_ALFABETA-1, last_c_piece, last_id_piece, last_dice, alpha, beta);
            
                if(valor > alpha){
                    alpha = valor;
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }

                if(beta <= alpha){
                    break;
                }
                
                siguiente_hijo = actual.generateNextMove(last_c_piece, last_id_piece, last_dice);

            }
            return alpha;
            
        }else{
            while(!(siguiente_hijo == actual)){
                
                valor = Poda_AlfaBeta(siguiente_hijo, jugador, PROFUNDIDAD_ALFABETA-1,last_c_piece, last_id_piece, last_dice, alpha, beta);

                if(valor < beta){
                    beta = valor;
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                }

                if(beta <= alpha){
                    break;
                }

                siguiente_hijo = actual.generateNextMove(last_c_piece, last_id_piece, last_dice);

            }

            return beta;
        }
    }
    /*
    while(!poda and !(siguiente_hijo == actual)){
        if(jugador == actual.getCurrentPlayerId()){
                cout << "entra en hijo" << endl;
                valor = Poda_AlfaBeta(siguiente_hijo, jugador, PROFUNDIDAD_ALFABETA-1, last_c_piece, last_id_piece, last_dice, alpha, beta);
                if(valor >= beta)
                    poda = true;
                if(valor > alpha){
                    alpha = valor;
                    if(PROFUNDIDAD_ALFABETA == 2){
                        c_piece = last_c_piece;
                        id_piece = last_id_piece;
                        dice = last_dice;
                    }
                }
                siguiente_hijo = actual.generateNextMove(last_c_piece, last_id_piece, last_dice);
                
                return alpha;
        }else{
                cout << "entra en hijo feo" << endl;
                valor = Poda_AlfaBeta(siguiente_hijo, jugador, PROFUNDIDAD_ALFABETA-1,last_c_piece, last_id_piece, last_dice, alpha, beta);
                if(valor <= alpha)
                    poda = true;
                if(valor < beta)
                    beta = valor;
                siguiente_hijo = actual.generateNextMove(last_c_piece, last_id_piece, last_dice);

                return beta;
        }
    }
    */

}


/*
Hacia abajo se propaga alpha en alpha y beta en beta
En los nodos min solo se modifica beta y se devuelve beta +inf
En los nodos maxa solo se modifica alpha y se devuelve alpha -inf
Si alpha >= beta se poda
alpha -> max  = -inf
beta -> min = +inf


*/

/*

Optimizacion cuello de botella

La division operacion mas costosas saber sustituir

Las multiplicaciones por multiplos de dos son menos costosas

lea ecx,[eax+eax]
lea eax,[ecx+eax*8]

Desenrollado de bucles: Ventajas, y cuanto reduce num saltos

Cómo evitar código ambiguo o sus efectos:
 Utilizar variables locales en lugar de punteros
 Utilizar variables globales si no se pueden utilizar las locales
 Poner las instrucciones de almacenamiento después o bastante
antes de las de carga de memoria.

Mejor que un dato no ocupe dos lineas de cache

Memoria asociatica: Problemas, tamaño de cache entre vias = separacion de datos

Reducir numero de saltos, salto condicional evita saltos.

Sentencias switch si tenemos case con menos probabilidad por al principio, si se hace busqueda binaria la
reorganizacion influye como tabla de saltos no.

Cmov, SET

*/
