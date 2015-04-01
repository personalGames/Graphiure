/* 
 * File:   XMLDocument.cpp
 * Author: dorian
 * 
 * Created on 1 de abril de 2015, 13:33
 */

#include "XMLDocument.h"

XMLDocument::XMLDocument(std::string path) {
    doc=new tinyxml2::XMLDocument();
    std::vector<char> writable = *convertString(path);
    doc->LoadFile(&writable[0]);
    if (doc->ErrorID() != 0) {
        std::cout << "Error: " << doc->ErrorID() << " - " << doc->ErrorName() << std::endl;
    }

    //delete the created vector
    deleteVector(writable);

}

void XMLDocument::load(std::string path) {
    if(doc==nullptr){
        doc=new tinyxml2::XMLDocument();
    }
    std::vector<char> writable = *convertString(path);
    doc->LoadFile(&writable[0]);
    if (doc->ErrorID() != 0) {
        std::cout << "Error: " << doc->ErrorID() << " - " << doc->ErrorName() << std::endl;
    }

    //delete the created vector
    deleteVector(writable);
}


XMLDocument::~XMLDocument() {
    delete doc;
}

