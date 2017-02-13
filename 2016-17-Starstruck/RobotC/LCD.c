
void waitForRelease()
{
while(nLCDButtons != 0){}
wait1Msec(5);
}

task runLCD()
{
//bLCDBacklight = true;                                    // Turn on LCD Backlight
string mainBattery, backupBattery,selector,liftSensor,clawSensor;
float PEBatteryLevel;
BotLocation bLoc;
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
const short bothButton = 5;

wAuton = 0;

while(true)                                                        // An infinite loop to keep the program running until you terminate it
{
PEBatteryLevel = (float)SensorValue[ pExp ] /275;
clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

//Display the Primary Robot battery voltage
displayLCDString(0, 0, "");
sprintf(mainBattery, "P:%1.2f%c E:%1.2f%c ", nImmediateBatteryLevel/1000.0,'V',PEBatteryLevel,'V'); //Build the value to be displayed
displayNextLCDString(mainBattery);

//Display the Backup battery voltage
displayLCDString(1, 0, "");
sprintf(backupBattery, "B:%1.2f%c Auton:%s", BackupBatteryLevel/1000.0, 'V',Auton[wAuton]);    //Build the value to be displayed
displayNextLCDString(backupBattery);
if(nLCDButtons == leftButton || nLCDButtons == rightButton)
	{
while(nLCDButtons != centerButton)
{
clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
clearLCDLine(1);
if(nLCDButtons == leftButton)
{
waitForRelease();
wAuton = (wAuton > 0) && (wAuton <=5 )? wAuton - 1:wAuton <= 0?5:wAuton >= 5? 0:0;
}
	if(nLCDButtons == rightButton)
{
waitForRelease();
wAuton = ((wAuton >= 0) && (wAuton <5 ))? wAuton + 1:wAuton <= 0?5:wAuton >= 5? 0:0;
}
displayLCDString(0, 0, "");
displayNextLCDString("Autonomous Selection");
displayLCDString(1, 0, "");
sprintf(selector, "%s",Auton[wAuton]);
displayNextLCDString(selector);
writeDebugStreamLine("Auton: %s - %i",Auton[wAuton], wAuton);
wait1Msec(100);
}
}
writeDebugStreamLine("Buttons %i",nLCDButtons);
if(nLCDButtons == bothButton)
	{
	while(nLCDButtons != centerButton)
  {
  clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
  clearLCDLine(1);

 	displayLCDString(0, 0, "");
	sprintf(clawSensor, "Claw:%i ", SensorValue[clawManiple]); //Build the value to be displayed
	displayNextLCDString(clawSensor);

//Display the Backup battery voltage
displayLCDString(1, 0, "");
get_botlocation(bLoc);
sprintf(liftSensor, "Lift: %i  Odom: %3.2f in", SensorValue[liftPot],bLoc.y_pos);    //Build the value to be displayed
displayNextLCDString(liftSensor);
wait1Msec(100);
	}
	}
//Short delay for the LCD refresh rate
wait1Msec(100);
}
}
