# include "ParchisGUI.h"

#define PI 3.14159265

void ParchisGUI::display()
{
    // El juego se crea dentro de la RenderWindow. Se le pasa tamaño, título y opciones (en este caso, que tenga barra de título y botón de cierre.)
    RenderWindow window(VideoMode(3200, 1600), "SFML works!", Style::Titlebar | Style::Close);
    CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Cursor cursor;

    // Imágenes de texturas.
    Texture tBoard; // Textura del tablero de juego.
    tBoard.loadFromFile("data/textures/parchis_board_resized.png");

    Texture tFichas; // Textura para las fichas.
    tFichas.loadFromFile("data/textures/fichas_parchis_resized.png");

    // Sprites, se generan a partir de una textura y es lo que se visualiza.
    Sprite board(tBoard); // Sprite del tablero.
    bool rotate_board = false; //Variables para rotar el tablero.
    float angle0 = 0.0;

    // Reloj para animaciones (por ejemplo, mover una ficha.)
    Clock animation_clock;
    

    //board.setScale(800.f/3740.f, 800.f/3740.f);

    // Pruebas de cursores. Se puede modificar el tipo de cursor (flecha, mano, reloj, ...) según sobre qué se encuentre el ratón.
    Image iCursorWait, iCursorThink, iCursorHand;
    iCursorThink.loadFromFile("data/cursors/hand_cursor_resized.png");

    Cursor cursorWait, cursorThink, cursorHand;
    cursorThink.loadFromPixels(iCursorThink.getPixelsPtr(), Vector2u(iCursorThink.getSize().x, iCursorThink.getSize().y), Vector2u(0, 0));

    // window.setMouseCursor(cursorThink);

    Sprite ficha1(tFichas); // Sprite para una ficha. Se harían tantos sprites como fichas haya, pero todos se montarían sobre la misma textura, la de las fichas.
    ficha1.setTextureRect(IntRect(0,30,30,30)); // La textura de las fichas contiene las fichas de todos los colores. Seleccionamos el rectángulo (esquina_x, esquina_y, largo, alto) con el color que nos interesa
    //ficha1.setScale(0.25, 0.25);
    int pos_ficha_x = 25;
    int pos_ficha_y = 305;
    ficha1.setPosition(pos_ficha_x, pos_ficha_y); // Posición del sprite dentro de la ventana.

    // Variables para el ejemplo de animación.
    bool animate_ficha = false;
    Vector2f start_anim, end_anim(385, 365);

    // Ejemplo para reproducir músca de fondo (clase Music).
    Music background_theme;
    const string background_theme_file = "data/music/background_theme";

    if(background_theme.openFromFile(background_theme_file + ".wav")){
        background_theme.setLoop(true); // Para reproducir en bucle.

        ifstream loop_file((background_theme_file + ".loop").c_str());
        if(loop_file.good()){
            float loop_start, loop_end;
            loop_file >> loop_start;
            loop_file >> loop_end;
            background_theme.setLoopPoints(Music::TimeSpan(seconds(loop_start), seconds(loop_end - loop_start))); // Se puede elegir los puntos exactos en los que cicle la música de fondo.
            cout << "Added loop points for background theme: " << loop_start << " " << loop_end << endl;
        }
        else cout << "No loop points found for background theme." << endl;
        
        background_theme.setVolume(100.f);
        background_theme.play();
    }

    // Ejemplo para reproducir sonidos Parte 1 (se cargan primero en SoundBuffer, parecido a lo que se hace con las texturas)
    int sound_id = 0;
    vector<SoundBuffer> sound_buffers;
    sound_buffers.resize(4);
    Sound sound;
    
    sound_buffers[0].loadFromFile("data/music/coin.wav");
    sound_buffers[1].loadFromFile("data/music/coin2.wav");
    sound_buffers[2].loadFromFile("data/music/explosion.wav");
    sound_buffers[3].loadFromFile("data/music/teleport.wav");
    
    // sound_buffers[4].loadFromFile("data/music/epic_win.wav");

    // Para girar el tablero (combinar con eventos de ratón)
    View view1(FloatRect(0.f, 0.f, 800.f, 800.f));
    view1.setViewport(FloatRect(0.f, 0.f, 0.5f, 1.0f));
    //view1.setRotation(45.f);
    // view1.setRotation(angle);
    window.setView(view1);
    

    Vector2i pos = Mouse::getPosition(window);
    Vector2f world_pos = window.mapPixelToCoords(pos);
    bool clicked = false;
    Vector2i click_pos = Vector2i(0, 0);

    cout << pos.x << " " << pos.y << endl;
    // cout << ficha1.getGlobalBounds() << endl;
    while(window.isOpen())
    {
        // Bucle principal. Se va refrescando en función de lo que ocurra en el juego.
        pos = Mouse::getPosition(window);
        world_pos = window.mapPixelToCoords(pos);

        Event event;
        // Gestión de colisiones (processCollisions()) para ver sobre qué está el ratón.
        if(ficha1.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: si el ratón está sobre la ficha se ilumina.
            if (cursor.loadFromSystem(sf::Cursor::Hand))
                window.setMouseCursor(cursor);
            ficha1.setColor(Color::White);
        }
        else{
            ficha1.setColor(Color(128,128,128,255));
        

            if(board.getGlobalBounds().contains((Vector2f) world_pos)){
                if (cursor.loadFromSystem(sf::Cursor::Hand))
                    window.setMouseCursor(cursor);
            }
            else{
                if (cursor.loadFromSystem(sf::Cursor::Arrow))
                    window.setMouseCursor(cursor);
                
            }
        }
        // Gestión de eventos (processEvents())
        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            // Ejemplo de manejo de teclas. En este caso desplaza la ficha según la dirección que se pulse. Creo que poca utilidad para el parchís.
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Up){
                    pos_ficha_y -= 1;
                }
                if(event.key.code == Keyboard::Down){
                    pos_ficha_y += 1;
                }
                if(event.key.code == Keyboard::Left){
                    pos_ficha_x -= 1;
                }
                if(event.key.code == Keyboard::Right){
                    pos_ficha_x += 1;
                }
                ficha1.setPosition(pos_ficha_x, pos_ficha_y);
                cout << pos_ficha_x << " " << pos_ficha_y << endl;
            }

            if(event.type == Event::MouseButtonPressed){ // Eventos de ratón.
                cout << pos.x << " " << pos.y << " " << world_pos.x << " " << world_pos.y << endl;
                if(event.mouseButton.button == Mouse::Left){
                    if(clicked==false){
                        clicked = true;
                        click_pos = pos;
                        if(ficha1.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: Al clickar en la ficha se inicia la animación que la mueve.
                            animate_ficha = true;
                            animation_clock.restart();
                            start_anim = ficha1.getPosition();
                        }
                        else if(board.getGlobalBounds().contains((Vector2f) world_pos)){ // Ejemplo: al clickar sobre el tablero y arrastrar, se puede girar.
                            cout << "ESTOY EN PARCHIS" << endl;
                            rotate_board = true;
                            FloatRect board_box = board.getGlobalBounds();
                            Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);
                            angle0 =  atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;
                        }
                    }

                    // Ejemplo para reproducir sonidos Parte 2 (en este caso, con cada click)
                    sound.setBuffer(sound_buffers[sound_id]);
                    sound.play();
                    sound_id = (sound_id + 1) % sound_buffers.size();
                }
            }

            if(event.type == Event::MouseButtonReleased){ // Evento de soltar ratón. Se termina por ejemplo el giro de tablero.
                clicked = false;
                rotate_board = false;
            }
        }

        // Girar tablero si se activó en el evento.
        if(rotate_board){
            FloatRect board_box = board.getGlobalBounds();
            Vector2f board_center(board_box.left + board_box.width / 2, board_box.top + board_box.height / 2);
            
            float angle = atan2(pos.x - board_center.x, pos.y - board_center.y) * 180.f / PI;
            
            view1.rotate(angle - angle0);
            angle0 = angle;
            window.setView(view1);
        }

        // Mover ficha (de forma animada) si se activó en el evento.
        if(animate_ficha){
            float t = animation_clock.getElapsedTime().asMilliseconds();
            if(t > 1000){
                t = 1000;
                animate_ficha = false;
            }
            Vector2f new_ficha_position = (1.f - t/1000) * start_anim + (t/1000) * end_anim;
            ficha1.setPosition(new_ficha_position);
        }

        // Se limpia la ventana y se redibujan los elementos.
        window.clear(Color::White);
        window.draw(board);
        window.draw(ficha1);
        // window.draw(shape);
        window.display();
    }  
}


