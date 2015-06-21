/* 
 * File:   TextNode.h
 * Author: dorian
 *
 * Created on 14 de diciembre de 2014, 15:05
 */

#ifndef TEXTNODE_H
#define	TEXTNODE_H

#include "ResourceHolder.h"
#include "IDFonts.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "SceneNode.h"

/**
 * Nodo para el dibujado de texto
 */
class TextNode : public SceneNode {
public:
    /**
     * Constructor
     * @param fonts fuentes a usar
     * @param text texto a dibujar
     */
    TextNode(const ResourceHolder<IDFonts, sf::Font>& fonts, const std::string& text);
    /**
     * Texto a mostrar
     * @param text texto a setear y mostrar
     */
    void setString(const std::string& text);


private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    /**
     * Texto a mostrar
     */
    sf::Text text;
};

#endif	/* TEXTNODE_H */

