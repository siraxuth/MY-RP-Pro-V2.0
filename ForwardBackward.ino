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