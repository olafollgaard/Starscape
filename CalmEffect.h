#ifndef _CALMEFFECT_H
#define _CALMEFFECT_H

#include "StarEffect.h"

class CalmEffect : public StarEffect {
public:
	void Next(StarTransition& transition);
};

#endif