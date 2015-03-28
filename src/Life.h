/* 
 * File:   Life.h
 * Author: dorian
 *
 * Created on 28 de marzo de 2015, 20:18
 */

#ifndef LIFE_H
#define	LIFE_H

class Life {
public:
    Life();
    Life(int maxLife);
    Life(const Life& orig);
    virtual ~Life();
    
    inline int getActualLife() const {
        return actualLife;
    }

    inline void setActualLife(int actualLife) {
        this->actualLife = actualLife;
    }

    inline int getMaxLife() const {
        return maxLife;
    }

    inline void setMaxLife(int maxLife) {
        this->maxLife = maxLife;
    }
    
    void damage(int damage);
    bool isAlive();

    
private:
    int maxLife;
    int actualLife;

};

#endif	/* LIFE_H */

