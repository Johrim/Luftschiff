#include <pigpio.h>

int main(){

	if (gpioInitialise()<0){
		        return 1;
		    }
	gpioTerminate();
    return 0;
}
