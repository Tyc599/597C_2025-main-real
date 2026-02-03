#include "main.h"

#include "pros/rtos.hpp"
#include "systems/DriveTrain.hpp"
#include "systems/Intake.hpp"
#include "systems/MobileClamp.hpp"
#include "systems/MatchLoad.hpp"
#include "systems/ColorSort.hpp"

//I love you raul
using namespace pros;


Controller master(E_CONTROLLER_MASTER);
DriveTrain dt = DriveTrain();
Intake it = Intake();
MobileClamp mbc = MobileClamp();
MatchLoad ml = MatchLoad();




/*
lvgl::LV_IMG_DECLARE(normal);
lv_obj_t* bgImg = lv_img_disp(&normal);
*/
char lY,rY,rX = 0;
/*
bool arcade;
inline lv_res_t toggleDriveMode(lv_obj_t* btn)
{
	arcade = !arcade;
    if (arcade) {
		dt.teleMove = [=]{dt.arcadeDrive(lY,rX);};
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Arcade Drive");
		} else {
		dt.teleMove = [=]{dt.tankDrive(lY,rY);};
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Tank Drive");
    }
	btnSetToggled(btn, arcade);
    return LV_RES_OK;
}

bool skills_auton;
inline lv_res_t toggleAutonType(lv_obj_t* btn)
{
	skills_auton = !skills_auton;
	if (skills_auton) {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Skills Auton");
	} else {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Match Auton");
	}
	btnSetToggled(btn, skills_auton);
    return LV_RES_OK;
}

bool right_auton;
inline lv_res_t toggleAutonSide(lv_obj_t* btn)
{
	right_auton = !right_auton;
	if (right_auton) {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Right Auton");
	} else {
		lv_label_set_text(lv_obj_get_child(btn, NULL), "Left Auton");
	}
	btnSetToggled(btn, right_auton);
    return LV_RES_OK;
}
*/
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	/*lv_obj_t* odometryInfo = createLabel(lv_scr_act(), 20, DISP_CENTER, 300, 40, "Odom Info");
	//Odometry odom = Odometry(&dt, &odometryInfo);
*/
	dt.arcadeDrive(lY,rX);/*
	lv_obj_t* driveBtn = createBtn(lv_scr_act(), 50, DISP_CENTER, 300, 20, "Tank Drive", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(driveBtn, LV_BTN_ACTION_CLICK, toggleDriveMode);

	lv_obj_t* autonTypeBtn = createBtn(lv_scr_act(), 80, DISP_CENTER, 300, 20, "Match Auton", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(autonTypeBtn, LV_BTN_ACTION_CLICK, toggleAutonType);

	lv_obj_t* autonSideBtn = createBtn(lv_scr_act(), 110, Display::DISP_CENTER, 300, 20, "Match Left", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_btn_set_action(autonSideBtn, LV_BTN_ACTION_CLICK, toggleAutonSide);
	lv_obj_t* odometryInfo = createLabel(lv_scr_act(), 20, DISP_CENTER, 300, 40, "Odom Info");
	lv_obj_t* pickleT = createLabel(lv_scr_act(), 140, DISP_CENTER, 300, 100,
		"Current pickle high scores (5 min)\nEsteban: 11\nJayleen: 10\nJI: 9");
	*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void debugWait() {
	dt.arcadeDrive(0, 0);
	delay(1000); // change to 500 when running fr
}

void autonomous() {
	// Left Side auton 4 balls top MID and matchLoad
	/*it.intake(); 
	dt.moveHorizontal(24.5,70 );
	delay(500); // move forward for 1 second at 100% speed
	it.intake(); 
	dt.turnAngle(15);
	delay(500);
	dt.moveHorizontal(10,70);
	delay(500);
	dt.moveHorizontal(-3.25,50);
	dt.turnAngle(90);
	dt.moveHorizontal(-6.5,50);
	it.score();
	delay(3000);
	dt.moveHorizontal(35.25,50);
	it.stop();
	delay(250);
	ml.down();
	dt.turnAngle(30);
	dt.moveHorizontal(-5,60);
	dt.moveHorizontal(10,80);
	it.intake();
	delay(2000);
	dt.moveHorizontal(-20,50);
	it.score();
	*/
	
	//programs -> 597C ->  competition -> programming skills -> */
  //  it.intake(); 
	dt.moveHorizontal(16.5,70 );
	delay(500); // move forward for 1 second at 100% speed
	it.intake(); 
	dt.turnAngle(-30);
	delay(500);
	dt.moveHorizontal(20,50);
	delay(500);
	dt.moveHorizontal(-3.65,50);
	dt.turnAngle(-96);
	dt.moveHorizontal(-14.25,60);
	it.score();
	delay(2000);
	dt.moveHorizontal(40,60);
     dt.turnAngle(-45);
	 ml.down();
	 dt.moveHorizontal(10);
	 it.intake();
	/*dt.turnAngle(90);
	dt.moveHorizontal(-6.5,50);
	//it.score();
	delay(3000);
	dt.moveHorizontal(35.25,50);
	//it.stop();
	delay(250);
	ml.down();
	dt.turnAngle(30);
	dt.moveHorizontal(-5,60);
	dt.moveHorizontal(10,80);
	//it.intake();
	delay(2000);
	dt.moveHorizontal(-20,50);
	*///it.score(); 
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
#ifdef COLOR_SORT_DEMO
	// Demo mode: print optical + vision certainties and combined result.
	// Defaults: change these with -D or by editing the macros below.
