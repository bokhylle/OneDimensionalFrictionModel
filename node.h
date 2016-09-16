#ifndef NODE_H
#define NODE_H
#include <vector>
#include <memory>
using namespace std;

class Node
        : public enable_shared_from_this<Node>
{
public:
    Node();
    ~Node();

    void setMass(double mass);
    void setPosition(double position);
    void setVelocity(double velocity);
    void setVelocityPreviousTimeStep(double velocity);
    void setNormalForce(double normalForce);
    void setTangentialForce(double tangentialForce);


    double getPosition() { return m_position; }
    double getVelocity() { return m_velocity; }
    double getVelocityPreviousTimeStep(){ return m_velocityPreviousTimeStep; }
    double getMass(){ return m_mass; }
    double getNormalForce(){ return m_normalForce; }
    double getTangentialForce(){ return m_tangentialForce; }

    void addComponent(shared_ptr<class NodeComponent> nodeComponent);
    void removeComponent(shared_ptr<class NodeComponent> nodeComponent);

    void sumComponentContributions();
    void sumComponentContributionsWithPriorityOne();

    void integrateComponentParameters(double dt);

private:
    double m_mass;
    double m_position;
    double m_velocity;
    double m_velocityPreviousTimeStep;
    double m_normalForce;
    double m_tangentialForce;
    vector<shared_ptr<class NodeComponent>> m_nodeComponents;
};

#endif // NODE_H
