#ifndef EXTERNALFORCE_H
#define EXTERNALFORCE_H
#include "forcemodifier.h"
#include <memory>
#include <iostream>
using namespace std;

class ExternalForce : public ForceModifier
{
public:
    ExternalForce();
    ~ExternalForce();

    void setNormalForce(double normalForce);
    void setTangentialForce(double tangentialForce);

    double getNormalForce();
    double getTangentialForce();

    void modifyParent(weak_ptr<Node> parent);

private:
    double m_normalForce;
    double m_tangentialForce;

};

#endif // EXTERNALFORCE_H
