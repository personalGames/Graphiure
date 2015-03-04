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
//#include <event.h>

#include "Component.h"

namespace GUI {

    class Container : public Component {
    public:
        Container();
        virtual ~Container();
        
        void pack(Component* component);
        virtual bool isSelectable() const;
        virtual void handleEvent(const sf::Event& event);
        
    private:
        std::vector<Component*> children;
        int selectedChild;
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        bool hasSelection() const;
        void select(std::size_t index);
        void selectNext();
        void selectPrevious();
    };
}

#endif	/* CONTAINER_H */

