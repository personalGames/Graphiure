/* 
 * File:   LifeNode.cpp
 * Author: dorian
 * 
 * Created on 28 de marzo de 2015, 20:25
 */

#include "LifeNode.h"

LifeNode::LifeNode(ResourceHolder<std::string, sf::Texture>& texture, Life& life, sf::Vector2f size)
: life(&life) {
    IXMLParser* parser = IXMLParser::make_parser(TypeParser::ANIMATION);
    parser->setResources(&texture);
    parser->setXML("Media/Data/heart.xml");
    DataUnion data;
    parser->parse(data);
    
    Animation* anim=data.animations->animations->at(0);
    sf::Vector2f ratio(1,1);
    ratio.x=size.x/anim->getFrame(0).width;
    ratio.y=size.y/anim->getFrame(0).height;
    background.play(*anim);
    background.scale(ratio);
    
    anim=data.animations->animations->at(1);
    fill.play(*anim);
    fill.scale(ratio);
    
    
    delete parser;
}

void LifeNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    float percentaje=((float)life->getActualLife())/life->getMaxLife();
    states.transform.scale(percentaje,1);
    target.draw(fill, states);
}

LifeNode::~LifeNode() {

}