#ifndef OPTICAL_PORT
#define OPTICAL_PORT 1
#endif
#ifndef VISION_PORT
#define VISION_PORT 1
#endif
#ifndef EXAMPLE_SIG
#define EXAMPLE_SIG 1
#endif
#ifndef OTHER_SIG
#define OTHER_SIG 2
#endif

	// Create Vision and color-code once
	pros::Vision vision_sensor(VISION_PORT);
	pros::vision_color_code_t code1 = vision_sensor.create_color_code(EXAMPLE_SIG, OTHER_SIG);

	while (true) {
		auto optCert = ColorSort::analyzeOptical(OPTICAL_PORT);
		auto visCert = ColorSort::analyzeVisionBySize(VISION_PORT, 1000, code1, 0);
		auto combined = ColorSort::mergeCertainties(optCert, visCert, 0.5);

		printf("OPT pres=%.2f r=%.2f b=%.2f | VIS pres=%.2f r=%.2f b=%.2f | COMB p=%.2f r=%.2f b=%.2f\n",
			   optCert.presence, optCert.red, optCert.blue,
			   visCert.presence, visCert.red, visCert.blue,
			   combined.presence, combined.red, combined.blue);

		delay(200);
	}
#endif
	bool prcsM = false;
	int prcsET = 0;
	bool clampState = false;
	bool loadState = false;
	bool wheelLocked = false;

	while (true) {
		// Set precision mode (dont repeat until half a second)
		if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && (millis() - prcsET > 500)) {prcsM = !prcsM; prcsET = millis();}

		{ // Set input for the drivetrain's teleMove according to precision mode.
			lY = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)/2 : master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			rX = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)/2 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		}

			// Toggle wheel lock with Y (new press) BEFORE processing drive inputs
			if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
				wheelLocked = !wheelLocked;
				dt.setWheelLock(wheelLocked);
				printf("[Main] Wheel lock %s\n", wheelLocked ? "ENABLED" : "DISABLED");
			}

			// Send drive inputs (will be ignored by DriveTrain if wheels are locked)
			dt.arcadeDrive(lY, rX);

		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			clampState = !clampState;
			mbc.changeClampState(clampState);
		}
		if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
			loadState = !loadState;
			ml.changeLoadState(loadState);
		}
		
			
		

		if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
            it.intake();
        } else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
            it.score();
		} else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
            it.outTake();
        } else {
			it.stop();
		}


		delay(20);
	}
}