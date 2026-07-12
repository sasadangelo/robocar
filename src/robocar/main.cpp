#include <Arduino.h>
#include <elegoo_robot_car.h>

ElegooRobotCar car;

void setup()
{
  // Initialize the motors hardware
  car.init();
}

void loop()
{
  // --- STEP 1: Drive straight ---
  // The car pushes forward at the configured speed (150 out of 255)
  car.forward(150);
  delay(2000);

  // --- STEP 2: Turn ---
  // Pivot turn on the spot for the duration of the turn
  car.backward(150);
  delay(2000);

  // --- STEP 3: Drive straight ---
  // The car pushes forward at the configured speed (150 out of 255)
  car.forward(150);
  delay(2000);

  // --- STEP 4: Drive straight ---
  // The car pushes forward at the configured speed (150 out of 255)
  car.turnLeftSmooth(150, 70);
  delay(2000);

  // --- STEP 5: Drive straight ---
  // The car pushes forward at the configured speed (150 out of 255)
  car.turnRightSmooth(150, 70);
  delay(2000);

  // --- STEP 6: Turn ---
  // Pivot turn on the spot for the duration of the turn
  car.backward(150);
  delay(2000);

  // --- STEP 3: Safety stop ---
  // Stop everything before restarting the cycle
  car.stop();
  delay(2000);
}