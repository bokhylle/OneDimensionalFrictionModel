#include "amontonscoulomb.h"
#include <iostream>
#include <cmath>
#include "node.h"
using namespace std;
AmontonsCoulomb::AmontonsCoulomb()
{
    cout << "Amontons-Coulomb friction law created" << endl;
}

AmontonsCoulomb::~AmontonsCoulomb()
{
    cout << "Amontons-Coulomb friction law destroyed" << endl;
}

void AmontonsCoulomb::setIsStatic(bool isStatic){
    m_isStatic = isStatic;
}

void AmontonsCoulomb::setStaticFrictionCoefficient(double staticFrictionCoefficient){
    m_staticFrictionCoefficient = staticFrictionCoefficient;
}

void AmontonsCoulomb::setDynamicFrictionCoefficient(double dynamicFrictionCoefficient){
    m_dynamicFrictionCoefficient = dynamicFrictionCoefficient;
}

bool AmontonsCoulomb::getIsStatic(){
    return m_isStatic;
}

double AmontonsCoulomb::getStaticFrictionCoefficient(){
    return m_staticFrictionCoefficient;
}

double AmontonsCoulomb::getDynamicFrictionCoefficient(){
    return m_dynamicFrictionCoefficient;
}

void AmontonsCoulomb::modifyParent(weak_ptr<Node> parent){

    double tangentialForce = parent.lock()->getTangentialForce();
    double normalForce = parent.lock()->getNormalForce();
    double parentVelocityPrevious = parent.lock()->getVelocityPreviousTimeStep();
    double parentVelocity = parent.lock()->getVelocity();

    //Test if node is unstuck or stuck
    if(m_isStatic){
        if(tangentialForce>(normalForce*m_staticFrictionCoefficient)){
            m_isStatic = false;
            m_frictionForce = -normalForce*m_dynamicFrictionCoefficient*sign(tangentialForce);
        }else{
            m_frictionForce = -tangentialForce;
        }
    }else{
        //Test if node velocity has changed sign (become stuck), then set velocity to zero
        if(sign(parentVelocity)!=sign(parentVelocityPrevious) && sign(parentVelocityPrevious)!=0){
            m_isStatic = true;
            m_frictionForce = -tangentialForce;
            parent.lock()->setVelocity(0.0);
        }else{
            m_frictionForce = -normalForce*m_dynamicFrictionCoefficient*sign(parentVelocity);
        }
    }
    parent.lock()->setTangentialForce(tangentialForce+m_frictionForce);
}
