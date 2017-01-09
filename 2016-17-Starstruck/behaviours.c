#define currentPos SensorValue[clawManiple]
#define wide 2350
#define closed 800
typedef struct {
	int tolerance;
	int desiredPos;
	int speed;
	int enabled;
} clawManipulator;
bool clawMan = true;
clawManipulator claw1;
task clawPos() {
	claw1.desiredPos = currentPos;
	while(true) {
		if(clawMan) {
			if(abs(claw1.desiredPos - currentPos) > claw1.tolerance) {
				if(motor[clawL] == 0){
					claw = ((claw1.desiredPos - currentPos > 0) ? claw1.speed : -claw1.speed);
			}}else{claw=0;}
			wait1Msec(20);
			if(vexRT[Btn7L] & vexRT[Btn8R]) {
				clawMan = false;
				claw = 0;
				while(vexRT[Btn7L] & vexRT[Btn8R]) {

				}
			}
		}
		if(!clawMan) {
			if(vexRT[Btn7L] == 1 & vexRT[Btn8R] == 1) {
				clawMan = true;
				while(vexRT[Btn7L] == 1 & vexRT[Btn8R] == 1)
				{}
			}
		}
	}
}

task macroSelection() {
	while(true) {
		switch(vexRT[Btn5D]) {
		case 1:
			claw1.desiredPos = wide;
			break;
		case 0:
			break;
		}
		switch(vexRT[Btn5U]) {
		case 1:
			claw1.desiredPos = closed;
			break;
		case 0:
			break;
		}
	}
}
task incDecTolerance() {
	while(true) {
		switch(vexRT[Btn7U]) {
		case 1:
			claw1.tolerance += 5;
			while(vexRT[Btn7U]) {

			}
			break;
		}
		switch(vexRT[Btn7D]) {
		case 1:
			claw1.tolerance -= 5;
			while(vexRT[Btn7D]) {

			}
			break;
		}
	}
}
