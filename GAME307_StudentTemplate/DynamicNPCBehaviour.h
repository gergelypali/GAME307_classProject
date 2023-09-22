#ifndef DYNAMIC_NPC_BEHAVIOUR_H
#define DYNAMIC_NPC_BEHAVIOUR_H

#include "DynamicBehaviour.h"

class DynamicNPCBehaviour : public DynamicBehaviour
{
public:
	DynamicNPCBehaviour() {};

	void Update(Body* targetBody, Body* charBody) override;
};

#endif // !DYNAMIC_NPC_BEHAVIOUR_H
