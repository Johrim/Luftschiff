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
	cout <<"IP-Adresse:"<<endl;
	cin >> host;

	//connect to host



	c.conn(host , 2022);

	initscr();
	int i=0;
	bool goOn=1;
	noecho();
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
/*
		if(i == 113){
			msg = string("BYEBYE");
			goOn = 0;
		}
*/
		printw("\nclient sends: %s",ch.c_str());
		//cout << "client sends:" << msg << endl;
		c.sendData(msg = ch);
		msg = c.receive(32);
		printw("\ngot response: %s",msg.c_str());
		//cout << "got response:" << msg << endl;

	}
	endwin();
	sleep(2);
	cout<<"\ngot response: "<<c.receive(32);


/*
	while(true){
		cin>>msg;
		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		if(msg.compare("BYEBYE")==0){
					break;
				}
		sleep(1);

	}
	*/
}


