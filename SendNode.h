#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFLEN 2048
#define MSGS 5	/* number of messages to send */

class SendNode {
public:
  SendNode(char* server_ip__ip, unsigned int port){
    service_port_ = port;
    server_ip_ = server_ip__ip;
    slen_ = sizeof(remaddr);
  }
  ~SendNode(){
    close(fd_);
  }

  bool ConnectToServer(){
    /* create a socket */

    if ((fd_=socket(AF_INET, SOCK_DGRAM, 0))==-1)
      printf("socket created\n");

    /* bind it to all local addresses and pick any port number */

    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(0);

    if (bind(fd_, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
      perror("bind failed");
      return false;
    }

    memset((char *) &remaddr, 0, sizeof(remaddr));
    remaddr.sin_family = AF_INET;
    remaddr.sin_port = htons(service_port_);
    if (inet_aton(server_ip_, &remaddr.sin_addr)==0) {
      fprintf(stderr, "inet_aton() failed\n");
      return false;
    }
    return true;
  }

  bool SendPose(double x, double y, double yaw){
    PoseMsg msg;
    msg.x = x;
    msg.y = y;
    msg.yaw = yaw;
//    printf("Sending packet to %s port %d\n", server_ip_, service_port_);
    if (sendto(fd_, &msg, sizeof(PoseMsg), 0, (struct sockaddr *)&remaddr, slen_)==-1){
        return false;
    }
    return true;
  }

  bool SendObstacleLocation(double x, double y){
    ObsMsg msg;
    msg.x = x;
    msg.y = y;
//    printf("Sending packet to %s port %d\n", server_ip_, service_port_);
    if (sendto(fd_, &msg, sizeof(ObsMsg), 0, (struct sockaddr *)&remaddr, slen_)==-1){
        return false;
    }
    return true;
  }

private:
	struct sockaddr_in myaddr, remaddr;
	int fd_, slen_;
	char *server_ip_;
	char buf[BUFLEN];
	unsigned int service_port_;

	#pragma pack(1)
	struct PoseMsg {
		PoseMsg(){
			x = 0;
			y = 0;
			yaw = 0;
		}
		const unsigned char id = 1;
		float x;
		float y;
		float yaw;
	};
	#pragma pack()

	#pragma pack(1)
	struct ObsMsg {
		ObsMsg(){
			x = 0;
			y = 0;
		}
		const unsigned char id = 2;
		float x;
		float y;
	};
	#pragma pack()
};
