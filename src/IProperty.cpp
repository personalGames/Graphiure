/* 
 * File:   IProperty.cpp
 * Author: dorian // https://github.com/LaurentGomila/SFML/wiki/Tutorial%3A-Object-Properties
 * 
 * Created on 2 de marzo de 2015, 19:42
 */

#include "IProperty.h"
#include <string>

IProperty::IProperty(std::string theType, const std::string thePropertyID) :
mType(theType),
mPropertyID(thePropertyID) {
}

IProperty::~IProperty() {
}

IProperty::Type_t* IProperty::GetType(void) {
    return &mType;
}

const std::string IProperty::GetID(void) const {
    return mPropertyID;
}

void IProperty::SetType(std::string theType) {
    mType = Type_t(theType);
}
