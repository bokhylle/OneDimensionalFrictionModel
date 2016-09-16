#include "powerlawfriction.h"
#include "node.h"
#include <cmath>

PowerLawFriction::PowerLawFriction()
{

}

PowerLawFriction::~PowerLawFriction()
{

}

void PowerLawFriction::setfrictionConstant(double frictionConstant){
    m_frictionConstant = frictionConstant;
}

void PowerLawFriction::setPowerLawCoefficient(double powerLawCoefficient){
    m_powerLawCoefficient = powerLawCoefficient;
}

double PowerLawFriction::getFrictionConstant(){
    return m_frictionConstant;
}

double PowerLawFriction::getPowerLawcoefficient(){
    return m_powerLawCoefficient;
}

void PowerLawFriction::modifyParent(weak_ptr<Node> parent){
    double parentVelocity = parent.lock()->getVelocity();
    double tangentialForce = parent.lock()->getTangentialForce();
    double normalForce = parent.lock()->getNormalForce();
    m_frictionForce = -normalForce*m_frictionConstant*pow(parentVelocity,m_powerLawCoefficient) * sign(parentVelocity);
    parent.lock()->setTangentialForce(tangentialForce+m_frictionForce);
}


