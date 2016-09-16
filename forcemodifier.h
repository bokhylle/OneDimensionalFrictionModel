#ifndef FORCEMODIFIER_H
#define FORCEMODIFIER_H
#include "nodecomponent.h"
#include <memory>

class ForceModifier : public NodeComponent
{
public:
    ForceModifier();
    void addParent(weak_ptr<class Node> node);
protected:


};

#endif // FORCEMODIFIER_H
