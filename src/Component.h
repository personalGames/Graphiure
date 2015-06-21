/* 
 * File:   Component.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 19:41
 */

#ifndef COMPONENT_H
#define	COMPONENT_H

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

namespace GUI {
    /**
     * Componente GUI, clase base
     */
    class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    public:
        /**
         * Constructor
         */
        Component();
        /**
         * Destructor
         */
        virtual ~Component();
        /**
         * Devuelve si el componente es seleccionable
         * @return true si es seleccionable
         */
        virtual bool isSelectable() const = 0;
        /**
         * Devuelve si el componente está seleccionado
         * @return true si está seleccionado
         */
        bool isSelected() const;
        /**
         * Selecciona el componente
         */
        virtual void select();
        /**
         * Deselecciona el componente
         */
        virtual void deselect();
        /**
         * Devuelve si el componente está activa
         * @return true si está activo
         */
        virtual bool isActive() const;
        /**
         * Activa el componente
         */
        virtual void activate();
        /**
         * Desactiva el componente
         */
        virtual void deactivate();
        /**
         * Maneja los eventos capturados
         * @param event evento capturado
         */
        virtual void handleEvent(const sf::Event& event) = 0;
        
    private:
        /**
         * Para comprobar si está seleccionado
         */
        bool selected;
        /**
         * Para comprobar si está activo
         */
        bool actived;

    };
    
}

#endif	/* COMPONENT_H */

