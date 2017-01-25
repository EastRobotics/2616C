task macroSelection() {
	while(true) {
		if(vexRT[Btn5D]) {
			claw1.desiredPos = wide;
			while(vexRT[Btn5D]) {

			}
		}
		if(vexRT[Btn5U]) {
			claw1.desiredPos = closed;
			while(vexRT[Btn5U]) {
			}
		}
		if(vexRT[Btn6U]) {
			lift1.tolerance =200;
			lift1.desiredPos = CoG;

			while(vexRT[Btn6U]) {
			}
		}
		if(vexRT[Btn6D]) {
			lift1.tolerance =300;
			lift1.desiredPos = min;
			while(vexRT[Btn6D]) {
			}
		}
		if (vexRT[Btn7R] && vexRT[Btn8L]){
			throwObjects();
			wait1Msec(100);
		}
	}
}
task incDecTolerance() {
	while(true) {
		if(vexRT[Btn7U]) {
			claw1.tolerance +=5;

			while(vexRT[Btn7U]) {}
		}

		if(vexRT[Btn7D]){
			claw1.tolerance -= 5;
			while(vexRT[Btn7D]) {

			}
		}
		wait1Msec(100);
	}
}
