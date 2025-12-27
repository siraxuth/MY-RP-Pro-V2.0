/*
 * =============================================================================
 *  TracDegree.ino - หมุนตัวและเดินตรงด้วย Gyro (อัพเดท)
 * =============================================================================
 *
 *  รูปแบบ: SpinDegree(speed, degree, mode)
 *
 *  Mode:
 *    0 = Relative (รีเซ็ตหลังเลี้ยว)
 *    1 = Absolute (0=หน้า, 90=ขวา, 180=หลัง, 270=ซ้าย)
 *
 *  ตัวอย่าง:
 *    SpinDegree(30, 90, 0);    // หมุนขวา 90°
 *    SpinDegree(30, -90, 0);   // หมุนซ้าย 90°
 *    TurnToHeading(30, 90);    // หมุนไปทิศขวา (Absolute)
 *
 * =============================================================================
 *  ตารางคำสั่งย่อ - TracDegree (เดินตรงด้วย Gyro)
 * =============================================================================
 *
 *  | คำสั่งย่อ      | คำสั่งเต็ม                               | คำอธิบาย                     |
 *  |---------------|------------------------------------------|------------------------------|
 *  | TDST(s,d,t,m) | TracDegreeSpeedTime(speed,deg,time,mode) | เดินตรงด้วย Gyro             |
 *  | TDSB(s,d,t,m) | TracDegreeSpeedTimeBack(speed,deg,t,m)   | ถอยหลังด้วย Gyro            |
 *  | TJD(s,d,t,m)  | TracJCDegree(speed,degree,tune,mode)     | เดินจนเจอแยกด้วย Gyro        |
 *  | TJDB(s,d,t,m) | TracJCDegreeBack(speed,degree,tune,mode) | ถอยจนเจอแยกด้วย Gyro         |
 *
 *  ตารางคำสั่งย่อ - หมุนตัว (Spin/Turn with Gyro)
 *
 *  | คำสั่งย่อ    | คำสั่งเต็ม                    | คำอธิบาย                      |
 *  |-------------|-------------------------------|-------------------------------|
 *  | SD(s,d,m)   | SpinDegree(speed,degree,mode) | หมุนตัวตามองศา                |
 *  | SL(s,d)     | SpinLeft(speed,degree)        | หมุนซ้าย                      |
 *  | SR(s,d)     | SpinRight(speed,degree)       | หมุนขวา                       |
 *  | SL(s,d,m)   | SpinLeft(speed,degree,mode)   | หมุนซ้าย (กำหนด mode)         |
 *  | SR(s,d,m)   | SpinRight(speed,degree,mode)  | หมุนขวา (กำหนด mode)          |
 *  | TTH(s,h)    | TurnToHeading(speed,heading)  | หมุนไปทิศที่กำหนด (Absolute)  |
 *  | TTF(s)      | TurnToFront(speed)            | หมุนไปทิศหน้า (0°)            |
 *  | TTB(s)      | TurnToBack(speed)             | หมุนไปทิศหลัง (180°)          |
 *  | TTL(s)      | TurnToLeft(speed)             | หมุนไปทิศซ้าย (-90°)          |
 *  | TTR(s)      | TurnToRight(speed)            | หมุนไปทิศขวา (90°)            |
 *  | SH(d)       | SetHeading(degree)            | ตั้งทิศอ้างอิง                |
 *
 *  หมายเหตุ:
 *  - Mode: 0 = Relative (รีเซ็ตหลังเลี้ยว), 1 = Absolute (0°=หน้า, 90°=ขวา)
 *  - degree: องศาที่ต้องการหมุน (บวก=ขวา, ลบ=ซ้าย)
 *  - heading: ทิศที่ต้องการหันไป (Absolute mode)
 * =============================================================================
 */

