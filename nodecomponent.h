#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H
#include <memory>
#include <vector>
using namespace std;

class NodeComponent
{
public:
    NodeComponent();
    virtual void modifyParent(weak_ptr<class Node> node);
    virtual void addParent(weak_ptr<class Node> node);
    virtual void integrateTimeDependentParameters(weak_ptr<class Node> node, double dt);
    int getNodePriority();
    vector<weak_ptr<class Node>> getParents();

protected:
    int m_nodePriority;
    vector<weak_ptr<class Node>> m_parents;
};

#endif // NODECOMPONENT_H
