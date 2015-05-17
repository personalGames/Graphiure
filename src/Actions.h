/* 
 * File:   Actions.h
 * Author: dorian
 *
 * Created on 15 de febrero de 2015, 13:45
 */

#ifndef ACTIONS_H
#define	ACTIONS_H

#include <vector>
#include <string>
#include <algorithm>

enum Actions {
    None,
    Left,
    Right,
    Up,
    Down,
    LeftUp,
    LeftDown,
    RightUp,
    RightDown,
    Move,
    ActionPlayer,
    ActionQuest,
    Attack,
    Dead,
    ActionCount
};

#endif	/* ACTIONS_H */

