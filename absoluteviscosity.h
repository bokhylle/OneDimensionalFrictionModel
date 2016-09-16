#ifndef ABSOLUTEVISCOSITY_H
#define ABSOLUTEVISCOSITY_H
#include "frictionlaw.h"

class AbsoluteViscosity : public FrictionLaw
{
public:
    AbsoluteViscosity();
    ~AbsoluteViscosity();

    void setViscosity(double viscosity);
    double getViscosity();
    void modifyParent(weak_ptr<class Node> parent);

private:
    double m_viscosity;
    double m_frictionForce;
};

#endif // ABSOLUTEVISCOSITY_H
