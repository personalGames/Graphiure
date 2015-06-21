/* 
 * File:   Container.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 19:41
 */

#ifndef CONTAINER_H
#define	CONTAINER_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <vector>
#include <memory.h>

#include "Component.h"

namespace GUI {
    /**
     * Contenedor GUI
     */
    class Container : public Component {
    public:
        /**
         * Constructor
         */
        Container();
        /**
         * Destructor
         */
        virtual ~Container();
        /**
         * Añade un componente al contenedor
         * @param component componente a añadir
         */
        void pack(Component* component);
        /**
         * Indica si es seleccionable el contenedor
         * @return true si es seleccionable
         */
        virtual bool isSelectable() const;
        /**
         * Procesa la entrada
         * @param event evento a procesar
         */
        virtual void handleEvent(const sf::Event& event);
        /**
         * Limpia la seleccion del contenedor
         */
        void clearSelection();
        
    private:
        /**
         * Lista de componentes hijos
         */
        std::vector<Component*> children;
        /**
         * Índice del hijo seleccionado
         */
        int selectedChild;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        /**
         * Indica si tiene algún hijo seleccionado
         * @return true si hay hijo seleccionado
         */
        bool hasSelection() const;
        /**
         * Selecciona un hijo concreto
         * @param index el hijo a seleccionar
         */
        void select(std::size_t index);
        /**
         * Selecciona el siguiente hijo
         */
        void selectNext();
        /**
         * Selecciona el anterior hijo
         */
        void selectPrevious();
    };
}

#endif	/* CONTAINER_H */

