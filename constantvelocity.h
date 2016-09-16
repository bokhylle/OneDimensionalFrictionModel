#ifndef CONSTANTVELOCITY_H
#define CONSTANTVELOCITY_H
#include <memory>
#include "frictionlaw.h"

class ConstantVelocity : public FrictionLaw
{
public:
    ConstantVelocity();
    ~ConstantVelocity();

    void modifyParent(weak_ptr<class Node> parent);

private:


};

#endif // CONSTANTVELOCITY_H
