#include "forcemodifier.h"

ForceModifier::ForceModifier()
{
    m_nodePriority = 1;
}

void ForceModifier::addParent(weak_ptr<class Node> node){
    m_parents.push_back(node);
}
