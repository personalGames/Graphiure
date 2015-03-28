/* 
 * File:   LifeNode.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 20:25
 */

#include "LifeNode.h"

LifeNode::LifeNode(ResourceHolder<std::string, sf::Texture>& texture, Life& life)
: life(&life) {
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(&texture);
    parser->setXML("Media/Data/heart.xml");
    DataUnion data;
    parser->parse(data);
    
    Animation* anim=data.animations->animations->at(0);
    background.play(*anim);
    anim=data.animations->animations->at(2);
    heart.play(*anim);
    anim=data.animations->animations->at(1);
    fill.play(*anim);
    
    delete parser;
}

void LifeNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
}

LifeNode::~LifeNode() {

}
