/*
 * =============================================================================
 *  Turn.ino - ฟังก์ชันเลี้ยวซ้าย/ขวา (อัพเดท)
 * =============================================================================
 *
 *  ฟังก์ชันหลัก:
 *    Left(speed, time)      - เลี้ยวซ้ายตามเวลา (ms)
 *    Right(speed, time)     - เลี้ยวขวาตามเวลา (ms)
 *    TurnLeft()             - เลี้ยวซ้ายจนเจอเส้น
 *    TurnRight()            - เลี้ยวขวาจนเจอเส้น
 *    TurnLeft(speed)        - เลี้ยวซ้ายจนเจอเส้น (กำหนดความเร็ว)
 *    TurnRight(speed)       - เลี้ยวขวาจนเจอเส้น (กำหนดความเร็ว)
 *    UTurnLeft()            - กลับตัวซ้าย 180°
 *    UTurnRight()           - กลับตัวขวา 180°
 *
 *  ตัวอย่างการใช้งาน:
 *    Left(50, 200);         // เลี้ยวซ้าย speed=50, 200ms
 *    Right(50, 200);        // เลี้ยวขวา speed=50, 200ms
 *    TurnLeft();            // เลี้ยวซ้ายจนเจอเส้น
 *    TurnRight();           // เลี้ยวขวาจนเจอเส้น
 *    TurnLeft(60);          // เลี้ยวซ้าย speed=60 จนเจอเส้น
 *    UTurnLeft();           // กลับตัวซ้าย
 *
 * =============================================================================
 *  ตารางคำสั่งย่อ - เลี้ยว (Turn)
 * =============================================================================
 *
 *  | คำสั่งย่อ    | คำสั่งเต็ม                          | คำอธิบาย                       |
 *  |-------------|-------------------------------------|--------------------------------|
 *  | TL()        | TurnLeft()                          | เลี้ยวซ้าย (ใช้ TurnSpeed)      |
 *  | TL(s)       | TurnLeft(speed)                     | เลี้ยวซ้าย กำหนดความเร็ว        |
 *  | TR()        | TurnRight()                         | เลี้ยวขวา (ใช้ TurnSpeed)       |
 *  | TR(s)       | TurnRight(speed)                    | เลี้ยวขวา กำหนดความเร็ว         |
 *  | UTL()       | UTurnLeft()                         | กลับตัวซ้าย (ใช้ TurnSpeed)     |
 *  | UTL(s)      | UTurnLeft(speed)                    | กลับตัวซ้าย กำหนดความเร็ว       |
 *  | UTR()       | UTurnRight()                        | กลับตัวขวา (ใช้ TurnSpeed)      |
 *  | UTR(s)      | UTurnRight(speed)                   | กลับตัวขวา กำหนดความเร็ว        |
 *  | LT(s,t)     | Left(speed, time)                   | หมุนซ้ายตามเวลา                 |
 *  | RT(s,t)     | Right(speed, time)                  | หมุนขวาตามเวลา                  |
 *  | TLD(s,t)    | TurnLeftDelay(speed, time)          | เลี้ยวซ้ายหน่วงเวลา             |
 *  | TRD(s,t)    | TurnRightDelay(speed, time)         | เลี้ยวขวาหน่วงเวลา              |
 *  | CL(s,t)     | CurveLeft(speed, time)              | โค้งซ้ายอ้อมสิ่งกีดขวาง         |
 *  | CR(s,t)     | CurveRight(speed, time)             | โค้งขวาอ้อมสิ่งกีดขวาง          |
 *  | TLB(s)      | TurnLeftBack(speed)                 | เลี้ยวซ้ายเช็คเซ็นเซอร์หลัง     |
 *  | TRB(s)      | TurnRightBack(speed)                | เลี้ยวขวาเช็คเซ็นเซอร์หลัง      |
 *  | TLS(s,n)    | TurnLeftSensor(speed, sensor)       | เลี้ยวซ้ายจนเจอเซ็นเซอร์ที่กำหนด |
 *  | TRS(s,n)    | TurnRightSensor(speed, sensor)      | เลี้ยวขวาจนเจอเซ็นเซอร์ที่กำหนด |
 *
 * =============================================================================
 */

// =============================================================================
//  ฟังก์ชันพื้นฐาน - เลี้ยวซ้าย (Spin Left)
// =============================================================================

