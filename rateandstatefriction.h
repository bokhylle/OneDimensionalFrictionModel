#ifndef RATEANDSTATEFRICTION_H
#define RATEANDSTATEFRICTION_H
#include "frictionlaw.h"
#include <memory>

class RateAndStateFriction : public FrictionLaw
{
public:
    RateAndStateFriction();
    ~RateAndStateFriction();

    void modifyParent(weak_ptr<class Node> parent);
    void integrateTimeDependentParameters(weak_ptr<Node> parent, double dt);

    void setMu0(double mu0){m_mu0 = mu0;}
    void setA(double A){m_A = A;}
    void setB(double B){m_B = B;}
    void setV0(double v0){m_v0 = v0;}
    void setDc(double dc){m_dc = dc;}
    void setTheta(double theta){m_theta = theta;}
    void setIsStatic(double isStatic){m_isStatic = isStatic;}

private:
    // mu = mu_0 + aln(v/v0) + bln(v0*theta/dc)
    double m_mu0;
    double m_A;
    double m_B;
    double m_v0;
    double m_dc;
    double m_theta;
    double m_frictionForce;
    bool m_isStatic;

};

#endif // RATEANDSTATEFRICTION_H
