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
//#include <pigpio.h>

class MyServer : public TCPserver{
public:
	MyServer(int portNmb, int maxSizeData) : TCPserver(portNmb,maxSizeData){
	};

protected:
	string myResponse(string inputStr);

};
int main(){
	srand(time(0));
	Myserver srv(2022,25);
	/*
	if (gpioInitialise()<0){
	        return 1;
	    }
	/*
	gpioSetMode(6, PI_OUTPUT);
	gpioSetMode(13,PI_ALT0);
	gpioSetPWMrange(13, 255);
	gpioPWM(13, 25);
	srv.run();
	*/
}

string MyServer::myResponse(string inputStr){
	string response;

	if(inputStr.compare("w")==0){
		/*
		gpioWrite(6, 1);
		gpioPWM(13, 25);
		*/
		sleep(4);
		return string("w");
	}

	return response;


}
/*
 * #include <unistd.h>
#include <pigpio.h>
#include <iostream>
using namespace std;
int main(){

    if (gpioInitialise()<0){
        return 1;
    }
    int x;
    gpioSetMode(6, PI_OUTPUT);
    gpioSetMode(5, PI_OUTPUT);
    gpioSetMode(26, PI_OUTPUT);
    gpioWrite(6, 1);
    gpioWrite(5, 1);
    gpioWrite(26, 1);
    gpioSetMode(13,PI_ALT0);
    gpioSetMode(19,PI_ALT5);
    gpioSetPWMrange(13, 255);
    gpioSetPWMrange(19, 255);

    /*gpioPWM(13, 25);
    gpioPWM(19, 25);
    sleep(4);
    gpioPWM(19, 0);
    gpioPWM(13, 50);
    gpioPWM(19, 50);
    sleep(4);
    gpioPWM(13, 75);
    gpioPWM(19, 75);
    sleep(4);

    cin >>x;
    while(x!=3){
        if(x==1){
        gpioPWM(13, 25);
        sleep(4);
        gpioPWM(13, 50);
        sleep(4);
        gpioPWM(13, 75);
        sleep(4);
        }
        if(x==0){
            gpioPWM(19, 25);
            sleep(4);
            gpioPWM(19, 50);
            sleep(4);
            gpioPWM(19, 75);
            sleep(4);
        }
        if(x==2){
            gpioPWM(13, 10);
            gpioPWM(19, 25);
            sleep(5);
            gpioPWM(13, 25);
            gpioPWM(19, 10);
            sleep(5);
        }
        gpioPWM(19, 0);
        gpioPWM(13, 0);
        cout<<"in\n";
        cin >>x;

    }

    gpioTerminate();


}
*/

