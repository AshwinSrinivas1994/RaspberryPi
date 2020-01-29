#include <stdio.h>
#include <wiringPi.h>
#include <stdbool.h>

#define FADER_PIN 18 //sets the voltage "flash" pin to GPIO 18, the PWM pin
#define BUTTON_PIN 16 //sets the button press pin to GPIO 16
bool running = true;

//Setup a ISR to halt pin flash upon button press
void halt_button(void)
{
running = false;
}

//Start Main Program
int main (void)
{
wiringPiSetupGpio () ;
pinMode (FADER_PIN, PWM_OUTPUT) ;
pinMode (BUTTON_PIN, INPUT);
wiringPiISR(BUTTON_PIN, INT_EDGE_RISING, &halt_button);//invoke the ISR


while (running)
{
for(int i=1; i<=1023; i++)
{
pwmWrite(FADER_PIN,i);
delay(1000);
}
for(int i=1022; i>=0; i--)
{
pwmWrite(FADER_PIN,i);
delay(1000);
}
}

return 0 ;
}
