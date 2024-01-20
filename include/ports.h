#include "main.h"

// Controller
Controller master;

// Motors and Motor Groups
Motor catapult_first(10, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor catapult_second(11, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor intake(13, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
MotorGroup catapult({catapult_first, catapult_second});

// Drivetrain Motors
Motor left_mtr_first(8, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor right_mtr_first(18, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor left_mtr_second(9, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor right_mtr_second(19, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
MotorGroup left_mtr({left_mtr_first, left_mtr_second});
MotorGroup right_mtr({right_mtr_first, right_mtr_second});

// Pneumatics
pros::ADIDigitalOut left_arm('A');
pros::ADIDigitalOut right_arm('H');

// Drivetrain
auto drivetrain =
    ChassisControllerBuilder()
        .withMotors(left_mtr, right_mtr)
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
        // .withGains({0, 0, 0}, {0, 0, 0}, {0, 0, 0})
        .withOdometry()
        .buildOdometry();

std::shared_ptr<AsyncMotionProfileController> trapezoidProfile =
    AsyncMotionProfileControllerBuilder()
        .withLimits({
            0.5, // Maximum linear velocity of the Chassis in m/s
            2.0, // Maximum linear acceleration of the Chassis in m/s/s
            10.0 // Maximum linear jerk of the Chassis in m/s/s/s
        })
        .withOutput(drivetrain)
        .buildMotionProfileController();