void ParchisGUI::moveFichas(){
    Vector2f start_anim, end_anim(385, 365);

    Clock animation_clock;


    Texture tFichas; // Textura para las fichas.
    tFichas.loadFromFile("data/textures/fichas_parchis_resized.png");

    Sprite ficha1(tFichas); // Sprite para una ficha. Se harían tantos sprites como fichas haya, pero todos se montarían sobre la misma textura, la de las fichas.
    ficha1.setTextureRect(IntRect(0,30,30,30)); // La textura de las fichas contiene las fichas de todos los colores. Seleccionamos el rectángulo (esquina_x, esquina_y, largo, alto) con el color que nos interesa
    //ficha1.setScale(0.25, 0.25);
    int pos_ficha_x = 25;
    int pos_ficha_y = 305;
    ficha1.setPosition(box2position[{1, box_type::normal, color::none}][0].x, box2position[{1, box_type::normal, color::none}][0].y); // Posición del sprite dentro de la ventana.

    for (int i = 2; i < 68; i++){
        start_anim = ficha1.getPosition();
        float t = animation_clock.getElapsedTime().asMilliseconds();
        if(t > 1000){
            t = 1000;
        }

        ficha1.setPosition(box2position[{i, box_type::normal, color::none}][0].x, box2position[{i, box_type::normal, color::none}][0].y);
    }
}