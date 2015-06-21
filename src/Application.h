/* 
 * File:   Application.h
 * Author: dorian
 *
 * Created on 28 de diciembre de 2014, 13:23
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.h"
#include "StateStack.h"
#include "IDFonts.h"
#include "SystemManager.h"

#include "IncludeStates.h"

#include "FrameClock.h"
#include "ClockHUD.h"

class Application {
public:
    /**
     * Constructor
     */
    Application();
    /**
     * Inicializa la aplicación
     */
    void run();

private:
    /**
     * Tiempo por frame
     */
    static const sf::Time timePerFrame;
    /**
     * Ventana de la aplicación
     */
    sf::RenderWindow window;
    /**
     * Texturas de la aplicación
     */
    ResourceHolder<std::string, sf::Texture> textures;
    /**
     * Fuentes de la aplicación
     */
    ResourceHolder<IDFonts, sf::Font> fonts;
    /**
     * Procesa la entrada del usuario
     */
    void processInput();
    /**
     * Actualiza
     * @param dt tiempo pasado entre frame y frame
     */
    void update(sf::Time dt);
    /**
     * Renderiza la aplicación
     */
    void render();
    /**
     * Registra los estados de la aplicación
     */
    void registerStates();
    /**
     * Carga las texturas
     */
    void loadTextures();
    /**
     * Carga las fuentes
     */
    void loadFonts();
    /**
     * Inicializa los sistemas del motor
     */
    void setSystemManager();

    /**
     * Reloj
     */
    sfx::FrameClock clock;
    /**
     * Interfaz para control de frames y otros datos
     */
    ClockHUD* hud;

    /*
     * Jugador
     */
    Player player;
    /**
     * Gestor de sistemas
     */
    SystemManager systemManager;
    /**
     * Pila de estados
     */
    StateStack stateStack;
    /**
     * Reproductor de música de la aplicación
     */
    MusicPlayer mMusic;
    /**
     * Reproductor de sonidos de la aplicación
     */
    SoundPlayer mSounds;
    /**
     * Nombre del nivel en el que está en la aplicación
     */
    std::string nameLevel;

};

#endif	/* APPLICATION_H */