//-----------------------------------------------------------------------------
// หมุนตัว (speed, degree, mode)
//-----------------------------------------------------------------------------
void SpinDegree(int speed, int degree, int mode)
{
  float targetAngle;

  if (mode == 0)
  {
    // Mode 0: Relative
    resetAngles();
    targetAngle = degree;
  }
  else
  {
    // Mode 1: Absolute
    targetAngle = degree;
    if (targetAngle > 180)
      targetAngle -= 360;
    if (targetAngle < -180)
      targetAngle += 360;
  }

  _integral = 0;
  _prevError = 0;
  int status = 0;

  MotorStop();

  while (status == 0)
  {
    float currentYaw = gyro('z');
    float error = targetAngle - currentYaw;

    // Wrap error
    if (error > 180)
      error -= 360;
    else if (error < -180)
      error += 360;

    _integral += error;
    float deriv = error - _prevError;
    _prevError = error;

    float output = (GYRO_KP * error) + (GYRO_KI * _integral) + (GYRO_KD * deriv);
    output = constrain(output, -speed, speed);

    Motor(-output, output);

    if (abs(error) <= 1.0)
    {
      status = 1;
    }

    delay(Kt);
  }

  MotorStop();

  if (mode == 0)
  {
    resetAngles();
  }
}

//-----------------------------------------------------------------------------
// หมุนซ้าย (speed, degree)
//-----------------------------------------------------------------------------
void SpinLeft(int speed, int degree)
{
  SpinDegree(speed, -abs(degree), 0);
}

void SpinLeft(int speed, int degree, int mode)
{
  if (mode == 0)
  {
    SpinDegree(speed, -abs(degree), mode);
  }
  else
  {
    float target = _absoluteAngle - abs(degree);
    if (target < -180)
      target += 360;
    SpinDegree(speed, target, mode);
    _absoluteAngle = target;
  }
}

//-----------------------------------------------------------------------------
// หมุนขวา (speed, degree)
//-----------------------------------------------------------------------------
void SpinRight(int speed, int degree)
{
  SpinDegree(speed, abs(degree), 0);
}

void SpinRight(int speed, int degree, int mode)
{
  if (mode == 0)
  {
    SpinDegree(speed, abs(degree), mode);
  }
  else
  {
    float target = _absoluteAngle + abs(degree);
    if (target > 180)
      target -= 360;
    SpinDegree(speed, target, mode);
    _absoluteAngle = target;
  }
}

//-----------------------------------------------------------------------------
// ตั้งทิศอ้างอิง (Absolute mode)
//-----------------------------------------------------------------------------
void SetHeading(int degree)
{
  _absoluteAngle = degree;
  if (_absoluteAngle > 180)
    _absoluteAngle -= 360;
  else if (_absoluteAngle < -180)
    _absoluteAngle += 360;
  resetAngles();
}

//-----------------------------------------------------------------------------
// หมุนไปทิศที่กำหนด (Absolute mode)
//-----------------------------------------------------------------------------
void TurnToHeading(int speed, int targetHeading)
{
  float target = targetHeading;
  if (target > 180)
    target -= 360;
  SpinDegree(speed, target, 1);
  _absoluteAngle = target;
}

void TurnToFront(int speed) { TurnToHeading(speed, 0); }
void TurnToBack(int speed) { TurnToHeading(speed, 180); }
void TurnToLeft(int speed) { TurnToHeading(speed, -90); }
void TurnToRight(int speed) { TurnToHeading(speed, 90); }

// =============================================================================
//  เดินตรงด้วย Gyro
// =============================================================================

//-----------------------------------------------------------------------------
// คำนวณ Error จาก Gyro
//-----------------------------------------------------------------------------
bool CalErrorGyro(int Degree)
{
  float yaw = gyro('z');
  Error = yaw - Degree;
  if (Error > 180)
    Error -= 360;
  else if (Error < -180)
    Error += 360;
  Error = Error / 5.0;
  return true;
}

bool CalErrorGyroBack(int Degree)
{
  float yaw = gyro('z');
  Error = Degree - yaw;
  if (Error > 180)
    Error -= 360;
  else if (Error < -180)
    Error += 360;
  Error = Error / 5.0;
  return true;
}

