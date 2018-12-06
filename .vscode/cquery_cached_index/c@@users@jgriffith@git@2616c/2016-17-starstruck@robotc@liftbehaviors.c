typedef struct {
	int tolerance;
	int desiredPos;
	int currentPos;
	int speed;
	int enabled;
	int difference;
} liftControl;
liftControl lift1;
bool liftMan = true;
task liftPos() {
	lift1.desiredPos = SensorValue[liftPot];
	while(true) {
		if(vexRT[Btn7U] && vexRT[Btn8U]) {
			liftMan = !liftMan;
			lift = 0;
			while(vexRT[Btn7U] & vexRT[Btn8U]) {}
		}
    SensorValue[liftlight] = liftMan ? 1 : 0;
		lift1.currentPos = SensorValue[liftPot];
		lift1.difference = abs(lift1.desiredPos - lift1.currentPos);
		//	writeDebugStreamLine(" Lift D: %d | C: %d | Diff: %d | S: %d |", lift1.desiredPos, lift1.currentPos, lift1.difference, lift1.speed);
		if(liftMan) {
			if(lift1.difference > lift1.tolerance) {
				if(motor[liftLB] == 0 || vexRT[Btn6U]) {
					lift = ((lift1.desiredPos - lift1.currentPos > 0) ? ( (lift1.difference > lift1.tolerance + 250) ? -lift1.speed : -(lift1.speed)/2 ) : ((lift1.difference > lift1.tolerance + 250) ? lift1.speed : lift1.speed/2 ));

				}
				}else {
				lift = 0;
			}
		}
		if(!liftMan) {
			if(vexRT[Btn6D]) {
				lift = lift1.speed;
				} else if(vexRT[Btn6U]){
				lift = -lift1.speed;
				} else {
				lift = 0;
			}
		}
		wait1Msec(100);
	}
}
void throwObjects() {
	lift1.speed =127;
	claw1.speed=127;
	lift1.desiredPos = liftthrow;
  while (lift1.currentPos <CoG-350){}
  claw1.desiredPos = clawthrow;
}
