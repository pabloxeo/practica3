#ifndef __PARCHISGUI_H__
#define __PARCHISGUI_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
#include "Board.h"
#include "Attributes.h"
#include "Parchis.h"
#include "DiceSprite.h"
#include "PieceSprite.h"
#include "ClickableSprite.h"
#include "SpriteAnimator.h"
#include <list>

using namespace sf;
using namespace std;

class ParchisGUI
{
private:
    static const map<Box, vector<Vector2i>> box2position;

    RenderWindow game_window;
    Parchis *model;
    
    //Textures' definitions  
    Texture tBoard;
    Texture tPieces;
    Texture tDices;
    
    //Sprites' definitions
    map <color, vector<PieceSprite>> pieces;
    map <color, vector<DiceSprite>> dices;
    Sprite board;

    //Sprites utilities to reduce the code.
    vector<Sprite*> all_drawable_sprites;
    vector<ClickableSprite*> all_clickable_sprites;

    //Sprites lists separated by views.
    vector<Sprite*> board_drawable_sprites;
    vector<Sprite*> dice_drawable_sprites;

    vector<ClickableSprite*> board_clickable_sprites;
    vector<ClickableSprite*> dice_clickable_sprites;

    // Views
    View board_view;
    View dice_view;

    //Music booleans
    bool music_enabled;
    bool sound_effects_enabled;

    //Click booleans
    bool clicked;

    //List of animations.
    list<SpriteAnimator> animations;

    /**
     * @brief Función que procesa las colisiones del ratón con fichas, dados, etc.
     * 
     */
    void processMouse();

    /**
     * @brief Función que procesa los eventos del ratón.
     * 
     */
    void processEvents();

    /**
     * @brief Función que procesa las animaciones.
     * 
     */
    void processAnimations();

    /**
     * @brief Función que procesa el resto de elementos de la interfaz (música, etc)
     * 
     */
    void processSettings();

    /**
     * @brief Función que refresca la ventana principal.
     * 
     */
    void paint();

    /**
     * @brief Agrupa todos los sprites en un vector común para facilitar dibujado y eventos.
     * 
     */
    void collectSprites();

public:
    ParchisGUI(Parchis & model);
    
    
    /**
     * @brief Bucle principal del juego. 
     * 
     */
    void mainLoop();

    /**
     * @brief Lanzar la ventana.
     * 
     */
    void run();

    void moveFichas(float t, int i, box_type bt, color c, Sprite &);
    void moveFichas(float t, int i_orig, box_type bt_orig, color c_orig, int i_end, box_type bt_end, color c_end, Sprite &);
    void set_color(color my_color, Sprite &);
    void load_player(color my_color, Sprite &ficha1, Sprite &ficha2, Sprite &ficha3, Sprite &ficha4);
    int num_box(int pos_x, int pos_y);


};

#endif
