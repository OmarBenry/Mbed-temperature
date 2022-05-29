#include "mbed.h"
#include "C12832.h"
#include "LM75B.h"

C12832 lcd(D11, D13, D12, D7, D10);
//Create an LM75B object at the default address (ADDRESS_0)
LM75B sensor(D14, D15);
/**
* \file main.cpp
* \brief file main
*
* \author U. F.
*
* \date 29/05/2022
*/
int main()
{
    //Try to open the LM75B
    /*!
    * \brief Prova ad aprire il sensore
    */
    if (sensor.open()) {
        printf("Device detected!\n");
        /*!
        * \var tempMin la temperatura minima
        */
        int tempMin=999;
        /**
        * \var tempMax la temperatura massima
        */
        int tempMax;
        /**
        * \var tempAvg la temperatura media
        */
        int tempAvg=0;
        /**
        * \var indexAvg il numero delle temperature totale
        */
        int indexAvg=0;
        /**
        * \var sumAvg la somma delle temperature
        */
        int sumAvg;
        while (1) {
            //clear the screen
            /**
            * \brief pullisce la scermata del display
            */
            lcd.cls();

            //Print the current temperature
            /**
            * \brief stampa la temperatura nella console
            */
            printf("Temp = %d\n", (int)sensor.temp());

            /**
            * \var temp prende il valore del sensore
            */
            int temp = sensor.temp();

            //sets the temperature changes
            /**
            * \brief imposta le cambiamenti della temperatura
            */
            if(temp<tempMin){
            tempMin=temp;
            }
            if(temp>tempMax){
                tempMax=temp;
            }
            if(tempAvg==0){
                tempAvg=temp;
                indexAvg++;
                sumAvg=temp;
            }
            else if(tempAvg!=0){
                sumAvg=sumAvg+temp;
                tempAvg=sumAvg/indexAvg;
                indexAvg++;
            }

            //print the current, min, max and avg temperature on display lcd
            /**
            * \brief stampa la corrente, minima, massima e media temperatura
            */
            lcd.locate(3, 2);
            lcd.printf("Temperature: %d'C", temp);
            lcd.locate(3, 12);
            lcd.printf("Min: %d'C Max: %d'C", tempMin, tempMax);
            lcd.locate(3, 22);
            lcd.printf("Avg: %d'C", tempAvg);

            //Sleep for 1 second
            /**
            * \brief aspeta 1 seconda
            */
            ThisThread::sleep_for(1000ms);
        }
    } else {
        error("Device not detected!\n");
    }
}
