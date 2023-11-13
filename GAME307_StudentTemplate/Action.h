#pragma once
#include "DecisionTreeNode.h"

enum class ACTION_SET {Seek, Arrive, Flee, Do_Nothing};

class Action :
    public DecisionTreeNode
{
private:
    ACTION_SET label;

public:
    Action() { label = ACTION_SET::Do_Nothing; }
    Action(ACTION_SET label_) { label = label_; }
    ~Action() {}

    DecisionTreeNode* makeDecision() { return this; }
    ACTION_SET getLabel() const { return label; }
};

