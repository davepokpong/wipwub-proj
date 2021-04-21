# Smart Music Box

## รายชื่อผู้จัดทำ
6210500579 นายสรวิชญ์ ทรัพย์มี
6210503519 นายชนม์ชนัส ทับเที่ยง
6210505210 นายปกป้อง นพคุณ

โปรเจคนี้เป็นของวิชา 01204223 คณะวิศวกรรมศาสตร์ ภาควิชาคอมพิวเตอร์ 
ภาคปลาย ปีการศึกษา 2563 มหาวิทยาลัยเกษตรศาสตร์

## Frontend
-------------------------------------
หน้า main 

ใช้ css ตกแต่ง
  background
  animation ต่างๆ 

ใช้ javascript ในการควบคุม
  button upload ,submit

-------------------------------------

หน้า playlist

ใช้ css ตกแต่ง
  button play, pause, clear
  background
  animation ต่างๆ

ใช้ javascript ในการควบคุมการทำงาน
  button play, pause, clear
  การทำงานของ button play, pause, clear
-------------------------------------

## Backend
-------------------------------------
libraries ต่างๆที่ใช้
- multer ใช้ส่งไฟล์ระหว่าง server
- body-parser จัดไฟล์
- express สร้าง server 
- child_process ส่งคำสั่งให้ rasberry pi ทำงาน

การทำงาน 
รับไฟล์ที่ถูก upload จากหน้าเว็ปไปเก็บไว้ใน /uploads ใน rasberry pi และสั่ง raspberry pi 
ให้รับคำสั่ง mpg123 เพื่อเล่นเพลงที่ถ upload ไปและแสดง led ให้เต้นตามจังหวะเพลง

-------------------------------------

## Hardware
-------------------------------------
อุปกรณ์ที่ใช้:
1.) Raspberry pi model B+ 1 เครื่อง
2.) MCU Board 1 ตัว
3.) Bluetooth Speaker 1 เครื่อง
4.) MAX7219 based dot matrix module size 32*16 จำนวน 1 อัน
5.) PCD Board 1 อัน
6.) Connector 10 ขา 1 อัน
7.) Connector 5 ขา 1 อัน
8.) สายเเพ 1 เส้น
9.) สายจัมเปอร์ 5 ขา 1 เส้น

ขั้นตอนสำหรับการใช้งาน Arduino 
- อัพเดตระบบ
	sudo apt update
	sudo apt upgrade
- ติดตั้ง lxsesson โปรเเกรมจัดการหน้าจอ desktop เเบบกราฟฟิก
	sudo apt install lxsession
- เปิดใช้งาน VNC เรียกคำสั่ง
	sudo raspi-config
	เข้า 1 System Options -> S5 Boot / Auto Login -> B4 Desktop Autologin
	เข้า 3 Interface Options -> P3 VNC -> Yes
	เข้า 2 Display Options -> D1 Resolution -> เลือกขนาดที่เหมาะสม เช่น 1024x768
	เลือก Finish -> Reboot
- เข้าหน้าจอ VNC Viewer ติดตั้ง VNC Viewer เเนะนำ RealVNC
- ใส่ชื่อเครื่องหรือหมายเลข ip ของ raspberrypi เพื่อเชื่อมต่อเครื่อง เเล้วทำการ login
- เข้า Terminal ติดตั้ง browser
	sudo apt install chromium-browser
- เข้า Internet เเล้วเข้าเว็ป https://www.arduino.cc/en/software เพื่อติดตั้ง Arduino IDE สำหรับ Linux ARM 32 bits
- นำไฟล์ที่ดาวน์โหลด (นามสกุล .tar.xz) ไปเเตกไว้ใน /opt ด้วยคำสั่ง
	sudo mkdir -p /opt
	cd /opt
	sudo tar xf ~/Downloads/arduino-1.8.13-linuxarm.tar.xz
- เรียกสคริปต์ติดตั้งทั้งในนามของผู้ใช้เเละผู้ดูเเลระบบ
	cd /opt/arduino-1.8.13
	sudo ./install.sh
	./install.sh
-สำเร็จสามารถเข้า Arduino ที่ Programming

libraries - libraries สำหรับให้ source code ทำงานได้
	- Max72xxPanel เเละ MD_MAX72xx-master คือ libraries สำหรับเเสดงไฟบน dot matrix led
	- arduinoFFT คือ libraries สำหรับคำนวณเกี่ยวกับสัญญาณเเละความถี่ของเสียง
	- Adafruit_GFX_Librery คือ library สำหรับเปลี่ยนข้อความไว้สำหรับเเสดงบนจอ led
	- Adafruit_BusIO คือ library สำหรับทำงาน I2C interface
 ledmatrix.ino ในโฟลเดอร์ code_arduino คือ โค้ดที่จะทำสัญญาณความถี่เสียงที่ raspberrypi เล่นอยู่มาคำนวณเเล้วเเสดงเป็นคลื่นการเต้นตามจังหวะบนจอ dot matrix led

ขั้นตอนสำหรับต่อ bluetooth กับอุปกรณ์ต่างๆ
- เริ่มต้นจากอัปเดตระบบ
	sudo apt update
	sudo apt upgrade
- Install PulseAudio Bluetooth profile
	sudo apt install pulseaudio-module-bluetooth
- Install Bluez เเละ Blueman
	sudo apt install bluez
	sudo apt install blueman
- เพิ่ม user pi เข้าไปในกลุ่ม bluetooth
	sudo usermod -a -G bluetooth pi
- Reboot ระบบ
- เริ่มต้นเปิดระบบ PulseAudio
	systemctl --user start pulseaudio
- เข้าใช้คำสั่งสำหรับ bluetooth
	bluetoothctl
- ค้นหา ip ของอุปกรณ์ที่ต้องการเชื่อมต่อ
	scan on
- หยุดการค้นหา
	scan off
- เชื่อมต่อ ip อุปกรณ์
	connect XX:XX:XX:XX:XX:XX
- เชื่อมต่อสำเร็จ ถ้าต้องการทำงานคำสั่งต่อให้ออกจากระบบ bluetooth
	exit
-------------------------------------
