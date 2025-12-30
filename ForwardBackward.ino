/*
 * =============================================================================
 *  ForwardBackward.ino - เดินหน้า/ถอยหลัง (อัพเดท)
 * =============================================================================
 *
 *  รูปแบบ: Forward(speed, kp, delayMs)
 *          Backward(speed, kp, delayMs)
 *
 *  ตัวอย่าง:
 *    Forward(50, 1.5, 500);   // เดินหน้า speed=50, kp=1.5, 500ms
 *    Backward(40, 1.2, 300);  // ถอยหลัง speed=40, kp=1.2, 300ms
 *
 * =============================================================================
 *  ตารางคำสั่งย่อ - เดินหน้า/ถอยหลัง
 * =============================================================================
 *
 *  | คำสั่งย่อ    | คำสั่งเต็ม                        | คำอธิบาย                     |
 *  |-------------|----------------------------------|------------------------------|
 *  | FD()        | Forward()                        | เดินหน้า                      |
 *  | FDD(t)      | ForwardDelay(time)               | เดินหน้าหน่วงเวลา             |
 *  | FST(s,t)    | ForwardSpeedTime(speed, time)    | เดินหน้าตามเวลา               |
 *  | FSD(t)      | ForwardSpeedDelay(time)          | เดินหน้าเร่งความเร็วหน่วงเวลา |
 *  | BK()        | Backward()                       | ถอยหลัง                       |
 *  | BKD(t)      | BackwardDelay(time)              | ถอยหลังหน่วงเวลา              |
 *  | BST(s,t)    | BackwardSpeedTime(speed, time)   | ถอยหลังตามเวลา                |
 *  | FJS()       | ForwardJCStop()                  | เดินหน้าเช็คแยกหยุด           |
 *  | FJ()        | ForwardJC()                      | เดินหน้าเช็คแยก               |
 *  | MS()        | MotorBrake()                      | หยุดมอเตอร์                   |
 *
 *  ฟังก์ชันเสริม:
 *  - ForwardSpeedTimeSmooth(speed, time, decelStep, decelDelay)
 *  - ForwardSpeedTimeSmoothEasy(speed, time)
 *  - BackwardSpeedTimeSmooth(speed, time, decelStep, decelDelay)
 *  - BackwardSpeedTimeSmoothEasy(speed, time)
 *  - SmoothStop(currentSpeed, decelStep, decelDelay)
 *  - SmoothStopBackward(currentSpeed, decelStep, decelDelay)
 *
 * =============================================================================
 */

//-----------------------------------------------------------------------------
// เดินหน้า (speed, kp, delayMs)
//-----------------------------------------------------------------------------
void Forward(int speed, float kp, int delayMs)
{
  // ตั้งค่า offset จาก speed
  setMotorOffset(speed);
  resetAngles();

  _integral = 0;
  _prevError = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < delayMs)
  {
    float yaw = gyro('z');
    float err = -yaw;

    _integral += err;
    float deriv = err - _prevError;
    _prevError = err;

    float corr = (kp * err) + (GYRO_KI * _integral) + (GYRO_KD * deriv);

    int leftSpeed = constrain(speed - corr - MOTOR_LEFT_OFFSET, -100, 100);
    int rightSpeed = constrain(speed + corr - MOTOR_RIGHT_OFFSET, -100, 100);
    Motor(leftSpeed, rightSpeed);

    delayMicroseconds(50);
  }
  MotorBrake();
}

//-----------------------------------------------------------------------------
// เดินหน้าไม่จำกัดเวลา (speed)
//-----------------------------------------------------------------------------
void Forward(int speed)
{
  setMotorOffset(speed);
  int leftSpeed = speed - MOTOR_LEFT_OFFSET;
  int rightSpeed = speed - MOTOR_RIGHT_OFFSET;
  Motor(leftSpeed, rightSpeed);
}

//-----------------------------------------------------------------------------
// เดินหน้า (ใช้ BaseSpeed)
//-----------------------------------------------------------------------------
void Forward()
{
  Forward(Speed);
}

