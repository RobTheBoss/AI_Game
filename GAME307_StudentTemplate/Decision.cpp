#include "Decision.h"

DecisionTreeNode* Decision::makeDecision()
{
    DecisionTreeNode* branch = getBranch();
    return branch->makeDecision();
}

DecisionTreeNode* Decision::getBranch()
{
    if (testValue())
        return trueBranch;
    else
        return falseBranch;
}