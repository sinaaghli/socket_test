#include "RecvNode.h"
#include <iostream>

void NewPoseReceived(float x, float y, float yaw){
  std::cout << "got Pose data " << x << " - " << y << " - " << yaw  << std::endl;
}

void NewObsReceived(float x, float y){
  std::cout << "got Obs Data "  << x << " - " << y << std::endl;
}

int main(int argc, char **argv)
{
  unsigned int port = 21234;

  RecvNode node(port);
  node.RegisterPoseUpdateCallBack(&NewPoseReceived);
  node.RegisterObsUpdateCallBack(&NewObsReceived);
  node.InitServer();

  std::cout << "waiting to receive ... " << std::endl;

  while(1){
    // do other stuff
  }
}
