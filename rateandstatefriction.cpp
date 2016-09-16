#include "rateandstatefriction.h"
#include "node.h"
#include <cmath>
#include <iostream>
using namespace std;

RateAndStateFriction::RateAndStateFriction(){

}

RateAndStateFriction::~RateAndStateFriction(){

}

void RateAndStateFriction::modifyParent(weak_ptr<Node> parent){
    double parentVelocityPrevious = parent.lock()->getVelocityPreviousTimeStep();
    double parentVelocity = parent.lock()->getVelocity();
    double tangentialForce = parent.lock()->getTangentialForce();
    double normalForce = parent.lock()->getNormalForce();
    double mu;

    mu = m_mu0 + m_A*log(abs(parent.lock()->getVelocity())/m_v0) + m_B*log(m_v0*m_theta/m_dc);
    m_frictionForce = -mu*parent.lock()->getNormalForce()*sign(parent.lock()->getVelocity());

    if(mu<m_mu0 && abs(parentVelocity)<m_v0){
        //mu = m_mu0;
    }

    //Test if node is unstuck or stuck
    if(m_isStatic){
        if(tangentialForce>(normalForce*mu)){
            m_isStatic = false;
            m_frictionForce = -normalForce*mu*sign(tangentialForce);
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
            m_frictionForce = -normalForce*mu*sign(parentVelocity);
        }
    }
    parent.lock()->setTangentialForce(tangentialForce+m_frictionForce);

}

void RateAndStateFriction::integrateTimeDependentParameters(weak_ptr<Node> parent, double dt){
    //dtheta/dt = 1 - v*theta/dc
    m_theta = m_theta + (1 - abs(parent.lock()->getVelocity()) * m_theta/m_dc)*dt;
}
