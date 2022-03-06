/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include <pigpio.h>
#include <iostream>
#include <thread>
#include <fstream>

class MyServer : public TCPserver{
public:
	MyServer(int portNmb, int maxSizeData) : TCPserver(portNmb,maxSizeData){
	};
	string myResponse(string inputStr);
	void checkCon();


private:

	void ansteuerung(string inputStr);
	//void checkCon();
	int power = 0;
	int powerMotorEinzel= 0;
	int maxpower = 100;
	char lastCommand;
	int con=0;
	bool checkcon = false;
	//string response;

};

using namespace std;
int main(){
	srand(time(nullptr));
	MyServer srv(2022,25);
	thread check(&MyServer::checkCon,&srv);
	//check.detach();
	srv.run();
	check.join();
	sleep(2);

}


string MyServer::myResponse(string inputStr){

	if(inputStr.compare("run")==0){
		con=1;
		return string("run");
	}
	if(inputStr.compare("connected")==0){
		checkcon=true;
		return string("conOk");
	}

	if(con==0){
		cout<<"Verbindung verloren!\n";
		return string("lost");
	}

	return string("unknown Command");


}

void MyServer::checkCon(){
	while(true){
		if(checkcon==true){
			break;
		}
	}
	while(checkcon){
		con=0;
		sleep(2);
		if(con==0){
			checkcon=false;
			cout<<"Verbindung verloren!\n";
		}
	}
}

