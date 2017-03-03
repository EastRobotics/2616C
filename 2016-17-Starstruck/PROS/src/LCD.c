#include "main.h"
void waitForRelease() {
	while(lcdReadButtons(uart1) != 0){}
	delay(5);
}
char Auton[6][3] = {"R1","R2","R3","L1","L2","L3"};
int wAuton;
void runLCD(void* ignore) {
	//bLCDBacklight = true;                                    // Turn on LCD Backlight
	char mainBattery[12], backupBattery[12], selector[12],liftSensor[12], clawSensor[12];
	float PEBatteryLevel;
	BotLocation bLoc;

	wAuton = 0;

	while(true) {                                                        // An infinite loop to keep the program running until you terminate it
		PEBatteryLevel = (float)analogRead(aPwrExpandSignal)/275;
		//Display the Primary Robot battery voltage
		sprintf(mainBattery, "P:%1.2f%c E:%1.2f%c ", powerLevelMain()/1000.0,'V',PEBatteryLevel,'V'); //Build the value to be displayed
		lcdSetText(uart1, 1, mainBattery);

		//Display the Backup battery voltage
		sprintf(backupBattery, "B:%1.2f%c Auton:%s", powerLevelBackup()/1000.0, 'V',Auton[wAuton]);    //Build the value to be displayed
		lcdSetText(uart1, 2, backupBattery);
		if(lcdReadButtons(uart1) == LCD_BTN_LEFT || lcdReadButtons(uart1) == LCD_BTN_RIGHT)
		{
			while(lcdReadButtons(uart1) != LCD_BTN_CENTER) {
				lcdClear(uart1);
				if(lcdReadButtons(uart1) == LCD_BTN_LEFT) {
					waitForRelease();
					wAuton = (wAuton > 0) && (wAuton <=5 )? wAuton - 1:wAuton <= 0?5:wAuton >= 5? 0:0;
				}
				if(lcdReadButtons(uart1) == LCD_BTN_RIGHT) {
					waitForRelease();
					wAuton = ((wAuton >= 0) && (wAuton <5 ))? wAuton + 1:wAuton <= 0?5:wAuton >= 5? 0:0;
				}
				lcdSetText(uart1, 1, "Autonomous Selection");
				sprintf(selector, "%s",Auton[wAuton]);
				lcdSetText(uart1, 2, selector);
				printf("Auton: %s - %i",Auton[wAuton], wAuton);
				delay(100);
			}
		}
		// printf("Buttons %i",lcdReadButtons(uart1));
		if(lcdReadButtons(uart1) == 5) {
			while(lcdReadButtons(uart1) != LCD_BTN_CENTER) {
				sprintf(clawSensor, "Claw:%i ", encoderGet(encClaw)); //Build the value to be displayed
				//Display the Backup battery voltage
				refreshBotLocation(&bLoc);
				sprintf(liftSensor, "Lift: %i  Odom: %3.2f in", analogRead(aLiftPot),bLoc.y_pos);    //Build the value to be displayed
        lcdSetText(uart1, 1, clawSensor);
        lcdSetText(uart1, 2, liftSensor);
				delay(100);
			}
		}
		//Short delay for the LCD refresh rate
		delay(100);
	}
}