//-----------------------------------------------------------------------------
// เดินตรงด้วย Gyro (speed, degree, delayMs, mode)
//-----------------------------------------------------------------------------
void TracDegreeSpeedTime(int speed, int degree, int delayMs, int mode)
{
  int TempSpeed = BaseSpeed;

  if (mode == 0)
    resetAngles();

  setMotorOffset(speed);
  StartTimer();
  BaseSpeed = speed;
  CalErrorGyro(degree);

  while (ReadTimer() < delayMs)
  {
    TracPID();
    StartTimer3();
    while (ReadTimer3() < Kt)
    {
      CalErrorGyro(degree);
    }
  }

  MotorStop();
  BaseSpeed = TempSpeed;
}

//-----------------------------------------------------------------------------
// ถอยหลังด้วย Gyro (speed, degree, delayMs, mode)
//-----------------------------------------------------------------------------
void TracDegreeSpeedTimeBack(int speed, int degree, int delayMs, int mode)
{
  int TempSpeed = BaseSpeed;

  if (mode == 0)
    resetAngles();

  setMotorOffset(speed);
  StartTimer();
  BaseSpeed = speed;
  CalErrorGyroBack(degree);

  while (ReadTimer() < delayMs)
  {
    TracPIDBack();
    StartTimer3();
    while (ReadTimer3() < Kt)
    {
      CalErrorGyroBack(degree);
    }
  }

  MotorStop();
  BaseSpeed = TempSpeed;
}

//-----------------------------------------------------------------------------
// เดินด้วย Gyro จนเจอแยก (speed, degree, tuneDelayMs, mode)
//-----------------------------------------------------------------------------
void TracJCDegree(int speed, int degree, int tuneDelayMs, int mode)
{
  int TempSpeed = BaseSpeed;

  if (mode == 0)
    resetAngles();

  setMotorOffset(speed);
  BaseSpeed = speed;
  CalErrorGyro(degree);
  ConvertADC();

  while (C == 1)
  {
    TracPID();
    StartTimer3();
    while (ReadTimer3() < Kt)
    {
      CalErrorGyro(degree);
    }
    ConvertADC();
  }

  MotorStop();
  TracDegreeSpeedTimeBack(speed, degree, tuneDelayMs, mode);
  BaseSpeed = TempSpeed;
}

//-----------------------------------------------------------------------------
// ถอยหลังด้วย Gyro จนเจอแยก (speed, degree, tuneDelayMs, mode)
//-----------------------------------------------------------------------------
void TracJCDegreeBack(int speed, int degree, int tuneDelayMs, int mode)
{
  int TempSpeed = BaseSpeed;

  if (mode == 0)
    resetAngles();

  setMotorOffset(speed);
  BaseSpeed = speed;
  CalErrorGyroBack(degree);
  ConvertADCBack();

  while (BL1 == 1 && BR1 == 1)
  {
    TracPIDBack();
    StartTimer3();
    while (ReadTimer3() < Kt)
    {
      CalErrorGyroBack(degree);
    }
    ConvertADCBack();
  }

  MotorStop();
  TracDegreeSpeedTime(speed, degree, tuneDelayMs, mode);
  BaseSpeed = TempSpeed;
}

// =============================================================================
//  ฟังก์ชันหมุนพิเศษ
// =============================================================================

void rotate_left(int speed, int degree, int brakeDelay)
{
  SpinLeft(speed, degree);
  delay(brakeDelay);
}

void rotate_right(int speed, int degree, int brakeDelay)
{
  SpinRight(speed, degree);
  delay(brakeDelay);
}

void place_left_in(int speed, int degree, int brakeDelay)
{
  SpinLeft(speed, degree);
  delay(brakeDelay);
}

void place_left_out(int speed, int degree, int brakeDelay)
{
  SpinRight(speed, degree);
  delay(brakeDelay);
}

void place_right_in(int speed, int degree, int brakeDelay)
{
  SpinRight(speed, degree);
  delay(brakeDelay);
}

void place_right_out(int speed, int degree, int brakeDelay)
{
  SpinLeft(speed, degree);
  delay(brakeDelay);
}