#ifndef SPRING_H
#define SPRING_H
#include <memory>
#include "forcemodifier.h"

class Spring : public ForceModifier
{
public:

    Spring();
    ~Spring();

    void setEquilibriumLength(double equilibriumLength);
    void setSpringConstant(double springConstant);
    void setDampingCoefficient(double dampingCoefficient);
    void updateForce();
    double getDampingCoefficient();
    double getEquilibriumLength();
    double getSpringConstant();
    double getForceContribution(weak_ptr<class Node> parent);

    void modifyParent(weak_ptr<Node> parent);

private:

    double m_equilibriumLength;
    double m_springConstant;
    double m_forceOnParentOne;
    double m_forceOnParentTwo;
    double m_dampingCoefficient;
};

#endif // SPRING_H
