#include "absoluteviscosity.h"
#include "node.h"

AbsoluteViscosity::AbsoluteViscosity(){

}

AbsoluteViscosity::~AbsoluteViscosity(){

}

void AbsoluteViscosity::setViscosity(double viscosity){
    m_viscosity = viscosity;
}

double AbsoluteViscosity::getViscosity(){
    return m_viscosity;
}


void AbsoluteViscosity::modifyParent(weak_ptr<Node> parent){

    double parentVelocity = parent.lock()->getVelocity();
    double tangentialForce = parent.lock()->getTangentialForce();
    double normalForce = parent.lock()->getNormalForce();

    m_frictionForce = -m_viscosity*parentVelocity;
    parent.lock()->setTangentialForce(tangentialForce+m_frictionForce);

}
