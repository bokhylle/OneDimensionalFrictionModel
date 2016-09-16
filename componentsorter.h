#ifndef COMPONENTSORTER_H
#define COMPONENTSORTER_H
#include "nodecomponent.h"
#include <vector>

class ComponentSorter
{
public:
    ComponentSorter();
    bool operator() (shared_ptr<NodeComponent> a, shared_ptr<NodeComponent> b) {
        return a->getNodePriority() < b->getNodePriority();
    }
};

#endif // COMPONENTSORTER_H
