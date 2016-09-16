#include "nodecomponent.h"

NodeComponent::NodeComponent()
{

}

void NodeComponent::modifyParent(weak_ptr<class Node> parent){

}

void NodeComponent::integrateTimeDependentParameters(weak_ptr<class Node> parent, double dt){

}

int NodeComponent::getNodePriority(){
    return m_nodePriority;
}

void NodeComponent::addParent(weak_ptr<class Node> node){
    m_parents.push_back(node);
}

vector<weak_ptr<class Node>> NodeComponent::getParents(){
    return m_parents;
}
