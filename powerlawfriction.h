#ifndef POWERLAWFRICTION_H
#define POWERLAWFRICTION_H
#include <memory>
#include "frictionlaw.h"
using namespace std;

class PowerLawFriction : public FrictionLaw
{
public:
    PowerLawFriction();
    ~PowerLawFriction();

    double getFrictionConstant();
    double getPowerLawcoefficient();

    void setfrictionConstant(double frictionConstant);
    void setPowerLawCoefficient(double poerLawCoefficient);

    void modifyParent(weak_ptr<class Node> parent);

private:
    double m_frictionConstant;
    double m_powerLawCoefficient;
    double m_frictionForce;

};

#endif // POWERLAWFRICTION_H
