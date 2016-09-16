#include <memory>
#include <vector>
#include <algorithm>
#include "node.h"
#include "nodecomponent.h"
#include "componentsorter.h"

Node::Node()
{

}

Node::~Node(){

}

void Node::setMass(double mass){
    m_mass = mass;
}

void Node::setPosition(double position){
    m_position = position;
}

void Node::setNormalForce(double normalForce){
    m_normalForce = normalForce;
}

void Node::setTangentialForce(double tangentialForce){
    m_tangentialForce = tangentialForce;
}

void Node::setVelocity(double velocity){
    m_velocity = velocity;
}

void Node::setVelocityPreviousTimeStep(double velocity){
    m_velocityPreviousTimeStep = velocity;
}

void Node::addComponent(shared_ptr<NodeComponent> nodeComponent){
    m_nodeComponents.push_back(nodeComponent);
    sort(m_nodeComponents.begin(),m_nodeComponents.end(),ComponentSorter()); //sort based on node priority
    nodeComponent->addParent(shared_from_this());
}

void Node::removeComponent(shared_ptr<NodeComponent> nodeComponent){
    m_nodeComponents.erase(remove(m_nodeComponents.begin(), m_nodeComponents.end(), nodeComponent), m_nodeComponents.end());
    sort(m_nodeComponents.begin(),m_nodeComponents.end(),ComponentSorter()); //sort based on node priority
}

void Node::sumComponentContributions(){

    //Set forces to zero:
    setNormalForce(0.0);
    setTangentialForce(0.0);

    //Loop over NodeComponents (according to their node priority), and invoke the changes to the properties of the node object
    for(unsigned int i = 0; i<m_nodeComponents.size(); i++){
        m_nodeComponents[i]->modifyParent(shared_from_this());
    }

}

void Node::sumComponentContributionsWithPriorityOne(){

    //Set forces to zero:
    setNormalForce(0.0);
    setTangentialForce(0.0);

    //Loop only over components with priority 1
    for(unsigned int i = 0; i<m_nodeComponents.size(); i++){
        if(m_nodeComponents[i]->getNodePriority()==1){
            m_nodeComponents[i]->modifyParent(shared_from_this());
        }
    }

}

void Node::integrateComponentParameters(double dt){
    for(unsigned int i = 0; i<m_nodeComponents.size(); i++){
        m_nodeComponents[i]->integrateTimeDependentParameters(shared_from_this(),dt);
    }
}


