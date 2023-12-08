#include <vector>

class decisionTreeNode
{
public:
	virtual decisionTreeNode* makeDecision() = 0;
};

class action : public decisionTreeNode
{
public:
	decisionTreeNode* makeDecision() override { return this; };
};

class decision : public decisionTreeNode
{
public:
	decisionTreeNode* trueNode{};
	decisionTreeNode* falseNode{};

	virtual decisionTreeNode* getBranch() = 0;
	decisionTreeNode* makeDecision() override { return getBranch()->makeDecision(); };
};

class floatDecision : public decision
{
public:
	float minValue{};
	float maxValue{};
	virtual float testValue() = 0;

	decisionTreeNode* getBranch() override
	{
		if (maxValue >= testValue() && testValue() > minValue)
			return trueNode;
		else
			return falseNode;
	};
};

class boolDecision : public decision
{
public:
	virtual bool testValue() = 0;

	decisionTreeNode* getBranch() override
	{
		if (testValue())
			return trueNode;
		else
			return falseNode;
	}
};