void sl(int speed)
{
  Motor(-speed, speed);
}

void SL(int speed)
{
  // 4WD mode - ถ้าต้องการควบคุมแยก
  Motor(-speed, speed);
}

// =============================================================================
//  ฟังก์ชันพื้นฐาน - เลี้ยวขวา (Spin Right)
// =============================================================================

void sr(int speed)
{
  Motor(speed, -speed);
}

void SR(int speed)
{
  // 4WD mode
  Motor(speed, -speed);
}

// =============================================================================
//  ฟังก์ชันพื้นฐาน - เลี้ยวซ้าย (Turn Left - ล้อข้างหนึ่งหมุน)
// =============================================================================

void tl(int speed)
{
  Motor(0, speed);
}

// =============================================================================
//  ฟังก์ชันพื้นฐาน - เลี้ยวขวา (Turn Right - ล้อข้างหนึ่งหมุน)
// =============================================================================

void tr(int speed)
{
  Motor(speed, 0);
}

// =============================================================================
//  Left - เลี้ยวซ้ายตามเวลา
// =============================================================================

void Left(int speed, int time)
{
  Motor(0, 0);
  delay(5);
  sl(speed);
  delay(time);
  Motor(0, 0);
}

// =============================================================================
//  Right - เลี้ยวขวาตามเวลา
// =============================================================================

void Right(int speed, int time)
{
  Motor(0, 0);
  delay(5);
  sr(speed);
  delay(time);
  Motor(0, 0);
}

// =============================================================================
//  TurnLeftDelay - เลี้ยวซ้ายตามเวลา (ไม่หยุด)
// =============================================================================

void TurnLeftDelay(int speed, int time)
{
  tl(speed);
  delay(time);
}

// =============================================================================
//  TurnRightDelay - เลี้ยวขวาตามเวลา (ไม่หยุด)
// =============================================================================

void TurnRightDelay(int speed, int time)
{
  tr(speed);
  delay(time);
}

// =============================================================================
//  TurnLeft - เลี้ยวซ้ายจนเจอเส้น (ใช้ TurnSpeed)
// =============================================================================

void TurnLeft()
{
  TurnLeft(TurnSpeed);
}

// =============================================================================
//  TurnLeft - เลี้ยวซ้ายจนเจอเส้น (กำหนดความเร็ว)
// =============================================================================

