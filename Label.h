/* 
 * File:   Label.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 19:42
 */

#ifndef LABEL_H
#define	LABEL_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ResourceHolder.h"
#include "IDFonts.h"
#include "Utilities.h"
#include "Component.h"

namespace GUI {
    class Label : public Component {
    public:
        Label(const std::string& text, const ResourceHolder<IDFonts, sf::Font>& fonts);
        virtual ~Label();
        
        virtual bool isSelectable() const;
        void setText(const std::string& text);
        virtual void handleEvent(const sf::Event& event);
        
    private:
        sf::Text text;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };
}

#endif	/* LABEL_H */

