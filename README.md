# 🤖 MyRobot Complete - Arduino Robot Library

<div align="center">

![Version](https://img.shields.io/badge/version-2.0-blue.svg)
![Arduino](https://img.shields.io/badge/Arduino-RP2040%20%7C%20RP2350-00979D.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Status](https://img.shields.io/badge/status-active-success.svg)

**ไลบรารี่ครบครันสำหรับหุ่นยนต์แข่งขัน พร้อมระบบควบคุม PID, Gyro และแขนกล**

[เริ่มต้นใช้งาน](#-quick-start) • [คำสั่งทั้งหมด](#-คำสั่งพื้นฐาน) • [ตัวอย่าง](#-ตัวอย่างโค้ด) • [คำสั่งย่อ](#-คำสั่งย่อ-shorthand)

</div>

---

## 📖 สารบัญ

<table>
<tr>
<td width="50%">

**🎯 เริ่มต้น**

- [ความสามารถ](#✨-ความสามารถหลัก)
- [ฮาร์ดแวร์](#🔧-ฮาร์ดแวร์ที่ต้องใช้)
- [การติดตั้ง](#📥-การติดตั้ง)
- [Quick Start](#🚀-quick-start)

</td>
<td width="50%">

**📚 คู่มือใช้งาน**

- [คำสั่งพื้นฐาน](#📚-คำสั่งพื้นฐาน)
- [คำสั่งย่อ](<#🎯-คำสั่งย่อ-(shorthand)>)
- [การจูนค่า](#⚙️-การจูนค่า)
- [ตัวอย่างโค้ด](#📝-ตัวอย่างโค้ด)

</td>
</tr>
</table>

---

## ✨ ความสามารถหลัก

<table>
<tr>
<td width="33%" align="center">

### 🎯 เดินตามเส้น

PID Control<br>
เซ็นเซอร์หน้า-หลัง<br>
ตรวจจับแยกอัตโนมัติ

</td>
<td width="33%" align="center">

### 🧭 Gyro Control

เดินตรงแม่นยำ<br>
หมุนตามองศาที่กำหนด<br>
ระบบทิศทาง Absolute

</td>
<td width="33%" align="center">

### 🦾 แขนกล

ควบคุม Servo 6 ตัว<br>
5 ระดับความสูง<br>
เปิด-ปิดกรงเล็บ

</td>
</tr>
<tr>
<td align="center">

### ⚙️ Auto Tuning

ปรับ PID ตาม Speed<br>
Motor Offset อัตโนมัติ<br>
Calibration ง่าย

</td>
<td align="center">

### 💾 EEPROM

บันทึกค่า Calibration<br>
เรียกใช้ได้ทันที<br>
ไม่ต้องตั้งค่าใหม่

</td>
<td align="center">

### 🎮 ง่ายต่อการใช้งาน

คำสั่งสั้น กระชับ<br>
40+ คำสั่งย่อ<br>
Documentation ครบ

</td>
</tr>
</table>

---

## 🔧 ฮาร์ดแวร์ที่ต้องใช้

| อุปกรณ์        | รุ่น/สเปค                  | หมายเหตุ            |
| -------------- | -------------------------- | ------------------- |
| 🎛️ **Board**   | MyMakers RP2040/RP2350 Pro | บอร์ดหลัก           |
| 🧭 **Gyro**    | BMI160 (I2C: 0x69)         | วัดการหมุน          |
| 🎯 **Sensor**  | MCP3008 x2 (16 ช่อง)       | อ่านค่าเซ็นเซอร์    |
| ⚙️ **Motor**   | PWM 12-bit (2 ช่อง)        | ควบคุมมอเตอร์       |
| 🦾 **Servo**   | 6 ตัว (Pin 34-39)          | แขนกล               |
| 💾 **EEPROM**  | CAT24C256 (I2C: 0x50)      | เก็บค่า Calibration |
| 🔘 **Button**  | 2 ปุ่ม                     | เริ่มงาน/หยุด       |
| 💡 **LED RGB** | 1 ชุด                      | แสดงสถานะ           |
| 🔊 **Buzzer**  | 1 ตัว                      | เสียงแจ้งเตือน      |

---

## 📥 การติดตั้ง

### ขั้นตอนที่ 1: ติดตั้ง Arduino IDE

1. **ดาวน์โหลด Arduino IDE 2.x**

   - 🔗 [arduino.cc/en/software](https://www.arduino.cc/en/software)
   - รองรับ Windows, Mac, Linux
     <img
       src="https://lh3.googleusercontent.com/d/1lQXN3XvdlXEALfh2bBt1lDtH7azLC6qs"
       style="border-radius: 24px;"
     />

2. **เปิดโปรแกรมและตรวจสอบเวอร์ชัน**
   ```
   File → About → ตรวจสอบเวอร์ชัน 2.x
   ```

### ขั้นตอนที่ 2: เพิ่ม Board URL

1. เปิด **File → Preferences**
   <img
     src="https://lh3.googleusercontent.com/d/1zOM3ZtS0dw7G5wXj1FZWva9HRgvJfMKC"
     style="border-radius: 24px;"
   />
2. ในช่อง **"Additional Boards Manager URLs"** ใส่:
   ```
   https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
   ```
3. กด **OK**
   <img
     src="https://lh3.googleusercontent.com/d/1GCQzF8oekAxL56g914r1w7Ye4JlFcDhm"
     style="border-radius: 24px;"
   />

### ขั้นตอนที่ 3: ติดตั้งบอร์ด

1. เปิด **Tools → Board → Boards Manager**
2. ค้นหา **"MyMakers"**
3. กด **Install**
4. รอจนติดตั้งเสร็จ
   <img
     src="https://lh3.googleusercontent.com/d/1g7WB3QsRjTdh-PcVeDurPjre0cHPqxmK"
     style="border-radius: 24px;"
   />

### ขั้นตอนที่ 4: เลือกบอร์ดและพอร์ต

```
Tools → Board → Raspberry Pi RP2040 Boards → MyMakers RP2350B
Tools → Port → เลือกพอร์ต COM/USB ที่เชื่อมต่อ
```

<img
    src="https://lh3.googleusercontent.com/d/1GQRyqfRdAAYStm5PmlxGxCbEGv6jCBTB"
    style="border-radius: 24px;"
  />
<img
    src="https://lh3.googleusercontent.com/d/1Uc_Lugs16NsZ4_HQR1dPMkx34meX7wUi"
    style="border-radius: 24px;"
  />

### ขั้นตอนที่ 5: ดาวน์โหลดไลบรารี่

1. ดาวน์โหลด **MY-RP-Pro-V2.0.zip**
2. แตกไฟล์ไปยังโฟลเดอร์ Arduino
3. เปิดไฟล์ **MY-RP-Pro-V2.0.ino**

---

## 🚀 Quick Start

### โครงสร้างโค้ดพื้นฐาน

```cpp
void setup() {
  Serial.begin(115200);

  // ⚙️ ขั้นตอนที่ 1: เริ่มต้นระบบ
  setup_robot();         // เริ่มต้นฮาร์ดแวร์
  initTuning();          // โหลดค่า Tuning
  calibrateGyro();       // Calibrate Gyro
  arm_down_open();       // เตรียมแขน

  // ⏸️ ขั้นตอนที่ 2: รอกดปุ่ม (ไฟเขียว)
  sw();

  // 🏃 ขั้นตอนที่ 3: ทำภารกิจ (ไฟน้ำเงิน)
  Forward(50, 1.5, 500);    // เดินหน้า
  TurnLeft();               // เลี้ยวซ้าย
  TracJC();                 // เดินจนเจอแยก

  // 🏁 ขั้นตอนที่ 4: จบการทำงาน (ไฟแดง + บี๊บ)
  Finish();
}

void loop() {
  // ไม่ต้องเขียนอะไรที่นี่
}
```

### ลำดับการทำงาน

```
┌────────────────────────────────────────────────┐
│  1️⃣  setup_robot()        ตั้งค่าฮาร์ดแวร์      │
│  2️⃣  initTuning()         โหลดค่า PID/Offset  │
│  3️⃣  calibrateGyro()      Calibrate Gyro     │
│  4️⃣  sw()                 🟢 รอกดปุ่ม         │
│  5️⃣  โค้ดภารกิจของคุณ        🔵 ทำงาน          │
│  6️⃣  Finish()             🔴 จบ (บี๊บ 3 ครั้ง) │
└────────────────────────────────────────────────┘
```

---

## 📚 คำสั่งพื้นฐาน

### 🏃 เดินหน้า/ถอยหลัง (Gyro)

<table>
<tr><th>คำสั่ง</th><th>คำอธิบาย</th><th>ตัวอย่าง</th></tr>

<tr>
<td><code>Forward(s,kp,t)</code></td>
<td>เดินหน้าด้วย Gyro</td>
<td><code>Forward(50, 1.5, 500);</code></td>
</tr>

<tr>
<td><code>Backward(s,kp,t)</code></td>
<td>ถอยหลังด้วย Gyro</td>
<td><code>Backward(40, 1.2, 300);</code></td>
</tr>

<tr>
<td><code>ForwardUntil(s,kp,sen)</code></td>
<td>เดินจนเจอเซ็นเซอร์</td>
<td><code>ForwardUntil(50, 1.5, "a0");</code></td>
</tr>

</table>

**พารามิเตอร์:**

- `s` = speed (ความเร็ว 0-100)
- `kp` = ค่า Kp สำหรับการแก้ทิศ (แนะนำ 1.2-1.8)
- `t` = เวลา (มิลลิวินาที)
- `sen` = เซ็นเซอร์ เช่น "a0", "a7", "a07"

### 🔄 หมุนตัว (Gyro)

<table>
<tr><th>คำสั่ง</th><th>คำอธิบาย</th><th>ตัวอย่าง</th></tr>

<tr>
<td><code>SpinDegree(s,d,m)</code></td>
<td>หมุนตามองศา</td>
<td><code>SpinDegree(30, 90, 0);</code></td>
</tr>

<tr>
<td><code>TurnToHeading(s,h)</code></td>
<td>หมุนไปทิศที่กำหนด</td>
<td><code>TurnToHeading(30, 90);</code></td>
</tr>

<tr>
<td><code>TurnToFront(s)</code></td>
<td>หมุนไปทิศหน้า (0°)</td>
<td><code>TurnToFront(30);</code></td>
</tr>

<tr>
<td><code>TurnToRight(s)</code></td>
<td>หมุนไปทิศขวา (90°)</td>
<td><code>TurnToRight(30);</code></td>
</tr>

</table>

**Mode:**

- `0` = Relative (หมุนจากตำแหน่งปัจจุบัน)
- `1` = Absolute (หมุนไปทิศที่กำหนด)

**Heading (ทิศทาง):**

- `0°` = หน้า
- `90°` = ขวา
- `180°` = หลัง
- `270°` = ซ้าย

### ↪️ เลี้ยว (ตามเซ็นเซอร์)

<table>
<tr><th>คำสั่ง</th><th>คำอธิบาย</th><th>ตัวอย่าง</th></tr>

<tr>
<td><code>TurnLeft()</code></td>
<td>เลี้ยวซ้ายจนเจอเส้น</td>
<td><code>TurnLeft();</code></td>
</tr>

<tr>
<td><code>TurnRight()</code></td>
<td>เลี้ยวขวาจนเจอเส้น</td>
<td><code>TurnRight();</code></td>
</tr>

<tr>
<td><code>UTurnLeft()</code></td>
<td>กลับตัวซ้าย 180°</td>
<td><code>UTurnLeft();</code></td>
</tr>

<tr>
<td><code>Left(s,t)</code></td>
<td>หมุนซ้ายตามเวลา</td>
<td><code>Left(50, 200);</code></td>
</tr>

</table>

### 📍 เดินตามเส้น

<table>
<tr><th>คำสั่ง</th><th>คำอธิบาย</th><th>ตัวอย่าง</th></tr>

<tr>
<td><code>TracJC()</code></td>
<td>เดินจนเจอแยก (เตรียมเลี้ยว)</td>
<td><code>TracJC();</code></td>
</tr>

<tr>
<td><code>TracJCSpeed()</code></td>
<td>เดินเร็วจนเจอแยก (ผ่านไป)</td>
<td><code>TracJCSpeed();</code></td>
</tr>

<tr>
<td><code>TracJCSlow()</code></td>
<td>เดินช้าจนเจอแยก</td>
<td><code>TracJCSlow();</code></td>
</tr>

<tr>
<td><code>TracBack()</code></td>
<td>ถอยหลังจนเจอแยก</td>
<td><code>TracBack();</code></td>
</tr>

</table>

### 🦾 แขนกล

<table>
<tr><th>คำสั่ง</th><th>คำอธิบาย</th></tr>

<tr>
<td><code>arm_down_open()</code></td>
<td>แขนลง + เปิดกรงเล็บ</td>
</tr>

<tr>
<td><code>arm_close()</code></td>
<td>ปิดกรงเล็บ (หยิบ)</td>
</tr>

<tr>
<td><code>arm_cm_close()</code></td>
<td>ยกแขนขึ้น + ปิดกรงเล็บ</td>
</tr>

<tr>
<td><code>arm_cm_2cm_close()</code></td>
<td>ยก 2 เซน + ปิดกรงเล็บ</td>
</tr>

<tr>
<td><code>arm_cm_3cm_open()</code></td>
<td>ยก 3 เซน + เปิดกรงเล็บ</td>
</tr>

<tr>
<td><code>arm_level(3)</code></td>
<td>ยกระดับ 3 (1-5)</td>
</tr>

</table>

**ระดับความสูง:** 1 (ต่ำสุด) → 5 (สูงสุด)

---

## 🎯 คำสั่งย่อ (Shorthand)

### 📋 ตารางเปรียบเทียบ

<table>
<tr>
<th width="20%">หมวด</th>
<th width="40%">คำสั่งเต็ม</th>
<th width="20%">คำสั่งย่อ</th>
<th width="20%">ตัวอย่าง</th>
</tr>

<tr>
<td rowspan="4"><strong>🏃 เดินหน้า</strong></td>
<td><code>Forward()</code></td>
<td><code>FD()</code></td>
<td><code>FD();</code></td>
</tr>
<tr>
<td><code>ForwardDelay(500)</code></td>
<td><code>FDD(500)</code></td>
<td><code>FDD(500);</code></td>
</tr>
<tr>
<td><code>ForwardSpeedTime(60,800)</code></td>
<td><code>FST(60,800)</code></td>
<td><code>FST(60,800);</code></td>
</tr>
<tr>
<td><code>MotorStop()</code></td>
<td><code>MS()</code></td>
<td><code>MS();</code></td>
</tr>

<tr>
<td rowspan="3"><strong>🔄 เลี้ยว</strong></td>
<td><code>TurnLeft()</code></td>
<td><code>TL()</code></td>
<td><code>TL();</code></td>
</tr>
<tr>
<td><code>TurnRight(60)</code></td>
<td><code>TR(60)</code></td>
<td><code>TR(60);</code></td>
</tr>
<tr>
<td><code>UTurnLeft()</code></td>
<td><code>UTL()</code></td>
<td><code>UTL();</code></td>
</tr>

<tr>
<td rowspan="3"><strong>📍 ตามเส้น</strong></td>
<td><code>TracJC()</code></td>
<td><code>TJ()</code></td>
<td><code>TJ();</code></td>
</tr>
<tr>
<td><code>TracJCSpeed()</code></td>
<td><code>TJSP()</code></td>
<td><code>TJSP();</code></td>
</tr>
<tr>
<td><code>TracJCSlow()</code></td>
<td><code>TJSL()</code></td>
<td><code>TJSL();</code></td>
</tr>

<tr>
<td rowspan="3"><strong>🧭 Gyro</strong></td>
<td><code>SpinDegree(30,90,0)</code></td>
<td><code>SD(30,90,0)</code></td>
<td><code>SD(30,90,0);</code></td>
</tr>
<tr>
<td><code>SpinLeft(30,90)</code></td>
<td><code>SL(30,90)</code></td>
<td><code>SL(30,90);</code></td>
</tr>
<tr>
<td><code>TurnToFront(30)</code></td>
<td><code>TTF(30)</code></td>
<td><code>TTF(30);</code></td>
</tr>

<tr>
<td rowspan="3"><strong>🦾 แขน</strong></td>
<td><code>arm_down_open()</code></td>
<td><code>GDP()</code></td>
<td><code>GDP();</code></td>
</tr>
<tr>
<td><code>arm_close()</code></td>
<td><code>GGU()</code></td>
<td><code>GGU();</code></td>
</tr>
<tr>
<td><code>arm_cm_3cm_close()</code></td>
<td><code>GGU3()</code></td>
<td><code>GGU3();</code></td>
</tr>

</table>

### 🔥 คำสั่งพิเศษ

| คำสั่ง        | คำอธิบาย                           |
| ------------- | ---------------------------------- |
| `TJCSS(3)`    | วิ่งผ่าน 3 แยก แล้ว TracJC 1 ครั้ง |
| `TJCSSL(2)`   | วิ่งผ่าน 2 แยก แล้ว TracJCSlow     |
| `TJCSSA(3,1)` | วิ่งผ่าน 3 แยก แล้ว TracJC 1 ครั้ง |

📖 [ดูคำสั่งย่อทั้งหมด 40+ คำสั่ง](Short_commands.ino)

---

## 📐 ฟังก์ชันเดินตามระยะทาง (CM)

ฟังก์ชันเหล่านี้ช่วยให้สั่งหุ่นยนต์เดินตามระยะทางที่แม่นยำเป็นเซนติเมตร โดยใช้การคำนวณจากขนาดล้อและความเร็ว

### 🔧 การตั้งค่า Calibration

ก่อนใช้งาน ต้องตั้งค่าขนาดล้อในไฟล์หลัก:

```cpp
// ตั้งค่าขนาดล้อ (วัดรวมยางด้วย!)
float WHEEL_DIAMETER_MM = 42.0;    // เส้นผ่านศูนย์กลางล้อ (mm)
float WHEEL_BASE_MM = 120.0;       // ระยะห่างระหว่างล้อซ้าย-ขวา (mm)
float SPEED_TO_MMPS = 3.0;         // ค่า calibrate (mm ต่อ speed ต่อวินาที)
float CM_CORRECTION_FACTOR = 1.0;  // ตัวแก้ไขระยะ (1.0 = ไม่แก้)
```

> ⚠️ **สำคัญ:** การวัด WHEEL_DIAMETER_MM ต้อง**รวมยาง**ของล้อด้วย เพราะยางคือส่วนที่สัมผัสพื้นจริง

### 📊 สูตรการคำนวณ

```
เส้นรอบวงล้อ = π × เส้นผ่านศูนย์กลาง
ความเร็ว (mm/s) = speed × SPEED_TO_MMPS
เวลา (ms) = (ระยะทาง_mm / ความเร็ว_mm/s) × 1000
```

### 🚀 ฟังก์ชันหลัก

<table>
<tr>
<th>ฟังก์ชัน</th>
<th>คำอธิบาย</th>
<th>ตัวอย่าง</th>
</tr>

<tr>
<td colspan="3"><strong>🏃 เดินหน้า/ถอยหลัง</strong></td>
</tr>
<tr>
<td><code>ForwardCM(speed, cm)</code></td>
<td>เดินหน้าตามระยะ cm (ไม่ใช้ Gyro)</td>
<td><code>ForwardCM(50, 15);</code></td>
</tr>
<tr>
<td><code>ForwardCM(speed, cm, kp)</code></td>
<td>เดินหน้าตามระยะ cm (ใช้ Gyro)</td>
<td><code>ForwardCM(50, 30, 0.5);</code></td>
</tr>
<tr>
<td><code>BackwardCM(speed, cm)</code></td>
<td>ถอยหลังตามระยะ cm</td>
<td><code>BackwardCM(40, 10);</code></td>
</tr>

<tr>
<td colspan="3"><strong>📍 เดินตามเส้น</strong></td>
</tr>
<tr>
<td><code>TracSpeedCM(speed, cm)</code></td>
<td>เดินตามเส้นตามระยะ cm</td>
<td><code>TracSpeedCM(50, 20);</code></td>
</tr>
<tr>
<td><code>TracCM(cm)</code></td>
<td>เดินตามเส้น (ใช้ BaseSpeed)</td>
<td><code>TracCM(15);</code></td>
</tr>
<tr>
<td><code>TracBackCM(speed, cm)</code></td>
<td>ถอยหลังตามเส้นตามระยะ cm</td>
<td><code>TracBackCM(40, 10);</code></td>
</tr>

<tr>
<td colspan="3"><strong>🧭 หมุนตามองศา</strong></td>
</tr>
<tr>
<td><code>TracDegreeSpeedCM(speed, deg)</code></td>
<td>หมุนตามองศา (คำนวณจาก CM)</td>
<td><code>TracDegreeSpeedCM(50, 90);</code></td>
</tr>
<tr>
<td><code>TracDegreeSpeedBackCM(speed, deg)</code></td>
<td>หมุนถอยหลังตามองศา</td>
<td><code>TracDegreeSpeedBackCM(40, -90);</code></td>
</tr>
<tr>
<td><code>SpinLeftCalc(speed, deg)</code></td>
<td>หมุนซ้ายตามองศา (คำนวณ)</td>
<td><code>SpinLeftCalc(50, 90);</code></td>
</tr>
<tr>
<td><code>SpinRightCalc(speed, deg)</code></td>
<td>หมุนขวาตามองศา (คำนวณ)</td>
<td><code>SpinRightCalc(50, 90);</code></td>
</tr>

<tr>
<td colspan="3"><strong>🔄 โค้ง/หมุนรอบล้อ</strong></td>
</tr>
<tr>
<td><code>CurveLeftCM(speed, deg, radius)</code></td>
<td>โค้งซ้ายตามรัศมี cm</td>
<td><code>CurveLeftCM(50, 90, 15);</code></td>
</tr>
<tr>
<td><code>CurveRightCM(speed, deg, radius)</code></td>
<td>โค้งขวาตามรัศมี cm</td>
<td><code>CurveRightCM(50, 90, 15);</code></td>
</tr>
<tr>
<td><code>PivotLeftCM(speed, deg)</code></td>
<td>หมุนรอบล้อซ้าย</td>
<td><code>PivotLeftCM(50, 90);</code></td>
</tr>
<tr>
<td><code>PivotRightCM(speed, deg)</code></td>
<td>หมุนรอบล้อขวา</td>
<td><code>PivotRightCM(50, 90);</code></td>
</tr>

</table>

### 📝 คำสั่งย่อ CM

| คำสั่งย่อ | ฟังก์ชันเต็ม | ตัวอย่าง |
|-----------|--------------|----------|
| `FCM(s,cm)` | ForwardCM | `FCM(50,15);` |
| `BCM(s,cm)` | BackwardCM | `BCM(40,10);` |
| `FCMS(s,cm,kp)` | ForwardCM + Gyro | `FCMS(50,30,0.5);` |
| `TCM(cm)` | TracCM | `TCM(20);` |
| `TSCM(s,cm)` | TracSpeedCM | `TSCM(50,15);` |
| `TBCM(s,cm)` | TracBackCM | `TBCM(40,10);` |
| `TDSCM(s,deg)` | TracDegreeSpeedCM | `TDSCM(50,90);` |
| `TDSBCM(s,deg)` | TracDegreeSpeedBackCM | `TDSBCM(40,-90);` |
| `SLC(s,deg)` | SpinLeftCalc | `SLC(50,90);` |
| `SRC(s,deg)` | SpinRightCalc | `SRC(50,90);` |
| `CLCM(s,d,r)` | CurveLeftCM | `CLCM(50,90,15);` |
| `CRCM(s,d,r)` | CurveRightCM | `CRCM(50,90,15);` |
| `PLCM(s,deg)` | PivotLeftCM | `PLCM(50,90);` |
| `PRCM(s,deg)` | PivotRightCM | `PRCM(50,90);` |

### 🔬 ฟังก์ชัน Calibration

```cpp
// ทดสอบ calibrate ค่า SPEED_TO_MMPS
calibrateSpeedTest(50, 5000);  // วิ่งความเร็ว 50 เป็นเวลา 5 วินาที แล้ววัดระยะจริง

// ทดสอบความแม่นยำ
testForwardCM(50, 30);  // ทดสอบเดินหน้า 30 cm ที่ความเร็ว 50
```

**วิธี Calibrate:**
1. รัน `calibrateSpeedTest(50, 5000);`
2. วัดระยะทางจริงที่หุ่นยนต์เดิน (mm)
3. คำนวณ: `SPEED_TO_MMPS = ระยะทาง_mm / (speed × เวลา_วินาที)`
4. ใส่ค่าใหม่ลงในโค้ด

### 💡 เมื่อไหร่ควรใช้ Gyro?

| ระยะทาง | แนะนำ | เหตุผล |
|---------|-------|--------|
| < 20 cm | `ForwardCM(speed, cm)` ไม่ใช้ Gyro | ระยะสั้น ไม่ทันเบี่ยง |
| 20-30 cm | เลือกได้ | ขึ้นกับพื้นผิว |
| > 30 cm | `ForwardCM(speed, cm, kp)` ใช้ Gyro | ระยะยาว อาจเบี่ยงได้ |

---

## ⚙️ การจูนค่า

### 🎯 PID คืออะไร?

PID (Proportional-Integral-Derivative) เป็นอัลกอริธึมควบคุมที่ใช้ในการเดินตามเส้น เพื่อให้หุ่นยนต์เกาะเส้นได้แม่นยำและเสถียร โดยคำนวณจาก error (การเบี่ยงเบนจากเส้นกลาง)

- Error = ค่าที่หุ่นยนต์เบี่ยงจากเส้น (เบนซ้าย = ลบ, เบนขวา = บวก)
<table>
<tr>
<th>ค่า</th>
<th>ความหมาย</th>
<th>เพิ่ม = ?</th>
<th>ลด = ?</th>
</tr>

<tr>
<td><strong>Kp (Proportional)</strong></td>
<td>แก้ไขตาม error ปัจจุบัน (ยิ่งเบี่ยงมาก ยิ่งแก้แรง</td>
<td>ตอบสนองเร็วขึ้น เกาะเส้นแน่นขึ้น</td>
<td>ตอบสนองช้า เบี้ยวตามโค้งง่าย</td>
</tr>

<tr>
<td><strong>Ki (Integral)</strong></td>
<td>แก้ error สะสม (เบี้ยวค้างซ้ำๆ)</td>
<td>แก้การเบี้ยวเล็กน้อยตลอดทางได้ดี</td>
<td>หากสูงเกินทำให้แกว่งช้า (overshoot)</td>
</tr>

<tr>
<td><strong>Kd (Derivative)</strong></td>
<td>ป้องกันการแกว่ง โดยดูอัตราการเปลี่ยนของ error</td>
<td>ลดการแกว่ง หยุดนิ่งเร็ว</td>
<td>แกว่งซ้าย-ขวามาก</td>
</tr>

</table>

### 📝 ขั้นตอนการจูน (ทีละขั้นตอน)

```
1️⃣ จูน Motor Offset ก่อน (ให้เดินตรงโดยไม่มี PID)
   → testMotorOffset(50, 2000);
   → เบี้ยวซ้าย → เพิ่ม offsetL
   → เบี้ยวขวา → เพิ่ม offsetR

2️⃣ จูน Kp (ตั้ง Ki=0, Kd=0)
   → testPID_Forward(50, 3000);
   → เพิ่ม Kp จนเริ่มแกว่ง → ลดลง 10-20%
   → เป้าหมาย: เกาะเส้นดี ไม่เบี้ยวโค้ง

3️⃣ จูน Kd
   → เพิ่ม Kd เพื่อลดการแกว่ง
   → แกว่งเร็ว → เพิ่ม Kd

4️⃣ จูน Ki (ถ้ายังเบี้ยวเล็กน้อยตลอด)
   → เพิ่ม Ki เล็กน้อย
   → ระวัง overshoot

5️⃣ ทดสอบหลายความเร็ว → ปรับ PID ตาม speed ใน getPID_Forward()
```

### 🎯 ตาราง Troubleshooting PID

| ปัญหา                 | สาเหตุหลัก                     | วิธีแก้หลัก                            |
| --------------------- | ------------------------------ | -------------------------------------- |
| แกว่งซ้าย-ขวารุนแรง   | Kp สูงเกิน / Kd ต่ำเกิน        | ลด Kp หรือ เพิ่ม Kd                    |
| เบี้ยวตามโค้ง         | Kp ต่ำเกิน                     | เพิ่ม Kp                               |
| เบี้ยวตรงเล็กน้อยตลอด | Error สะสม (มอเตอร์ไม่เท่ากัน) | เพิ่ม Ki เล็กน้อย หรือจูน Motor Offset |
| ตอบสนองช้า            | Kp ต่ำเกิน                     | เพิ่ม Kp                               |
| Overshoot (แกว่งช้า)  | Ki สูงเกิน                     | ลด Ki                                  |

### 🔧 แก้ไขค่า PID

แก้ที่ไฟล์ `Initial.ino` → ฟังก์ชัน `getPID_Forward()`:

```cpp
void getPID_Forward(int speed, float &kp, float &ki, float &kd) {
  if (speed <= 50) {
    kp = 0.45;     // ← แก้ตรงนี้
    ki = 0.0001;   // ← ถ้าเบี้ยวเล็กน้อย เพิ่มค่านี้
    kd = 0.025;    // ← ถ้าแกว่ง เพิ่มค่านี้
  }
  else if (speed <= 70) {
    kp = 0.50;
    ki = 0.0001;
    kd = 0.030;
  }
  // ...
}
```

### 🔧 แก้ไข Motor Offset

แก้ที่ไฟล์ `Initial.ino` → ฟังก์ชัน `getMotorTuning()`:

```cpp
void getMotorTuning(int speed, int &offsetL, int &offsetR) {
  if (speed <= 50) {
    offsetL = 0;    // ← เบี้ยวซ้าย = เพิ่มค่านี้
    offsetR = 2;    // ← เบี้ยวขวา = เพิ่มค่านี้
  }
  // ...
}
```

### 🎯 ตาราง Troubleshooting

| ปัญหา            | สาเหตุ             | วิธีแก้              |
| ---------------- | ------------------ | -------------------- |
| หมุนตัวเกิน      | GYRO_KP สูง        | ลด GYRO_KP           |
| หมุนตัวไม่ถึง    | SPIN_TOLERANCE แคบ | เพิ่ม SPIN_TOLERANCE |
| เลี้ยวไม่ถึง 90° | TURN_DELAY_90 น้อย | เพิ่ม TURN_DELAY_90  |

---

## 📝 ตัวอย่างโค้ด

### 🎯 ตัวอย่างที่ 1: เริ่มต้นพื้นฐาน

```cpp
void setup() {
  Serial.begin(115200);

  // เริ่มต้นระบบ
  setup_robot();
  initTuning();
  calibrateGyro();
  arm_down_open();

  sw();  // รอกดปุ่ม

  // ภารกิจ: เดินหน้า → เลี้ยวซ้าย → เดินจนเจอแยก
  Forward(50, 1.5, 500);
  TurnLeft();
  TracJC();

  Finish();
}

void loop() {}
```

### 🎯 ตัวอย่างที่ 2: ใช้คำสั่งย่อ

```cpp
void setup() {
  setup_robot();
  initTuning();
  sw();

  // โค้ดสั้นลง 50%!
  FST(60, 800);    // ForwardSpeedTime
  TL();            // TurnLeft
  TJ();            // TracJC
  TR();            // TurnRight
  TJSP();          // TracJCSpeed
  MS();            // MotorStop

  Finish();
}
```

### 🎯 ตัวอย่างที่ 3: หยิบ-วาง ของ

```cpp
void setup() {
  setup_robot();
  initTuning();
  sw();

  // เดินไปหยิบของ
  TracJC();
  arm_close();          // หยิบ
  delay(200);
  arm_cm_3cm_close();   // ยก 3 เซน

  // เดินไปวางของ
  UTurnLeft();
  TracJC();
  arm_down_open();      // วาง

  Finish();
}
```

### 🎯 ตัวอย่างที่ 4: เดินเป็นสี่เหลี่ยม (Gyro)

```cpp
void setup() {
  setup_robot();
  initTuning();
  calibrateGyro();

  SetHeading(0);  // ตั้งทิศหน้า = 0°
  sw();

  // เดิน 4 ด้าน
  for(int i=0; i<4; i++) {
    Forward(50, 1.5, 1000);
    SpinDegree(30, 90, 0);   // หมุนขวา 90°
  }

  Finish();
}
```

### 🎯 ตัวอย่างที่ 5: ผ่านหลายแยก

```cpp
void setup() {
  setup_robot();
  initTuning();
  sw();

  // ผ่าน 3 แยก แล้วเลี้ยวซ้าย
  TJCSS(3);        // ผ่าน 3 แยก
  TurnLeft();

  // ผ่าน 2 แยก แล้วหยุด
  TJCSSL(2);

  Finish();
}
```

---

## 📁 โครงสร้างไฟล์

```
MY-RP-Pro-V2.0/
├── 📄 MY-RP-Pro-V2.0.ino      # ไฟล์หลัก + ตั้งค่า
├── ⚙️  Motor.ino               # ควบคุมมอเตอร์
├── 🧭 Gyro.ino                # อ่านค่า BMI160
├── 🎯 Sensor.ino              # อ่านค่า MCP3008
├── 🏃 ForwardBackward.ino     # เดินหน้า/ถอยหลัง
├── 🔄 TracDegree.ino          # หมุนตัว + เดินด้วย Gyro
├── 📍 Trac.ino                # เดินตามเส้น TracJC
├── 🛤️  FLine.ino               # fline/bline Advanced
├── ↪️  Turn.ino                # เลี้ยวซ้าย/ขวา
├── 🦾 Servo.ino               # ควบคุม Servo
├── 🔧 Calibrate.ino           # Calibration
├── ⚙️  Initial.ino             # ตั้งค่า/จูนค่า PID
├── 🎮 Utility.ino             # LED, Buzzer, Button
├── 📋 Short_commands.ino      # คำสั่งย่อ 40+
└── 📖 README.md               # ไฟล์นี้
```

---

## 🤝 การสนับสนุน

<table>
<tr>
<td width="50%">

### 📚 เอกสารเพิ่มเติม

- [คู่มือการใช้งานฉบับเต็ม](https://www.mymakers.online/myrpprov2.php)
- [ตัวอย่างโค้ด](https://github.com/nui4328/My_RP_Bot)
- [Forum สนทนา](https://www.mymakers.online)

</td>
<td width="50%">

### 💬 ติดต่อสอบถาม

- 🌐 Website: [mymakers.online](https://www.mymakers.online)
- 📱 Facebook: [MyMakers Thailand](https://www.facebook.com/profile.php?id=100057567184557)
- 💻 Facebook (ผู้พัฒนาเวอร์ชั่นนี้): [Sirayuth Zx ](https://www.facebook.com/sirayuth.zx/)

</td>
</tr>
</table>


---

<div align="center">

**Made with [Siraxyuth Dev](https://www.siraxuth.xyz/) for Robot Competition**
<a href="https://www.siraxuth.xyz/">
<img
    src="https://lh3.googleusercontent.com/d/1UJECLtCPfMSQofCMZxdM7uBPL_M6nsWH"
    style="border-radius: 24px;"
  />
</a>


[![Website](https://img.shields.io/badge/Website-MyMakers-blue)](https://www.mymakers.online/myrpprov2.php)
[![GitHub](https://img.shields.io/badge/GitHub-My__RP__Bot-black)](https://github.com/nui4328/My_RP_Bot)
[![Version](https://img.shields.io/badge/Version-2.0-green)](https://github.com/nui4328/My_RP_Bot)


## 📄 License

```
Free Non-Commercial License

Copyright (c) 2025 MyMakers

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"),
to use, copy, modify, and distribute the Software **for non-commercial purposes only**.

The Software may be used, modified, and shared **free of charge only**.
Selling, sublicensing, or using the Software for commercial purposes
in any form is strictly prohibited without prior written permission
from the copyright holder.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT.

IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES, OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR
OTHERWISE, ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE OR
THE USE OR OTHER DEALINGS IN THE SOFTWARE.

```
_Last Updated: December 2025_

[🔝 กลับไปด้านบน](#-myrobot-complete---arduino-robot-library)

</div>
