#ifndef _STAREFFECT_H
#define _STAREFFECT_H

#include "StarValue.h"

class StarEffect {
public:
	virtual void Update() { }
	virtual void Next(StarTransition& transition) = 0;
};

#endif