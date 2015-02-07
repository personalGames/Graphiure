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
    
    class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    public:
        Component();
        virtual ~Component();
        
        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();
        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();
        virtual void handleEvent(const sf::Event& event) = 0;
        
    private:
        bool selected;
        bool actived;

    };
    
}

#endif	/* COMPONENT_H */

