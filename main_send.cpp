#include "SendNode.h"
#include <iostream>
#include <thread>

int main(int argc, char **argv)
{
  char* server_ip = "192.168.50.229";
  unsigned int port = 21234;
  SendNode node(server_ip,port);
  if(!node.ConnectToServer()){
    exit(1);
  }

  while(1){
    std::cout << "sent " << std::endl;
    node.SendPose(1.1,2.2,3.3);
    node.SendObstacleLocation(4.4,5.5);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
