#include "mbed.h"
#include "C12832.h"

#include "LM75B.h"
 
C12832 lcd(D11, D13, D12, D7, D10);
//Create an LM75B object at the default address (ADDRESS_0)
LM75B sensor(D14, D15);
 
int main()
{
    //Try to open the LM75B
    if (sensor.open()) {
        printf("Device detected!\n");
 
        while (1) {
            lcd.cls();
            //Print the current temperature
            printf("Temp = %d\n", (int)sensor.temp());
            int temp = sensor.temp();
            lcd.locate(3, 3);
            lcd.printf("Temperature: %d'C", temp);
 
            //Sleep for 0.5 seconds
            ThisThread::sleep_for(1000ms);
        }
    } else {
        error("Device not detected!\n");
    }
}
