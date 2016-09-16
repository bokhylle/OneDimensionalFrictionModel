#include "externalforce.h"
#include "node.h"

ExternalForce::ExternalForce()
{
    cout << "externalForce created" << endl;
}

ExternalForce::~ExternalForce()
{
    cout << "externalForce destroyed" << endl;
}

void ExternalForce::setNormalForce(double normalForce){
    m_normalForce = normalForce;
}

void ExternalForce::setTangentialForce(double tangentialForce){
    m_tangentialForce = tangentialForce;
}

double ExternalForce::getNormalForce(){
    return m_normalForce;
}

double ExternalForce::getTangentialForce(){
    return m_tangentialForce;
}

void ExternalForce::modifyParent(weak_ptr<Node> parent){
    //cout << "Modify externalforce" << endl;
    parent.lock()->setNormalForce(parent.lock()->getNormalForce()+m_normalForce);
    parent.lock()->setTangentialForce(parent.lock()->getTangentialForce()+m_tangentialForce);

}
