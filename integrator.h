#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Integrator
{
public:
    Integrator();
    void Integrate(vector<shared_ptr<class Node>> nodes, double dt, unsigned int numberOfTimeSteps, string algorithm);

private:
    void VelocityVerlet(vector<shared_ptr<class Node>> nodes, double dt);
    void ForwardEuler(vector<shared_ptr<class Node>> nodes, double dt);
    void ForwardEulerCromer(vector<shared_ptr<class Node>> nodes, double dt);

};

#endif // INTEGRATOR_H
