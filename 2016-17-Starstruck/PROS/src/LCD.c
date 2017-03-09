#include "main.h"
void waitForRelease() {
	while(lcdReadButtons(uart2) != 0) {
		printf("holding\n");
	}
	delay(5);
}
TaskHandle lcdTask;
char Auton[6][3] = {"R1","R2","R3","L1","L2","L3"};
char mainBattery[12], backupBattery[12], selector[12],liftSensor[12], clawSensor[12];
int wAuton;



void runLCD(void* ignore) {                     // Turn on LCD Backlight
	float PEBatteryLevel;
	BotLocation bLoc;
	wAuton = 0;
	while(true) {                               // An infinite loop to keep the program running until you terminate it
		PEBatteryLevel = (float)analogRead(aPwrExpandSignal)/275;
		//Display the Primary Robot battery voltage
		sprintf(mainBattery, "P:%1.2f%s E:%1.2f%s ", powerLevelMain()/1000.0,"V",PEBatteryLevel,"V"); //Build the value to be displayed
		lcdSetText(uart2, 1, mainBattery);

		//Display the Backup battery voltage
		sprintf(backupBattery, "B:%1.2f%s Auton:%s", powerLevelBackup()/1000.0, "V",Auton[wAuton]);    //Build the value to be displayed
		lcdSetText(uart2, 2, backupBattery);

		if(lcdReadButtons(uart2) == LCD_BTN_LEFT || lcdReadButtons(uart2) == LCD_BTN_RIGHT) {
			speakerPlayRtttl("LiftBeep: d=32,o=5,b=108: d");
			printf("left / right");
			while(lcdReadButtons(uart2) != LCD_BTN_CENTER) {
				lcdClear(uart2);
				if(lcdReadButtons(uart2) == LCD_BTN_LEFT) {
					waitForRelease();
					wAuton = (wAuton > 0) && (wAuton <=5 )? wAuton - 1:wAuton <= 0?5:wAuton >= 5? 0:0;
				}
				if(lcdReadButtons(uart2) == LCD_BTN_RIGHT) {
					waitForRelease();
					wAuton = ((wAuton >= 0) && (wAuton <5 ))? wAuton + 1:wAuton <= 0?5:wAuton >= 5? 0:0;
					printf("%f %s\n", (double)wAuton, "hi");
				}
				lcdSetText(uart2, 1, "Autonomous Selection");
				sprintf(selector, "%s",Auton[wAuton]);
				lcdSetText(uart2, 2, selector);
				printf("Auton: %s - %f",Auton[wAuton], (double)wAuton);
				delay(100);
			}
		}

		// printf("Buttons %f",lcdReadButtons(uart2));
		printf("LCDButton:  %d ",lcdReadButtons(uart2));
		if(lcdReadButtons(uart2) == 5) {
			while(lcdReadButtons(uart2) != LCD_BTN_CENTER) {
				sprintf(clawSensor, "Claw:%f ", (double)encoderGet(encClaw)); //Build the value to be displayed
				//Display the Backup battery voltage
				refreshBotLocation(&bLoc);
				sprintf(liftSensor, "Lift: %d  Odom: %3.2f in", analogRead(aLiftPot),bLoc.y_pos);    //Build the value to be displayed
        lcdSetText(uart2, 1, clawSensor);
        lcdSetText(uart2, 2, liftSensor);
				delay(100);
			}
		}
		//Short delay for the LCD refresh rate
		delay(1000);
	}
}
void initLCDFromLCDc() {
	lcdClear(uart2);
	lcdInit(uart2);
	lcdSetBacklight(uart2, true);
	lcdTask = taskCreate(runLCD, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