//-----------------------------------------------------------------------------
// เดินหน้าเร่งความเร็วหน่วงเวลา
//-----------------------------------------------------------------------------
void ForwardSpeedDelay(int Time)
{
  BaseSpeed = ACCSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// เดินหน้าตามความเร็วและเวลา
//-----------------------------------------------------------------------------
void ForwardSpeedTime(int MotorSpeed, int Time)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// เดินหน้าตามความเร็วและเวลา พร้อมหยุดแบบ Smooth
//-----------------------------------------------------------------------------
void ForwardSpeedTimeSmooth(int MotorSpeed, int Time, int decelStep, int decelDelay)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  SmoothStop(MotorSpeed, decelStep, decelDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// เดินหน้าตามความเร็วและเวลา พร้อมหยุดแบบ Smooth (ใช้ค่า default)
//-----------------------------------------------------------------------------
void ForwardSpeedTimeSmoothEasy(int MotorSpeed, int Time)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Forward();
  delay(Time);
  SmoothStop(MotorSpeed, 5, 20); // ลดทีละ 5, หน่วง 20ms
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// เดินหน้าจนเจอเซ็นเซอร์ (speed, kp, sensor)
//-----------------------------------------------------------------------------
void ForwardUntil(int speed, float kp, String sensor)
{
  setMotorOffset(speed);
  resetAngles();

  _integral = 0;
  _prevError = 0;

  while (true)
  {
    float yaw = gyro('z');
    float err = -yaw;

    _integral += err;
    float deriv = err - _prevError;
    _prevError = err;

    float corr = (kp * err) + (GYRO_KI * _integral) + (GYRO_KD * deriv);

    int leftSpeed = constrain(speed - corr - MOTOR_LEFT_OFFSET, -100, 100);
    int rightSpeed = constrain(speed + corr - MOTOR_RIGHT_OFFSET, -100, 100);
    Motor(leftSpeed, rightSpeed);

    // ตรวจสอบเซ็นเซอร์
    bool stop = false;
    if (sensor == "a0" && read_sensorA(0) < md_sensorA(0))
      stop = true;
    else if (sensor == "a7" && read_sensorA(7) < md_sensorA(7))
      stop = true;
    else if (sensor == "a07" && read_sensorA(0) < md_sensorA(0) && read_sensorA(7) < md_sensorA(7))
      stop = true;
    else if (sensor == "b0" && read_sensorB(0) < md_sensorB(0))
      stop = true;
    else if (sensor == "b7" && read_sensorB(7) < md_sensorB(7))
      stop = true;
    else if (sensor == "c0" && analogRead(CENTER_SENSOR_L) < md_sensorC(0))
      stop = true;
    else if (sensor == "c1" && analogRead(CENTER_SENSOR_R) < md_sensorC(1))
      stop = true;

    if (stop)
      break;

    delayMicroseconds(50);
  }
  MotorBrake();
}

//-----------------------------------------------------------------------------
// เดินหน้าเช็คแยกแล้วหยุด
//-----------------------------------------------------------------------------
void ForwardJCStop()
{
  Forward();
  // รอจนกว่าจะเจอแยก (เซ็นเซอร์ซ้ายและขวาเจอเส้นพร้อมกัน)
  while (!(read_sensorA(0) < md_sensorA(0) && read_sensorA(7) < md_sensorA(7)))
  {
    delayMicroseconds(50);
  }
  MotorBrake();
}

//-----------------------------------------------------------------------------
// เดินหน้า delay แบบง่าย
//-----------------------------------------------------------------------------
void ForwardDelay(int delayMs)
{
  Forward(BaseSpeed);
  delay(delayMs);
  MotorBrake();
}

//-----------------------------------------------------------------------------
// เดินหน้าพร้อม Grip
//-----------------------------------------------------------------------------
void FDG(int MotorSpeed, int Time)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  delay(100);
  arm_down();
  Forward();
  delay(Time);
  BaseSpeed = Speed;
  arm_close();
  arm_up();
  InitialSpeed();
  delay(200);
}

//-----------------------------------------------------------------------------
// Smooth Stop - ค่อยๆ ลดความเร็วลงจนหยุด
//-----------------------------------------------------------------------------
void SmoothStop(int currentSpeed, int decelStep, int decelDelay)
{
  // currentSpeed = ความเร็วปัจจุบัน
  // decelStep = ลดความเร็วทีละเท่าไหร่ (เช่น 5, 10)
  // decelDelay = หน่วงเวลาแต่ละขั้น (ms)
  for (int spd = currentSpeed; spd > 0; spd -= decelStep)
  {
    BaseSpeed = spd;
    InitialSpeed();
    Forward();
    delay(decelDelay);
  }
  MotorStop();
}

//=============================================================================
// ฟังก์ชันถอยหลัง (Backward)
//=============================================================================

//-----------------------------------------------------------------------------
// ถอยหลัง (speed, kp, delayMs)
//-----------------------------------------------------------------------------
void Backward(int speed, float kp, int delayMs)
{
  setMotorOffset(speed);
  resetAngles();

  _integral = 0;
  _prevError = 0;
  unsigned long startTime = millis();

  while (millis() - startTime < delayMs)
  {
    float yaw = gyro('z');
    float err = -yaw;

    _integral += err;
    float deriv = err - _prevError;
    _prevError = err;

    float corr = (kp * err) + (GYRO_KI * _integral) + (GYRO_KD * deriv);

    int leftSpeed = constrain(-(speed - corr - MOTOR_LEFT_OFFSET), -100, 100);
    int rightSpeed = constrain(-(speed + corr - MOTOR_RIGHT_OFFSET), -100, 100);
    Motor(leftSpeed, rightSpeed);

    delayMicroseconds(50);
  }
  MotorBrake();
}

//-----------------------------------------------------------------------------
// ถอยหลังไม่จำกัดเวลา (speed)
//-----------------------------------------------------------------------------
void Backward(int speed)
{
  setMotorOffset(speed);
  int leftSpeed = -(speed - MOTOR_LEFT_OFFSET);
  int rightSpeed = -(speed - MOTOR_RIGHT_OFFSET);
  Motor(leftSpeed, rightSpeed);
}

//-----------------------------------------------------------------------------
// ถอยหลัง (ใช้ BaseSpeed)
//-----------------------------------------------------------------------------
void Backward()
{
  Backward(Speed);
}

//-----------------------------------------------------------------------------
// ถอยหลังตามความเร็วและเวลา
//-----------------------------------------------------------------------------
void BackwardSpeedTime(int MotorSpeed, int Time)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Backward();
  delay(Time);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// ถอยหลังตามความเร็วและเวลา พร้อมหยุดแบบ Smooth
//-----------------------------------------------------------------------------
void BackwardSpeedTimeSmooth(int MotorSpeed, int Time, int decelStep, int decelDelay)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Backward();
  delay(Time);
  SmoothStopBackward(MotorSpeed, decelStep, decelDelay);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// ถอยหลังตามความเร็วและเวลา พร้อมหยุดแบบ Smooth (ใช้ค่า default)
//-----------------------------------------------------------------------------
void BackwardSpeedTimeSmoothEasy(int MotorSpeed, int Time)
{
  BaseSpeed = MotorSpeed;
  InitialSpeed();
  Backward();
  delay(Time);
  SmoothStopBackward(MotorSpeed, 5, 20);
  BaseSpeed = Speed;
  InitialSpeed();
}

//-----------------------------------------------------------------------------
// ถอยหลังจนเจอเซ็นเซอร์ (speed, kp, sensor)
//-----------------------------------------------------------------------------
void BackwardUntil(int speed, float kp, String sensor)
{
  setMotorOffset(speed);
  resetAngles();

  _integral = 0;
  _prevError = 0;

  while (true)
  {
    float yaw = gyro('z');
    float err = -yaw;

    _integral += err;
    float deriv = err - _prevError;
    _prevError = err;

    float corr = (kp * err) + (GYRO_KI * _integral) + (GYRO_KD * deriv);

    int leftSpeed = constrain(-(speed - corr - MOTOR_LEFT_OFFSET), -100, 100);
    int rightSpeed = constrain(-(speed + corr - MOTOR_RIGHT_OFFSET), -100, 100);
    Motor(leftSpeed, rightSpeed);

    // ตรวจสอบเซ็นเซอร์
    bool stop = false;
    if (sensor == "b0" && read_sensorB(0) < md_sensorB(0))
      stop = true;
    else if (sensor == "b7" && read_sensorB(7) < md_sensorB(7))
      stop = true;
    else if (sensor == "b07" && read_sensorB(0) < md_sensorB(0) && read_sensorB(7) < md_sensorB(7))
      stop = true;
    else if (sensor == "a0" && read_sensorA(0) < md_sensorA(0))
      stop = true;
    else if (sensor == "a7" && read_sensorA(7) < md_sensorA(7))
      stop = true;
    else if (sensor == "c0" && analogRead(CENTER_SENSOR_L) < md_sensorC(0))
      stop = true;
    else if (sensor == "c1" && analogRead(CENTER_SENSOR_R) < md_sensorC(1))
      stop = true;

    if (stop)
      break;

    delayMicroseconds(50);
  }
  MotorBrake();
}

//-----------------------------------------------------------------------------
// ถอยหลัง delay แบบง่าย
//-----------------------------------------------------------------------------
void BackwardDelay(int delayMs)
{
  Backward(BaseSpeed);
  delay(delayMs);
  MotorBrake();
}

//-----------------------------------------------------------------------------
// Smooth Stop สำหรับถอยหลัง
//-----------------------------------------------------------------------------
void SmoothStopBackward(int currentSpeed, int decelStep, int decelDelay)
{
  for (int spd = currentSpeed; spd > 0; spd -= decelStep)
  {
    BaseSpeed = spd;
    InitialSpeed();
    Backward();
    delay(decelDelay);
  }
  MotorStop();
}

//-----------------------------------------------------------------------------
// เปลี่ยนความเร็ว
//-----------------------------------------------------------------------------
void ChangeSpeed(int NewSpeed, int NewACCSpeed)
{
  Speed = NewSpeed;
  ACCSpeed = NewACCSpeed;
  BaseSpeed = NewSpeed;
  TurnSpeed = NewSpeed;
}

//-----------------------------------------------------------------------------
// เริ่มต้นหุ่นยนต์
//-----------------------------------------------------------------------------
void RobotStart()
{
  ForwardSpeedTime(60, 200);
}

// =============================================================================
//  ฟังก์ชันเดินหน้า/ถอยหลังแบบ CM (เซนติเมตร)
// =============================================================================
/*
 * วิธีคำนวณที่แม่นยำที่สุด:
 *
 * 1. สูตรพื้นฐาน:
 *    เวลา (ms) = ระยะทาง (mm) / ความเร็ว (mm/s)
 *              = ระยะทาง (cm) * 10 / (speed * SPEED_TO_MMPS) * 1000
 *              = ระยะทาง (cm) * 10000 / (speed * SPEED_TO_MMPS)
 *
 * 2. การ Calibrate ค่า SPEED_TO_MMPS:
 *    - ให้หุ่นเดิน speed=50 เป็นเวลา 1000ms
 *    - วัดระยะทางที่เดินได้ (mm)
 *    - SPEED_TO_MMPS = ระยะทาง / speed
 *
 * 3. การ Fine-tune ด้วย CM_CORRECTION_FACTOR:
 *    - ถ้าเดินได้น้อยกว่าที่กำหนด: เพิ่มค่า > 1.0
 *    - ถ้าเดินได้มากกว่าที่กำหนด: ลดค่า < 1.0
 *
 * 4. ข้อควรระวัง:
 *    - ต้องคำนึงถึงเวลาเบรค (BRAKE_TIME)
 *    - ความเร็วต่ำจะแม่นยำกว่าความเร็วสูง
 *    - พื้นผิวและแบตเตอรี่มีผลต่อความแม่นยำ
 */

//-----------------------------------------------------------------------------
// คำนวณเวลาจากระยะทาง (CM)
//-----------------------------------------------------------------------------
unsigned long calculateTimeFromCM(float cm, int speed)
{
  // สูตร: เวลา (ms) = ระยะทาง (mm) / ความเร็ว (mm/ms)
  // โดย ความเร็ว (mm/ms) = speed * SPEED_TO_MMPS / 1000

  float distance_mm = cm * 10.0;                              // แปลง cm เป็น mm
  float velocity_mmps = (float)speed * SPEED_TO_MMPS;         // mm/s
  float time_ms = (distance_mm / velocity_mmps) * 1000.0;     // ms

  // ใช้ correction factor
  time_ms = time_ms * CM_CORRECTION_FACTOR;

  // หักเวลาเบรค (ประมาณ 30% ของระยะเบรค)
  // เพราะระหว่างเบรคหุ่นยังเคลื่อนที่อยู่
  float brake_distance_compensation = BRAKE_TIME * 0.3;
  if (time_ms > brake_distance_compensation)
  {
    time_ms -= brake_distance_compensation;
  }

  return (unsigned long)time_ms;
}

//-----------------------------------------------------------------------------
// เดินหน้า (speed, cm) - ใช้ Gyro รักษาทิศ
//-----------------------------------------------------------------------------
void ForwardCM(int speed, float cm)
{
  ForwardCM(speed, cm, GYRO_KP);
}

//-----------------------------------------------------------------------------
// เดินหน้า (speed, cm, kp) - กำหนด Kp เอง
//-----------------------------------------------------------------------------
void ForwardCM(int speed, float cm, float kp)
{
  unsigned long delayMs = calculateTimeFromCM(cm, speed);
  Forward(speed, kp, delayMs);
}

//-----------------------------------------------------------------------------
// ถอยหลัง (speed, cm) - ใช้ Gyro รักษาทิศ
//-----------------------------------------------------------------------------
void BackwardCM(int speed, float cm)
{
  BackwardCM(speed, cm, GYRO_KP);
}

//-----------------------------------------------------------------------------
// ถอยหลัง (speed, cm, kp) - กำหนด Kp เอง
//-----------------------------------------------------------------------------
void BackwardCM(int speed, float cm, float kp)
{
  unsigned long delayMs = calculateTimeFromCM(cm, speed);
  Backward(speed, kp, delayMs);
}

//-----------------------------------------------------------------------------
// เดินหน้าแบบ Smooth Stop (speed, cm)
//-----------------------------------------------------------------------------
void ForwardCMSmooth(int speed, float cm)
{
  unsigned long delayMs = calculateTimeFromCM(cm, speed);
  // หักเวลาสำหรับ smooth stop
  unsigned long smoothTime = (speed / 5) * 20; // เวลาที่ใช้ในการ smooth stop
  if (delayMs > smoothTime)
  {
    delayMs -= smoothTime;
  }
  ForwardSpeedTimeSmooth(speed, delayMs, 5, 20);
}

//-----------------------------------------------------------------------------
// ถอยหลังแบบ Smooth Stop (speed, cm)
//-----------------------------------------------------------------------------
void BackwardCMSmooth(int speed, float cm)
{
  unsigned long delayMs = calculateTimeFromCM(cm, speed);
  unsigned long smoothTime = (speed / 5) * 20;
  if (delayMs > smoothTime)
  {
    delayMs -= smoothTime;
  }
  BackwardSpeedTimeSmooth(speed, delayMs, 5, 20);
}

// =============================================================================
//  ฟังก์ชัน Calibration
// =============================================================================

//-----------------------------------------------------------------------------
// ทดสอบ Calibration - เดินหน้า 1 วินาที
//-----------------------------------------------------------------------------
void calibrateSpeedTest(int speed)
{
  Serial.println("=== Speed Calibration Test ===");
  Serial.print("Speed: ");
  Serial.println(speed);
  Serial.println("Running for 1000ms...");
  Serial.println("Measure the distance traveled!");

  delay(1000);
  Forward(speed, GYRO_KP, 1000);

  Serial.println("Done! Measure the distance in mm.");
  Serial.println("Then calculate: SPEED_TO_MMPS = distance / speed");
  Serial.print("Example: If distance = 150mm, SPEED_TO_MMPS = 150 / ");
  Serial.print(speed);
  Serial.print(" = ");
  Serial.println(150.0 / speed);
}

//-----------------------------------------------------------------------------
// ทดสอบความแม่นยำ CM
//-----------------------------------------------------------------------------
void testForwardCM(int speed, float cm)
{
  Serial.println("=== ForwardCM Test ===");
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(", Target: ");
  Serial.print(cm);
  Serial.println(" cm");

  unsigned long calcTime = calculateTimeFromCM(cm, speed);
  Serial.print("Calculated time: ");
  Serial.print(calcTime);
  Serial.println(" ms");

  delay(1000);
  ForwardCM(speed, cm);

  Serial.println("Done! Measure actual distance.");
  Serial.print("If different from ");
  Serial.print(cm);
  Serial.println(" cm, adjust CM_CORRECTION_FACTOR");
}

//-----------------------------------------------------------------------------
// ตั้งค่า Calibration
//-----------------------------------------------------------------------------
void setSpeedCalibration(float speedToMmps)
{
  SPEED_TO_MMPS = speedToMmps;
  Serial.print("SPEED_TO_MMPS set to: ");
  Serial.println(SPEED_TO_MMPS);
}

void setCMCorrection(float factor)
{
  CM_CORRECTION_FACTOR = factor;
  Serial.print("CM_CORRECTION_FACTOR set to: ");
  Serial.println(CM_CORRECTION_FACTOR);
}

void setWheelDiameter(float diameter_mm)
{
  WHEEL_DIAMETER_MM = diameter_mm;
  WHEEL_CIRCUMFERENCE_MM = WHEEL_DIAMETER_MM * 3.14159265359;
  Serial.print("Wheel diameter: ");
  Serial.print(WHEEL_DIAMETER_MM);
  Serial.print(" mm, Circumference: ");
  Serial.print(WHEEL_CIRCUMFERENCE_MM);
  Serial.println(" mm");
}

void setWheelBase(float base_mm)
{
  WHEEL_BASE_MM = base_mm;
  Serial.print("Wheel base set to: ");
  Serial.print(WHEEL_BASE_MM);
  Serial.println(" mm");
}