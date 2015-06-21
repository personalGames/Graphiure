////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef ANIMATEDSPRITE_INCLUDE
#define ANIMATEDSPRITE_INCLUDE

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.h"

/**
 * Clase para reproducir una animación
 */
class AnimatedSprite : public sf::Drawable, public sf::Transformable {
public:
    /**
     * Constructor
     * @param frameTime tiempo entre frames de la animación
     * @param paused por defecto false, establece si está pausado
     * @param looped por defecto true, establece si es cíclico
     * @param wait por defecto false, establece si hay que esperar a que la animación termine
     */
    explicit AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f), bool paused = false, bool looped = true, bool wait=false);

    /**
     * Actualiza la animación
     * @param deltaTime tiempo entre frame y frame
     */
    void update(sf::Time deltaTime);
    /**
     * Establece la animación
     * @param animation animación a setear
     */
    void setAnimation(const Animation& animation);
    /**
     * Establece el tiempo entre los frames de la animación
     * @param time
     */
    void setFrameTime(sf::Time time);
    /**
     * Reproduce la animación
     */
    void play();
    /**
     * Reproduce la animación dada y la setea
     * @param animation
     */
    void play(const Animation& animation);
    /**
     * Pausa la animación
     */
    void pause();
    /**
     * Para la animación
     */
    void stop();
    /**
     * Setea si se espera al final de la animación
     * @param wait true si se espera, false al contrario
     */
    inline void setWait(bool wait){
        this->wait=wait;
    }
    
    /**
     * Devuelve si se espera por
     * @return 
     */
    inline bool getWait(){
        return wait;
    }
    /**
     * Setea si es cíclico
     * @param looped true si es cíclico
     */
    void setLooped(bool looped);
    /**
     * COlorea los vértices
     * @param color
     */
    void setColor(const sf::Color& color);
    
    /**
     * Devuelve la animación
     * @return la animación seteada
     */
    const Animation* getAnimation() const;
    
    sf::FloatRect getLocalBounds() const;
    
    sf::FloatRect getGlobalBounds() const;
    /**
     * Indica si es cíclico
     * @return 
     */
    bool isLooped() const;
    /**
     * Indica si se está reproduciendo
     * @return 
     */
    bool isPlaying() const;
    /**
     * Devuelve el tiempo entre frames de la animación
     * @return 
     */
    sf::Time getFrameTime() const;
    /**
     * Setea el frame indicado
     * @param newFrame el indice del frame a setear
     * @param resetTime por defecto true, si se empieza a contar desde cero el tiempo de frame
     */
    void setFrame(std::size_t newFrame, bool resetTime = true);

private:
    /**
     * Animación
     */
    const Animation* m_animation;
    /**
     * TIempo de frame
     */
    sf::Time m_frameTime;
    /**
     * Tiempo actual transcurrido
     */
    sf::Time m_currentTime;
    /**
     * Frame actual
     */
    std::size_t m_currentFrame;
    /**
     * Si está pausad
     */
    bool m_isPaused;
    /**
     * SI está en bucle
     */
    bool m_isLooped;
    /**
     * Imagen de los frames
     */
    const sf::Texture* m_texture;
    /**
     * Si se espera a que termine
     */
    bool wait;
    /**
     * Vértices del frame
     */
    sf::Vertex m_vertices[4];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // ANIMATEDSPRITE_INCLUDE