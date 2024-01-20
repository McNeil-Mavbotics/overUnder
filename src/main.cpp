#include "main.h"
#include "controls.h"
#include "ports.h"
#include "autoSelect/selection.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	// Credit: https://github.com/kunwarsahni01/Vex-Autonomous-Selector
	selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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

void frontAutonomous()
{
	// drivetrain->moveDistance(1_ft);
	// drivetrain->turnAngle(90_deg);
	// drivetrain->moveDistance(1_ft);
	// drivetrain->turnAngle(-90_deg);
	// drivetrain->moveDistance(1_ft);
	// intake.moveVelocity(-200);
	// trapezoidProfile->generatePath(
	// 	{{0_ft, 0_ft, 0_deg}, {3_ft, 1.5_ft, 0_deg}}, "A");
	// trapezoidProfile->setTarget("A");
	// trapezoidProfile->waitUntilSettled();
	// trapezoidProfile->removePath("A");
	// intake.moveVelocity(-200);
	// pros::delay(1000);
	// intake.moveVelocity(0);
	// drivetrain->moveDistance(-1_ft);
	// drivetrain->turnAngle(-130_deg);
	// drivetrain->getModel()->arcade(-200, 0);
	// trapezoidProfile->generatePath(
	// 	{{0_ft, 0_ft, 0_deg}, {4_ft, 0_ft, 0_deg}}, "A");
	// trapezoidProfile->setTarget("A");
	// trapezoidProfile->waitUntilSettled();
	// trapezoidProfile->removePath("A");
	// // Turn right
	// drivetrain->turnAngle(70_deg);
	// // Drive forward
	// intake.moveRelative(-360, 200);
	// pros::delay(1000);
	// drivetrain->turnAngle(-130_deg);
	// drivetrain->getModel()->arcade(200, 0);
	// pros::delay(1000);
	// drivetrain->moveRaw(0);
	// drivetrain->moveDistance(2.4_ft);
	// intake.moveRelative(720, 200);
	// pros::delay(1000s);
	// drivetrain->turnAngle(100_deg);
	// drivetrain->moveDistance(2.4_ft);
	// intake.moveRelative(-360, 200);
	// pros::delay(1000);
	// drivetrain->turnAngle(150_deg);
	// trapezoidProfile->generatePath(
	// 	{{0_ft, 0_ft, 0_deg}, {1_ft, 0_ft, 0_deg}}, "B");
	// trapezoidProfile->setTarget("B");
	// trapezoidProfile->waitUntilSettled();
	// trapezoidProfile->removePath("B");
	// trapezoidProfile->generatePath(
	// 	{{0_ft, 0_ft, 0_deg}, {0_ft, -4_ft, 0_deg}}, "B");
	// trapezoidProfile->setTarget("B");
	// trapezoidProfile->waitUntilSettled();
	// trapezoidProfile->removePath("B");
	intake.moveRelative(800, 200);
	left_mtr.moveRelative(700, 200);
	right_mtr.moveRelative(700, 200);
	left_mtr.moveRelative(280, 200);
	right_mtr.moveRelative(-280, 200);
	left_mtr.moveRelative(525, 200);
	right_mtr.moveRelative(525, 200);
	left_mtr.moveRelative(-280, 200);
	right_mtr.moveRelative(280, 200);
	left_mtr.moveRelative(100, 100);
	right_mtr.moveRelative(100, 100);
	intake.moveRelative(-500, 200);
	left_mtr.moveRelative(-100, 100);
	right_mtr.moveRelative(-100, 100);
	left_mtr.moveRelative(550, 200);
	right_mtr.moveRelative(-550, 200);
	left_mtr.moveRelative(-300, 300);
	right_mtr.moveRelative(-300, 300);
}

void autonomous()
{
	// intakein(800)
	// drive(700)
	// rotate(280)
	// drive(525)
	// rotate(-280)
	// drive(100, 50)
	// intakespit(500)
	// drive(-100, 50)
	// rotate(550)
	// drive(-300, 300)
	switch (selector::auton)
	{
	case -2:
		// Blue Back
		break;
	case -1:
		// Blue Front
		frontAutonomous();
		break;
	case 0:
		// Skills
		break;
	case 1:
		// Red Front
		frontAutonomous();
		break;
	case 2:
		// Red Back
		break;
	}
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
void opcontrol()
{
	catapult.setBrakeMode(AbstractMotor::brakeMode::hold);

	while (true)
	{
		// Drive
		drivetrain->getModel()->arcade(master.getAnalog(ControllerAnalog::leftY),
									   master.getAnalog(ControllerAnalog::rightX), 0.08);

		// Intake
		if (master.operator[](intakeBtn).isPressed())
		{
			intake.moveVelocity(200);
		}
		else if (master.operator[](reverseIntakeBtn).isPressed())
		{
			intake.moveVelocity(-200);
		}
		else
		{
			intake.moveVoltage(0);
		}

		// Catapult
		if (master.operator[](catapultBtn).isPressed())
		{
			catapult.moveVelocity(200);
		}
		else if (master.operator[](reverseCatapultBtn).isPressed())
		{
			catapult.moveVelocity(-200);
		}
		else
		{
			catapult.moveVoltage(0);
		}

		// Pneumatics
		if (master.operator[](extendArms).changedToPressed())
		{
			left_arm.set_value(true);
			right_arm.set_value(true);
		}
		else if (master.operator[](retractArms).changedToReleased())
		{
			left_arm.set_value(false);
			right_arm.set_value(false);
		}

		// Delay
		pros::delay(20);
	}
}
