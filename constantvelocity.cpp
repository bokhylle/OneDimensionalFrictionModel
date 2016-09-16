#include "constantvelocity.h"
#include <iostream>
#include "node.h"
using namespace std;

ConstantVelocity::ConstantVelocity()
{
    cout << "Constant velocity created" << endl;
}

ConstantVelocity::~ConstantVelocity()
{
    cout << "Constant velocity destroyed" << endl;
}

void ConstantVelocity::modifyParent(weak_ptr<Node> parent){
    parent.lock()->setTangentialForce(0.0);
}