void TurnLeft(int speed)
{
  Motor(0, 0);
  delay(5);

  // เริ่มหมุน
  if (WheelDrive == 0)
  {
    sl(speed);
  }
  else
  {
    SL(speed);
  }

  // Delay เริ่มต้น (ให้พ้นเส้นเดิมก่อน)
  delay(turn_delay_90 / speed);

  // ถ้าเร็วเกิน 90 ให้ลดความเร็ว
  if (speed > 90)
  {
    if (WheelDrive == 0)
    {
      sl(90);
    }
    else
    {
      SL(90);
    }
  }

  // รอจนเจอเส้น (เช็คตามความเร็ว)
  if (speed <= 40)
  {
    // ความเร็วต่ำ - เช็คเซ็นเซอร์กลาง
    while (read_sensorA(3) > md_sensorA(3) && read_sensorA(4) > md_sensorA(4))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 50)
  {
    // เช็ค L1 (sensor 2)
    while (read_sensorA(2) > md_sensorA(2))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 60)
  {
    // เช็ค L2 (sensor 1)
    while (read_sensorA(1) > md_sensorA(1))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    // เช็ค L3 (sensor 0)
    while (read_sensorA(0) > md_sensorA(0))
    {
      delayMicroseconds(50);
    }
  }

  // เบรค
  if (BrakeTime > 0 && speed > 70)
  {
    Right(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  TurnRight - เลี้ยวขวาจนเจอเส้น (ใช้ TurnSpeed)
// =============================================================================

void TurnRight()
{
  TurnRight(TurnSpeed);
}

// =============================================================================
//  TurnRight - เลี้ยวขวาจนเจอเส้น (กำหนดความเร็ว)
// =============================================================================

void TurnRight(int speed)
{
  Motor(0, 0);
  delay(5);

  // เริ่มหมุน
  if (WheelDrive == 0)
  {
    sr(speed);
  }
  else
  {
    SR(speed);
  }

  // Delay เริ่มต้น
  delay(turn_delay_90 / speed);

  // ถ้าเร็วเกิน 90 ให้ลดความเร็ว
  if (speed > 90)
  {
    if (WheelDrive == 0)
    {
      sr(90);
    }
    else
    {
      SR(90);
    }
  }

  // รอจนเจอเส้น
  if (speed <= 40)
  {
    while (read_sensorA(3) > md_sensorA(3) && read_sensorA(4) > md_sensorA(4))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 50)
  {
    // เช็ค R1 (sensor 5)
    while (read_sensorA(5) > md_sensorA(5))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 60)
  {
    // เช็ค R2 (sensor 6)
    while (read_sensorA(6) > md_sensorA(6))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    // เช็ค R3 (sensor 7)
    while (read_sensorA(7) > md_sensorA(7))
    {
      delayMicroseconds(50);
    }
  }

  // เบรค
  if (BrakeTime > 0 && speed > 70)
  {
    Left(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  UTurnLeft - กลับตัวซ้าย 180° (ใช้ TurnSpeed)
// =============================================================================

void UTurnLeft()
{
  UTurnLeft(TurnSpeed);
}

// =============================================================================
//  UTurnLeft - กลับตัวซ้าย 180° (กำหนดความเร็ว)
// =============================================================================

void UTurnLeft(int speed)
{
  Motor(0, 0);
  delay(5);

  // เริ่มหมุน
  if (WheelDrive == 0)
  {
    sl(speed);
  }
  else
  {
    SL(speed);
  }

  // Delay สำหรับ 180°
  delay(turn_delay_180 / speed);

  // ถ้าเร็วเกิน 70 ให้ลดความเร็ว
  if (speed > 70)
  {
    if (WheelDrive == 0)
    {
      sl(60);
    }
    else
    {
      SL(60);
    }
  }

  // รอจนเจอเส้น
  if (speed <= 40)
  {
    while (read_sensorA(3) > md_sensorA(3) && read_sensorA(4) > md_sensorA(4))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 50)
  {
    while (read_sensorA(2) > md_sensorA(2))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 60)
  {
    while (read_sensorA(1) > md_sensorA(1))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    while (read_sensorA(0) > md_sensorA(0))
    {
      delayMicroseconds(50);
    }
  }

  // เบรค
  if (BrakeTime > 0 && speed > 70)
  {
    Right(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  UTurnRight - กลับตัวขวา 180° (ใช้ TurnSpeed)
// =============================================================================

void UTurnRight()
{
  UTurnRight(TurnSpeed);
}

// =============================================================================
//  UTurnRight - กลับตัวขวา 180° (กำหนดความเร็ว)
// =============================================================================

void UTurnRight(int speed)
{
  Motor(0, 0);
  delay(5);

  // เริ่มหมุน
  if (WheelDrive == 0)
  {
    sr(speed);
  }
  else
  {
    SR(speed);
  }

  // Delay สำหรับ 180°
  delay(turn_delay_180 / speed);

  // ถ้าเร็วเกิน 70 ให้ลดความเร็ว
  if (speed > 70)
  {
    if (WheelDrive == 0)
    {
      sr(60);
    }
    else
    {
      SR(60);
    }
  }

  // รอจนเจอเส้น
  if (speed <= 40)
  {
    while (read_sensorA(3) > md_sensorA(3) && read_sensorA(4) > md_sensorA(4))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 50)
  {
    while (read_sensorA(5) > md_sensorA(5))
    {
      delayMicroseconds(50);
    }
  }
  else if (speed <= 60)
  {
    while (read_sensorA(6) > md_sensorA(6))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    while (read_sensorA(7) > md_sensorA(7))
    {
      delayMicroseconds(50);
    }
  }

  // เบรค
  if (BrakeTime > 0 && speed > 70)
  {
    Left(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  CurveLeft - โค้งซ้ายอ้อมสิ่งกีดขวาง
// =============================================================================

void CurveLeft(int speed, int time)
{
  Motor(0, 0);
  delay(5);

  // เลี้ยวซ้ายเล็กน้อย
  Left(speed, 130);

  // วิ่งโค้ง (ล้อซ้ายเร็วกว่า)
  if (WheelDrive == 0)
  {
    Motor(speed, speed * 0.58);
  }
  else
  {
    Motor(speed, speed * 0.58);
  }
  delay(900);

  // รอจนเจอเส้น (เซ็นเซอร์ขวา)
  while (read_sensorA(5) > md_sensorA(5))
  {
    delayMicroseconds(50);
  }
  while (read_sensorA(5) < md_sensorA(5))
  {
    delayMicroseconds(50);
  }

  delay(time);
  TurnLeft();
}

// =============================================================================
//  CurveRight - โค้งขวาอ้อมสิ่งกีดขวาง
// =============================================================================

void CurveRight(int speed, int time)
{
  Motor(0, 0);
  delay(5);

  // เลี้ยวขวาเล็กน้อย
  Right(speed, 130);

  // วิ่งโค้ง (ล้อขวาเร็วกว่า)
  if (WheelDrive == 0)
  {
    Motor(speed * 0.58, speed);
  }
  else
  {
    Motor(speed * 0.58, speed);
  }
  delay(900);

  // รอจนเจอเส้น (เซ็นเซอร์ซ้าย)
  while (read_sensorA(2) > md_sensorA(2))
  {
    delayMicroseconds(50);
  }
  while (read_sensorA(2) < md_sensorA(2))
  {
    delayMicroseconds(50);
  }

  delay(time);
  TurnRight();
}

// =============================================================================
//  TurnLeftSensor - เลี้ยวซ้ายจนเจอเซ็นเซอร์ที่กำหนด
// =============================================================================

void TurnLeftSensor(int speed, int sensor)
{
  Motor(0, 0);
  delay(5);

  sl(speed);
  delay(50); // ให้พ้นเส้นเดิม

  // รอจนเจอเส้น
  while (read_sensorA(sensor) > md_sensorA(sensor))
  {
    delayMicroseconds(50);
  }

  Motor(0, 0);
}

// =============================================================================
//  TurnRightSensor - เลี้ยวขวาจนเจอเซ็นเซอร์ที่กำหนด
// =============================================================================

void TurnRightSensor(int speed, int sensor)
{
  Motor(0, 0);
  delay(5);

  sr(speed);
  delay(50);

  while (read_sensorA(sensor) > md_sensorA(sensor))
  {
    delayMicroseconds(50);
  }

  Motor(0, 0);
}

// =============================================================================
//  TurnLeftBack - เลี้ยวซ้ายจนเจอเส้น (ใช้เซ็นเซอร์หลัง)
// =============================================================================

void TurnLeftBack(int speed)
{
  Motor(0, 0);
  delay(5);

  sl(speed);
  delay(turn_delay_90 / speed);

  if (speed > 90)
    sl(90);

  // รอจนเซ็นเซอร์หลังเจอเส้น
  if (speed <= 50)
  {
    while (read_sensorB(3) > md_sensorB(3) && read_sensorB(4) > md_sensorB(4))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    while (read_sensorB(2) > md_sensorB(2))
    {
      delayMicroseconds(50);
    }
  }

  if (BrakeTime > 0 && speed > 70)
  {
    Right(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  TurnRightBack - เลี้ยวขวาจนเจอเส้น (ใช้เซ็นเซอร์หลัง)
// =============================================================================

void TurnRightBack(int speed)
{
  Motor(0, 0);
  delay(5);

  sr(speed);
  delay(turn_delay_90 / speed);

  if (speed > 90)
    sr(90);

  // รอจนเซ็นเซอร์หลังเจอเส้น
  if (speed <= 50)
  {
    while (read_sensorB(3) > md_sensorB(3) && read_sensorB(4) > md_sensorB(4))
    {
      delayMicroseconds(50);
    }
  }
  else
  {
    while (read_sensorB(5) > md_sensorB(5))
    {
      delayMicroseconds(50);
    }
  }

  if (BrakeTime > 0 && speed > 70)
  {
    Left(BrakeSpeed, BrakeTime);
  }
  else
  {
    Motor(0, 0);
  }
}

// =============================================================================
//  ฟังก์ชันตั้งค่า
// =============================================================================

void setTurnSpeed(int speed)
{
  TurnSpeed = speed;
}

void setTurnBrake(int speed, int time)
{
  BrakeSpeed = speed;
  BrakeTime = time;
}

void setTurnDelay90(int delayVal)
{
  turn_delay_90 = delayVal;
}

void setTurnDelay180(int delayVal)
{
  turn_delay_180 = delayVal;
}

void setWheelDrive(int mode)
{
  WheelDrive = mode; // 0 = 2WD, 1 = 4WD
}

// =============================================================================
//  ฟังก์ชัน Turn แบบ CM (โค้งตามระยะทาง)
// =============================================================================
/*
 * เลี้ยวโค้งโดยกำหนดรัศมีวงเลี้ยวและระยะทาง
 *
 * สูตรการคำนวณโค้ง:
 * - ความยาวส่วนโค้ง = (มุม/360) * 2 * π * รัศมี
 * - ความเร็วล้อใน = speed * (รัศมี - WHEEL_BASE/2) / รัศมี
 * - ความเร็วล้อนอก = speed * (รัศมี + WHEEL_BASE/2) / รัศมี
 *
 * ข้อดี:
 * - ควบคุมรัศมีวงเลี้ยวได้แม่นยำ
 * - กำหนดระยะทางโค้งได้
 */

//-----------------------------------------------------------------------------
// คำนวณความเร็วล้อสำหรับโค้ง
//-----------------------------------------------------------------------------
void calculateCurveSpeeds(int baseSpeed, float radiusCM, bool turnLeft, int &speedL, int &speedR)
{
  float radius_mm = radiusCM * 10.0;
  float half_base = WHEEL_BASE_MM / 2.0;

  if (turnLeft)
  {
    // เลี้ยวซ้าย: ล้อซ้ายเป็นล้อใน (เร็วน้อยกว่า)
    speedL = (int)(baseSpeed * (radius_mm - half_base) / radius_mm);
    speedR = (int)(baseSpeed * (radius_mm + half_base) / radius_mm);
  }
  else
  {
    // เลี้ยวขวา: ล้อขวาเป็นล้อใน (เร็วน้อยกว่า)
    speedL = (int)(baseSpeed * (radius_mm + half_base) / radius_mm);
    speedR = (int)(baseSpeed * (radius_mm - half_base) / radius_mm);
  }

  // Constrain speeds
  speedL = constrain(speedL, -100, 100);
  speedR = constrain(speedR, -100, 100);
}

//-----------------------------------------------------------------------------
// คำนวณเวลาสำหรับโค้ง
//-----------------------------------------------------------------------------
unsigned long calculateCurveTime(float degrees, float radiusCM, int speed)
{
  // ความยาวส่วนโค้งที่จุดกึ่งกลางหุ่น
  float radius_mm = radiusCM * 10.0;
  float arc_length_mm = (abs(degrees) / 360.0) * 2.0 * 3.14159265359 * radius_mm;

  // คำนวณเวลา
  float velocity_mmps = (float)speed * SPEED_TO_MMPS;
  float time_ms = (arc_length_mm / velocity_mmps) * 1000.0;

  // ใช้ correction factor
  time_ms = time_ms * CM_CORRECTION_FACTOR;

  return (unsigned long)time_ms;
}

//-----------------------------------------------------------------------------
// โค้งซ้าย (speed, degrees, radiusCM)
//-----------------------------------------------------------------------------
void CurveLeftCM(int speed, float degrees, float radiusCM)
{
  int speedL, speedR;
  calculateCurveSpeeds(speed, radiusCM, true, speedL, speedR);
  unsigned long curveTime = calculateCurveTime(degrees, radiusCM, speed);

  Motor(speedL, speedR);
  delay(curveTime);
  MotorBrake();
}

//-----------------------------------------------------------------------------
// โค้งขวา (speed, degrees, radiusCM)
//-----------------------------------------------------------------------------
void CurveRightCM(int speed, float degrees, float radiusCM)
{
  int speedL, speedR;
  calculateCurveSpeeds(speed, radiusCM, false, speedL, speedR);
  unsigned long curveTime = calculateCurveTime(degrees, radiusCM, speed);

  Motor(speedL, speedR);
  delay(curveTime);
  MotorBrake();
}

//-----------------------------------------------------------------------------
// โค้งซ้ายตามระยะทาง (speed, arcLengthCM, radiusCM)
//-----------------------------------------------------------------------------
void CurveLeftDistanceCM(int speed, float arcLengthCM, float radiusCM)
{
  // คำนวณมุมจากความยาวส่วนโค้ง
  float arc_mm = arcLengthCM * 10.0;
  float radius_mm = radiusCM * 10.0;
  float degrees = (arc_mm / (2.0 * 3.14159265359 * radius_mm)) * 360.0;

  CurveLeftCM(speed, degrees, radiusCM);
}

//-----------------------------------------------------------------------------
// โค้งขวาตามระยะทาง (speed, arcLengthCM, radiusCM)
//-----------------------------------------------------------------------------
void CurveRightDistanceCM(int speed, float arcLengthCM, float radiusCM)
{
  float arc_mm = arcLengthCM * 10.0;
  float radius_mm = radiusCM * 10.0;
  float degrees = (arc_mm / (2.0 * 3.14159265359 * radius_mm)) * 360.0;

  CurveRightCM(speed, degrees, radiusCM);
}

// =============================================================================
//  ฟังก์ชัน Turn แบบ CM (Pivot Turn)
// =============================================================================
/*
 * Pivot Turn คือการเลี้ยวโดยให้ล้อข้างหนึ่งหยุดนิ่ง
 * รัศมีวงเลี้ยว = WHEEL_BASE_MM
 *
 * สูตร:
 *   ระยะทางที่ล้อนอกต้องหมุน = (มุม/360) * 2 * π * WHEEL_BASE_MM
 */

//-----------------------------------------------------------------------------
// Pivot Left CM (ล้อซ้ายหยุด ล้อขวาหมุน)
//-----------------------------------------------------------------------------
void PivotLeftCM(int speed, float degrees)
{
  float distance_mm = (abs(degrees) / 360.0) * 2.0 * 3.14159265359 * WHEEL_BASE_MM;
  float velocity_mmps = (float)speed * SPEED_TO_MMPS;
  unsigned long time_ms = (unsigned long)((distance_mm / velocity_mmps) * 1000.0 * CM_CORRECTION_FACTOR);

  Motor(0, speed);
  delay(time_ms);
  MotorBrake();
}

//-----------------------------------------------------------------------------
// Pivot Right CM (ล้อขวาหยุด ล้อซ้ายหมุน)
//-----------------------------------------------------------------------------
void PivotRightCM(int speed, float degrees)
{
  float distance_mm = (abs(degrees) / 360.0) * 2.0 * 3.14159265359 * WHEEL_BASE_MM;
  float velocity_mmps = (float)speed * SPEED_TO_MMPS;
  unsigned long time_ms = (unsigned long)((distance_mm / velocity_mmps) * 1000.0 * CM_CORRECTION_FACTOR);

  Motor(speed, 0);
  delay(time_ms);
  MotorBrake();
}

// =============================================================================
//  ฟังก์ชันทดสอบ CM
// =============================================================================

//-----------------------------------------------------------------------------
// ทดสอบโค้ง
//-----------------------------------------------------------------------------
void testCurveCM(int speed, float degrees, float radiusCM)
{
  Serial.println("=== Curve CM Test ===");
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(", Degrees: ");
  Serial.print(degrees);
  Serial.print(", Radius: ");
  Serial.print(radiusCM);
  Serial.println(" cm");

  int speedL, speedR;
  calculateCurveSpeeds(speed, radiusCM, true, speedL, speedR);
  Serial.print("Left wheel speed: ");
  Serial.print(speedL);
  Serial.print(", Right wheel speed: ");
  Serial.println(speedR);

  unsigned long curveTime = calculateCurveTime(degrees, radiusCM, speed);
  Serial.print("Calculated time: ");
  Serial.print(curveTime);
  Serial.println(" ms");

  delay(1000);
  CurveLeftCM(speed, degrees, radiusCM);

  Serial.println("Done!");
}

//-----------------------------------------------------------------------------
// ทดสอบ Spin จาก Wheel Base
//-----------------------------------------------------------------------------
void testSpinCalc(int speed, float degrees)
{
  Serial.println("=== Spin Calc Test ===");
  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print(", Degrees: ");
  Serial.println(degrees);

  float distance = calculateTurnDistance(degrees);
  Serial.print("Turn distance per wheel: ");
  Serial.print(distance);
  Serial.println(" mm");

  unsigned long turnTime = calculateTurnTime(degrees, speed);
  Serial.print("Calculated time: ");
  Serial.print(turnTime);
  Serial.println(" ms");

  delay(1000);
  SpinRightCalc(speed, degrees);

  Serial.println("Done! Measure actual angle.");
}