#include "integrator.h"
#include "node.h"
#include <iostream>
#include <omp.h>
using namespace std;

Integrator::Integrator()
{

}

void Integrator::VelocityVerlet(vector<shared_ptr<Node>> nodes, double dt){
    // x(t+dt) = x(t) + v(t)dt + 0.5*a(t)*dt^2
    // v(t+dt) = v(t) + 0.5*(a(t) + a(t+dt))*dt
    vector<double> forceAtInitialTime(nodes.size());

#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        forceAtInitialTime[i] = nodes[i]->getTangentialForce();
        nodes[i]->setPosition(nodes[i]->getPosition() + nodes[i]->getVelocity()*dt + 0.5*nodes[i]->getTangentialForce()/nodes[i]->getMass()*dt*dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->integrateComponentParameters(dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->sumComponentContributions();
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setVelocityPreviousTimeStep(nodes[i]->getVelocity());
        nodes[i]->setVelocity(nodes[i]->getVelocity() + 0.5*(forceAtInitialTime[i] + nodes[i]->getTangentialForce())/nodes[i]->getMass()*dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->sumComponentContributions();
    }

}

void Integrator::ForwardEuler(vector<shared_ptr<Node>> nodes, double dt){

#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setVelocityPreviousTimeStep(nodes[i]->getVelocity());
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setPosition(nodes[i]->getPosition() + nodes[i]->getVelocity()*dt);
        nodes[i]->setVelocity(nodes[i]->getVelocity() + nodes[i]->getTangentialForce()/nodes[i]->getMass()*dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->integrateComponentParameters(dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->sumComponentContributions();
    }
}


void Integrator::ForwardEulerCromer(vector<shared_ptr<Node>> nodes, double dt){
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setVelocityPreviousTimeStep(nodes[i]->getVelocity());
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setVelocity(nodes[i]->getVelocity() + nodes[i]->getTangentialForce()/nodes[i]->getMass()*dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->integrateComponentParameters(dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->setPosition(nodes[i]->getPosition() + nodes[i]->getVelocity()*dt);
    }
#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->sumComponentContributions();
    }
}

void Integrator::Integrate(vector<shared_ptr<Node>> nodes, double dt, unsigned int numberOfTimeSteps, string algorithm){

#pragma omp parallel for
    for(unsigned int i = 0; i<nodes.size(); i++){
        nodes[i]->sumComponentContributions();
    }

    if(algorithm.compare("forwardeuler") == 0){
        for(unsigned int i = 0; i<numberOfTimeSteps; i++){
            ForwardEuler(nodes,dt);
        }

    }else if(algorithm.compare("forwardeulercromer") == 0){
        for(unsigned int i = 0; i<numberOfTimeSteps; i++){
            ForwardEulerCromer(nodes,dt);
        }

    }else if(algorithm.compare("velocityverlet") == 0){
        for(unsigned int i = 0; i<numberOfTimeSteps; i++){
            VelocityVerlet(nodes,dt);
        }

    }else{
        perror("Integrator not found");
    }

}
