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
#include <wchar.h>

namespace GUI {
    /**
     * Etiqueta GUI
     */
    class Label : public Component {
    public:
        /**
         * Constructor
         * @param text texto de la etiqueta
         * @param fonts fuentes que puede usar
         */
        Label(const wchar_t* text, const ResourceHolder<IDFonts, sf::Font>& fonts);
        /**
         * Destructor
         */
        virtual ~Label();
        
        virtual bool isSelectable() const;
        /**
         * Setea el texto de la etiqueta
         * @param text nuevo texto
         */
        void setText(const wchar_t* text);
        /**
         * Setea el texto de la etiqueta
         * @param text nuevo texto
         */
        void setText(const std::string& text);
        
        virtual void handleEvent(const sf::Event& event);
        
    private:
        /**
         * Texto
         */
        sf::Text text;
        
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };
}

#endif	/* LABEL_H */

