#ifndef FRICTIONLAW_H
#define FRICTIONLAW_H
#include "nodecomponent.h"
#include <memory>

class FrictionLaw : public NodeComponent
{
public:
    FrictionLaw();
    void addParent(weak_ptr<class Node> node);
    int sign(double a);

protected:

};

#endif // FRICTIONLAW_H
