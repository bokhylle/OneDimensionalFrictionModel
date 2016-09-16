#ifndef AMONTONSCOULOMB_H
#define AMONTONSCOULOMB_H
#include "frictionlaw.h"

class AmontonsCoulomb : public FrictionLaw
{
public:
    AmontonsCoulomb();
    ~AmontonsCoulomb();
    void setIsStatic(bool isStatic);
    void setStaticFrictionCoefficient(double staticFrictionCoefficient);
    void setDynamicFrictionCoefficient(double dynamicFrictionCoefficient);

    bool getIsStatic();
    double getStaticFrictionCoefficient();
    double getDynamicFrictionCoefficient();

    void modifyParent(weak_ptr<class Node> parent);

private:
    bool m_isStatic;
    double m_staticFrictionCoefficient;
    double m_dynamicFrictionCoefficient;
    double m_frictionForce;

    //double m_parentVelocity;
    //double m_parentVelocityPrevious;
};

#endif // AMONTONSCOULOMB_H
