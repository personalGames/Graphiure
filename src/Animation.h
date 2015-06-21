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

#ifndef ANIMATION_INCLUDE
#define ANIMATION_INCLUDE

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>

/**
 * Clase para las animaciones, guarda la lista de frames de una animación concreta
 */
class Animation {
public:
    /**
     * Constructor
     */
    Animation();
    /**
     * Añade un frame
     * @param rect rectángulo que define el frame en la imagen
     */
    void addFrame(sf::IntRect rect);
    /**
     * Estblece la imagen donde estan los frames
     * @param texture imagen
     */
    void setSpriteSheet(const sf::Texture& texture);
    /**
     * Devuelve la imagen donde estan los frames
     * @return imagen
     */
    const sf::Texture* getSpriteSheet() const;
    /**
     * Devuelve el número de frames
     * @return numero de frames
     */
    std::size_t getSize() const;
    /**
     * Devuelve el rectángulo del frame especificado
     * @param n numero de frame
     * @return rectangulo del frame
     */
    const sf::IntRect& getFrame(std::size_t n) const;

    /**
     * Establece si la animación es cíclica
     * @param replay true si es cíclica
     */
    inline void setReplay(bool replay) {
        this->replay = replay;
    }

    /**
     * Devuelve si la animación es cíclica
     * @return  true si es cíclica
     */
    inline bool getReplay() {
        return replay;
    }

    /**
     * Establece si hay que esperar a que la animación finalice
     * @param wait true si hay que esperar a que finalice la animación
     */
    inline void setWait(bool wait) {
        this->wait = wait;
    }

    /**
     * Indica si hay que esperar a que la animación finalice
     * @return true si hay que esperar a que finalice la animación
     */
    inline bool getWait() {
        return wait;
    }

private:
    /*
     Lista de frames*
     */
    std::vector<sf::IntRect> m_frames;
    /**
     * Imagen con los frames
     */
    const sf::Texture* m_texture;
    /**
     * SI es cíclico
     */
    bool replay;
    /**
     * SI hay que esperar a que finalice
     */
    bool wait;
};

#endif // ANIMATION_INCLUDE