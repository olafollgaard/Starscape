#ifndef _STAREFFECT_H
#define _STAREFFECT_H

#include "Color.h"

class StarEffect {
public:
	virtual void Update() { }
	virtual void Next(transition_t& transition) = 0;
};

#endif