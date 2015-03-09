/* 
 * File:   IXMLParser.cpp
 * Author: dorian
 * 
 * Created on 9 de marzo de 2015, 22:55
 */

#include "IXMLParser.h"

IXMLParser* IXMLParser::make_parser(TypeParser choice) {
    switch (choice) {
        case TypeParser::MAP:
            break;
        defaul:
            break;
    };
    
    return nullptr;
}

void IXMLParser::setXML(std::string path) {
    std::vector<char> writable = *convertString(path);

    doc.LoadFile(&writable[0]);
    if (doc.ErrorID() != 0) {
        std::cout << "Error: " << doc.ErrorID() << " - " << doc.ErrorName() << std::endl;
    }

    //delete the created vector
    deleteVector(writable);
}
