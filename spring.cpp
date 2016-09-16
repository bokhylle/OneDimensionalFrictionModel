#include <iostream>
using namespace std;
#include <cmath>
#include <memory>
#include "spring.h"
#include "node.h"

Spring::Spring()
{
    //Initialize spring with zero equilibrium length and zero spring constant.
    //addSpringPointerToParents();
    //setParents(parentOne,parentTwo);
    //addParent(parentOne);
    //addParent(parentTwo);
    //setEquilibriumLength(0.0);
    //setSpringConstant(0.0);
    //updateForce();
    cout << "spring created" << endl;
}

Spring::~Spring(){
    cout << "spring destroyed" << endl;
}

void Spring::setEquilibriumLength(double equilibriumLength)
{
    m_equilibriumLength = equilibriumLength;
}

void Spring::setSpringConstant(double springConstant)
{
    m_springConstant = springConstant;
}

void Spring::setDampingCoefficient(double dampingCoefficient){
    m_dampingCoefficient = dampingCoefficient;
}

double Spring::getSpringConstant(){
    return m_springConstant;
}

double Spring::getEquilibriumLength(){
    return m_equilibriumLength;
}

double Spring::getDampingCoefficient(){
    return m_dampingCoefficient;
}

void Spring::updateForce(){
    double springLength = (m_parents[1].lock()->getPosition()-m_parents[0].lock()->getPosition());
    double velocityDifference = m_parents[1].lock()->getVelocity() - m_parents[0].lock()->getVelocity();
    double dampingForce = velocityDifference*m_dampingCoefficient;
    m_forceOnParentOne = m_springConstant*(springLength - m_equilibriumLength) + dampingForce;
    m_forceOnParentTwo = -m_forceOnParentOne;
}

double Spring::getForceContribution(weak_ptr<Node> parent){
    updateForce();

    if (parent.lock()==m_parents[0].lock()){
        return m_forceOnParentOne;
    }else if (parent.lock()==m_parents[1].lock()){
        return m_forceOnParentTwo;
    }else{
        perror ("input parent is not a parent of the Spring object");
        return 0;
    }
}

void Spring::modifyParent(weak_ptr<Node> parent){
    //cout << "Modify spring" << endl;
    double force = getForceContribution(parent);
    parent.lock()->setTangentialForce(parent.lock()->getTangentialForce()+force);//Add force to parent

}


