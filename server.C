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

class MyServer : public TCPserver{
public:
	MyServer(int portNmb, int maxSizeData) : TCPserver(portNmb,maxSizeData){
	};

private:
	string myResponse(string inputStr);
	int power = 0;
	int powerMotorEinzel= 0;
	int maxpower = 100;
	char lastCommand;

};
using namespace std;
int main(){
	srand(time(nullptr));
	MyServer srv(2022,25);

	gpioTerminate();
	if (gpioInitialise()<0){
	        return 1;
	    }

	gpioSetMode(5,PI_OUTPUT); 	//Modus vom Dual Motor Driver
	gpioSetMode(6,PI_OUTPUT); 	//Richtung Motor 1
	gpioSetMode(15,PI_OUTPUT);	//Richtung Motor 3
	gpioSetMode(26,PI_OUTPUT); 	//Richtung Motor 2
	gpioSetMode(13,PI_ALT0); 	//Geschwindigkeit Motor 1
	gpioSetMode(18,PI_ALT0); 	//Geschwindigkeit Motor 3
	gpioSetMode(19,PI_ALT5);	//Geschwindigkeit Motor 2
	gpioSetPWMrange(13,255);
	gpioSetPWMrange(18,255);
	gpioSetPWMrange(19,255);
	gpioWrite(5,1);
	gpioPWM(13,0);
	gpioPWM(18,0);
	gpioPWM(19,0);

	srv.run();
	gpioTerminate();

}


string MyServer::myResponse(string inputStr){

	if(inputStr.compare("w")==0){
		if(lastCommand !='w'){
			lastCommand = 'w';
			power=0;
		}
		if(power < maxpower){
			power=power+5;
			gpioWrite(6, 1);
			gpioWrite(26, 1);
			gpioPWM(13, power);
			gpioPWM(19, power);
		}
		return string("vorwärts");
	}else if(inputStr.compare("s")==0){
		if(lastCommand !='s'){
			lastCommand = 's';
		}
		if(power > 0){
			power=power-5;
			gpioPWM(13, power);
			gpioPWM(19, power);
		}
		return string("bremsen");
	}else if(inputStr.compare("a")==0){
		if(lastCommand !='a'){
			lastCommand = 'a';
			power=0;
			gpioWrite(6, 0);
			gpioWrite(26, 1);
		}
		if(power < maxpower){
			power=power+5;
			gpioPWM(13, power);
			gpioPWM(19, power);
		}
		return string("links");
	}else if(inputStr.compare("d")==0){
		if(lastCommand !='d'){
			lastCommand = 'd';
			power=0;
			gpioWrite(6, 1);
			gpioWrite(26, 0);
		}
		if(power < maxpower){
			power=power+5;
			gpioPWM(13, power);
			gpioPWM(19, power);
		}
		return string("rechts");
	}else if(inputStr.compare("hoch")==0){
		if(powerMotorEinzel < maxpower){
			powerMotorEinzel=powerMotorEinzel+5;
			gpioWrite(15, 1);
			gpioPWM(18, powerMotorEinzel);
		}
		return string("hoch");
	}else if(inputStr.compare("runter")==0){
		if(powerMotorEinzel > 0){
			powerMotorEinzel=powerMotorEinzel-5;
			gpioWrite(15, 0);
			gpioPWM(18, powerMotorEinzel);
		}
		return string("runter");
	}else if(inputStr.compare(0,10,"\0")==0){
		gpioTerminate();
		return string("BYEBYE");
	}else if(inputStr.compare("stopp")==0){
		power=0;
		powerMotorEinzel=0;
		gpioPWM(13, power);
		gpioPWM(19, power);
		gpioPWM(18, powerMotorEinzel);

		return string("stopp");
	}
	return string("unknown command");

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

