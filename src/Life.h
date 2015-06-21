/* 
 * File:   Life.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 20:18
 */

#ifndef LIFE_H
#define	LIFE_H

/**
 * Clase representando una vida
 */
class Life {
public:
    /**
     * Constructor por defecto dejando una vida de 100 unidades
     */
    Life();
    /**
     * COnstructor especificando el máximo de vida
     * @param maxLife máximo de vida
     */
    Life(int maxLife);
    /**
     * Constructor copia
     * @param orig vida a copiar
     */
    Life(const Life& orig);
    /**
     * Destructor
     */
    virtual ~Life();
    /**
     * Devuelve la vida actual
     * @return devuelve la vida actual que le queda
     */
    inline int getActualLife() const {
        return actualLife;
    }

    /**
     * Setea la vida
     * @param actualLife vida actual a setear
     */
    inline void setActualLife(int actualLife) {
        this->actualLife = actualLife;
    }

    /**
     * Devuelve la vida máxima
     * @return vida máxima
     */
    inline int getMaxLife() const {
        return maxLife;
    }

    /**
     * Setea la vida máxima
     * @param maxLife vida máxima a setear
     */
    inline void setMaxLife(int maxLife) {
        this->maxLife = maxLife;
    }
    
    /**
     * Establece un daño, decrementa la vida en las unidades especificadas
     * @param damage unidades a decrementar la vida
     */
    void damage(int damage);
    /**
     * Determina si está vivo, es decir, si la vida es mayor de 0
     * @return true si está vivo
     */
    bool isAlive();

    
private:
    /**
     * Máximo vida
     */
    int maxLife;
    /**
     * Vida actual
     */
    int actualLife;

};

#endif	/* LIFE_H */

