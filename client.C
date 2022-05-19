/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <stdlib.h>
#include <ncurses.h>

#include "SIMPLESOCKET.H"

using namespace std;

int main() {
	srand(time(nullptr));
	TCPclient c;
	string host = "";
	string msg,ch;


	//connect to host

	while(true){
		cout <<"IP-Adresse:"<<endl;
		cin >> host;
		if(c.conn(host , 2022)==true){
			break;
		}
	}

	initscr();
	int i=0;
	bool goOn=1;
	noecho();
	while(goOn){ // send and receive data
		i=getch();
		switch (i){
		case 119:
			msg = string("w\0");
			break;
		case 97:
			msg = string("a\0");
			break;
		case 100:
			msg = string("d\0");
			break;
		case 115:
			msg = string("s\0");
			break;
		case 56:
			msg =string("hoch\0");
			break;
		case 53:
			msg=string("runter\0");
			break;
		case 32:
			msg=string("stopp\0");
			break;
		case 42:
			msg = string("BYEBYE\0");
			goOn = 0;
			break;
		case 109:
			msg = string("hstopp\0");
			goOn = 0;
			break;
		default :
			break;
		}

		printw("\nclient sends: %s",msg.c_str());
		//cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		printw("\ngot response: %s",msg.c_str());
		//cout << "got response:" << msg << endl;

	}
	endwin();
	sleep(2);

}
