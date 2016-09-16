#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>
#include <vector>
#include <cmath>
#include "integrator.h"
#include "constantvelocity.h"
#include "node.h"
#include "spring.h"
#include "amontonscoulomb.h"
#include "externalforce.h"
#include "absoluteviscosity.h"
#include "rateandstatefriction.h"

using namespace std;

int main(int argc, char *argv[]){

    double dt = 1*pow(10,-6);
    unsigned int numberOfTimeSteps = 10000000;
    unsigned int outputFrequency = 1000;
    unsigned int numberOfNodes = 2;
    double drivingVelocity = 0.01;
    double slope = 0;//M_PI/8;
    double sliderLength = 0.1;
    double sliderCrossSectionalArea = pow(10,-4);
    double sliderYoungsModulus = 2.5*pow(10,9);
    double sliderMass = 0.012;
    double normalLoad = 400;
    double initialVelocity = pow(10,-3);
    double v0 = pow(10,-3);
    double staticFrictionCoefficient = 0.7;
    double dynamicFrictionCoefficient = 0.45;
    double drivingSpringConstant = 8*pow(10,5);

    double normalForce = normalLoad/numberOfNodes;//sliderMass*gravity/numberOfNodes*cos(slope);
    double tangentialForce = 0;//sliderMass*gravity/numberOfNodes*sin(slope);
    double springConstant = (numberOfNodes-1)*sliderYoungsModulus*sliderCrossSectionalArea/sliderLength;

    Integrator integrator;

    //Initialize nodes:
    vector<shared_ptr<Node>> nodes(numberOfNodes);
    for(unsigned int i = 0; i<numberOfNodes; i++){
        nodes[i] = make_shared<Node>();
        nodes[i]->setMass(sliderMass/numberOfNodes);
        nodes[i]->setPosition(double(i)*sliderLength/numberOfNodes);
        nodes[i]->setVelocity(initialVelocity);
    }

    //Initialize external force;
    shared_ptr<ExternalForce> externalForce = make_shared<ExternalForce>();//External force does not go out of scope, so we can update it later
    externalForce->setNormalForce(normalForce);
    externalForce->setTangentialForce(tangentialForce);

    //Initialize friction laws
    for(unsigned int i = 1; i<numberOfNodes; i++){

        //shared_ptr<AmontonsCoulomb> friction = make_shared<AmontonsCoulomb>();
        //friction->setDynamicFrictionCoefficient(dynamicFrictionCoefficient);
        //friction->setStaticFrictionCoefficient(staticFrictionCoefficient);
        //friction->setIsStatic(true);

        //shared_ptr<AbsoluteViscosity> friction = make_shared<AbsoluteViscosity>();
        //friction->setViscosity(1.0);

        shared_ptr<RateAndStateFriction> friction = make_shared<RateAndStateFriction>();
        friction->setA(0.05);
        friction->setB(0.1);
        friction->setDc(pow(10,-3));
        friction->setMu0(0.25);
        friction->setV0(v0);
        friction->setIsStatic(true);
        friction->setTheta(pow(10,-3)/v0);

        nodes[i]->addComponent(move(friction));
        nodes[i]->addComponent(externalForce);

    }

    //Initialize springs:
    for(unsigned int j = 1; j<numberOfNodes-1; j++){
        shared_ptr<Spring>spring = make_shared<Spring>();
        spring->setEquilibriumLength(sliderLength/(numberOfNodes));
        spring->setSpringConstant(springConstant);
        spring->setDampingCoefficient(sqrt(0.1*sliderMass/numberOfNodes*springConstant));
        nodes[j]->addComponent(spring);
        nodes[j+1]->addComponent(spring);
    }

    //First node is a driving node with constant velocity
    shared_ptr<ConstantVelocity> constVel = make_shared<ConstantVelocity>();
    nodes[0]->setVelocity(drivingVelocity);
    nodes[0]->addComponent(move(constVel));
    shared_ptr<Spring>spring = make_shared<Spring>();
    spring->setEquilibriumLength(sliderLength/(numberOfNodes));
    spring->setSpringConstant(drivingSpringConstant);
    spring->setDampingCoefficient(0.0);
    nodes[0]->addComponent(spring);
    nodes[1]->addComponent(spring);

    //Integrate and output:
    ofstream positionFile("position.txt");
    ofstream velocityFile("velocity.txt");
    ofstream springTangentialForceFile("springTangentialForce.txt");
    ofstream totalTangentialForceFile("totalTangentialForce.txt");
    ofstream normalForceFile("normalForce.txt");

    for(int i = 0; i<numberOfTimeSteps/outputFrequency; i++){
        integrator.Integrate(nodes,dt,outputFrequency,"velocityverlet");
        cout << i*outputFrequency*dt << "/" << numberOfTimeSteps*dt << endl;


        if(i==50000){
            nodes[0]->setVelocity(nodes[0]->getVelocity()*2);
        }


        //output:
        for(unsigned int j = 0; j<nodes.size(); j++){
            positionFile << setprecision(10) << nodes[j]->getPosition() << " ";
            velocityFile << setprecision(10) << nodes[j]->getVelocity() << " ";
            nodes[j]->sumComponentContributionsWithPriorityOne();
            springTangentialForceFile << setprecision(10) << nodes[j]->getTangentialForce() << " ";
            nodes[j]->sumComponentContributions();
            totalTangentialForceFile << setprecision(10) << nodes[j]->getTangentialForce() << " ";
            normalForceFile << setprecision(10) << nodes[j]->getNormalForce() << " ";

        }

        positionFile << endl;
        velocityFile << endl;
        springTangentialForceFile << endl;
        totalTangentialForceFile << endl;
        normalForceFile << endl;
    }

    positionFile.close();
    velocityFile.close();
    springTangentialForceFile.close();
    totalTangentialForceFile.close();
    normalForceFile.close();

    return 0;
}
