#include "frictionlaw.h"
#include "node.h"
#include <cmath>

FrictionLaw::FrictionLaw()
{
    m_nodePriority = 2;
}

void FrictionLaw::addParent(weak_ptr<class Node> node){
    m_parents.push_back(node);
    node.lock()->setVelocityPreviousTimeStep(node.lock()->getVelocity());
}

int FrictionLaw::sign(double a){
    if(a==0){
        return 0;
    }else{
        return a/abs(a);
    }
}

