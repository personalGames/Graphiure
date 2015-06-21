/* 
 * File:   Utilities.h
 * Author: dorian
 *
 * Created on 13 de diciembre de 2014, 17:53
 */

#ifndef UTILITIES_H
#define	UTILITIES_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <string.h>
#include <cmath>
#include <cassert>

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

/**
 * Convert enumerators to strings
 */
std::string toString(sf::Keyboard::Key key);

/**
 * Convierte un elemento en un wide string
 * @param value un elemento
 * @return wide string del elemento
 */
template <typename T>
const std::wstring toString(const T& value);

/**
 * Convierte un elemento en un string
 * @param value elemento
 * @return el string del elemento
 */
template <typename T>
std::string toStringKey(const T& value);

/**
 * Centra el origen (situado en la esquina izquierda superior) en el centro de la imagen
 * @param sprite
 */
void centerOrigin(sf::Sprite& sprite);
/**
 * Centra el origen (situado en la esquina izquierda superior) en el centro del texto
 * @param text
 */
void centerOrigin(sf::Text& text);


/**
 * Conversión a grados
 * @param radian
 * @return grados
 */
float toDegree(float radian);
/**
 * Conversión a radianes
 * @param degree
 * @return radianes
 */
float toRadian(float degree);


/**
 * Genera un número aleatorio desde 0 hasta el número
 * indicado y excluido
 * @param exclusiveMax máximo de generado excluido
 * @return número aleatorio
 */
int randomInt(int exclusiveMax);

/*
 * Longitud de un vector
 */
float length(sf::Vector2f vector);
/**
 * Unidad de un vector
 * @param vector
 * @return 
 */
sf::Vector2f unitVector(sf::Vector2f vector);

/**
 * Needs to ALWAYS free the resulting vector when used
 * Convierte un string a vector de chars
 * @param convert el string a convertir
 * @return el string convertido en un vector de chars
 */
std::vector<char>* convertString(std::string convert);

/**
 * Borra un vector
 * @param deleted vector a borrar
 */
template <class E>
void deleteVector(std::vector<E> &deleted) {
    deleted.clear();
    std::vector<E>(deleted).swap(deleted);
}

/**
 * Divide el string en partess
 * @param s string a dividir
 * @param delim delimitador que separa
 * @param elems vector donde se guarda el resultado
 * @return vector con el resultado
 */
std::vector<std::string> &split(const std::string &s,
        char delim, std::vector<std::string> &elems);


/**
 * 
 * Divide el string en partess
 * @param s string a dividir
 * @param delim delimitador que separa
 * @return vector con los strings separados
 */
std::vector<std::string> split(const std::string &s, char delim);

/**
 * 
 * @param a
 * @param b
 * @return 
 */
inline double Dot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return (a.x * b.x) + (a.y * b.y);
}

/**
 * 
 * @param a
 * @param b
 * @return 
 */
inline double PerpDot(const sf::Vector2f& a, const sf::Vector2f& b) {
    return (a.y * b.x) - (a.x * b.y);
}

/**
 * Comprueba si hay colisión entre dos líneas dadas por dos puntos
 * @param A1 Punto 1 de una recta
 * @param A2 Punto 2 de una recta
 * @param B1 Punto 1 de la otra recta
 * @param B2 Punto 2 de la otra recta
 * @param out opcional, ?
 * @return true si colisionan
 */
bool LineCollision(const sf::Vector2f& A1, const sf::Vector2f& A2,
        const sf::Vector2f& B1, const sf::Vector2f& B2,
        double* out = 0);


#endif	/* UTILITIES_H */

