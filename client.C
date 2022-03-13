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
#include <thread>
#include <chrono>

#include "SIMPLESOCKET.H"

class MyClient : public TCPclient{
public:
	bool sendRun=true;
	void checkCon();

};


using namespace std;

int main() {
	srand(time(nullptr));
	MyClient c;
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
	thread check(&MyClient::checkCon,&c);
	while(goOn){ // send and receive data
		i=getch();
		switch (i){
		case 119:
			ch = string("w\0");
			break;
		case 97:
			ch = string("a\0");
			break;
		case 100:
			ch = string("d\0");
			break;
		case 115:
			ch = string("s\0");
			break;
		case 56:
			ch =string("hoch\0");
			break;
		case 53:
			ch=string("runter\0");
			break;
		case 32:
			ch=string("stopp\0");
			break;
		case 27:
			ch = string("BYEBYE\0");
			goOn = 0;
			break;
		default :
			cout<<"\nUnknown Command!"<<endl;
		}

		printw("\nclient sends: %s",ch.c_str());
		//cout << "client sends:" << msg << endl;
		c.sendData(msg = ch);
		msg = c.receive(32);
		printw("\ngot response: %s von 255",msg.c_str());
		//cout << "got response:" << msg << endl;

	}
	endwin();
	sleep(2);
}

void MyClient::checkCon(){
	string msg;
	int x=0;
		while(true){
			if(x<6){
				x++;
				sendData("run");
				msg=receive(32);
				cout<<"sendRun: "<<sendRun<<endl;
				if(msg.compare("run")==0){
					this_thread::sleep_for(chrono::seconds(2));
				}
			}
		}
}

