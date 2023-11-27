#include "main.h"

// Controller
Controller master;

// Motors and Motor Groups
Motor catapult_first(10, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor catapult_second(17, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor intake(1, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
MotorGroup catapult({catapult_first, catapult_second});

// Drivetrain Motors
Motor left_mtr_first(8, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor right_mtr_first(18, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor left_mtr_second(9, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor right_mtr_second(19, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

// Drivetrain
std::shared_ptr<ChassisController> drivetrain =
    ChassisControllerBuilder()
        .withMotors({left_mtr_first, left_mtr_second}, {right_mtr_first,
                                                        right_mtr_second})
        // Fix values
        .withDimensions(AbstractMotor::gearset::green, {{4_in, 16_in}, imev5GreenTPR})
        // .withGains({0, 0, 0}, {0, 0, 0}, {0, 0, 0})
        .build();

std::shared_ptr<AsyncMotionProfileController> trapezoidProfile =
    AsyncMotionProfileControllerBuilder()
        .withLimits({
            1.0, // Maximum linear velocity of the Chassis in m/s
            2.0, // Maximum linear acceleration of the Chassis in m/s/s
            10.0 // Maximum linear jerk of the Chassis in m/s/s/s
        })
        .withOutput(drivetrain)
        .buildMotionProfileController();