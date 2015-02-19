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

class TextNode : public SceneNode {
public:
    TextNode(const ResourceHolder<IDFonts, sf::Font>& fonts, const std::string& text);
    void setString(const std::string& text);


private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Text text;
};

#endif	/* TEXTNODE_H */

