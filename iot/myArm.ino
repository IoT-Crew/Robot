
// Arduino 4DOF Robot Arm
#include <Servo.h> // Serve motor header 

// JoyStick
#define XPOS 0
#define YPOS 1

// 4DOF 
const int SERVOS = 4;
int PIN[SERVOS]; // 서보모터 pin 
int MIN[SERVOS], MAX[SERVOS]; // 최소, 최대 각도
int INITANGLE[SERVOS], previousAngle[SERVOS], currentAngle[SERVOS]; // 초기 각도, 이전 각도, 현재 각도
int value[SERVOS], idle[SERVOS], ANA[SERVOS]; // analog (joystick)

Servo myservo[SERVOS]; // servo list -> [myservo0, myservo1, myservo2, myservo3]

// 시리얼 데이터 전달 (논블로킹 방식)
unsigned long previousTime = 0; // 이전 시간 
unsigned long interval = 1000; // 원하는 간격 (밀리초 단위)

int angleDatas[4]; // 서보 각도
int initAng[4] = {90, 120, 90, 120}; // 초기 각도

void setup()   {
  Serial.begin(9600); // 시리얼 (baudrate) 
  // Base servo 
  PIN[0] = 10; // pin   
  MIN[0] = 0;  // 최소 각도
  MAX[0] = 180; // 최대 각도
  INITANGLE[0] = initAng[0];  // 초기 각도
  ANA[0] = 3; // Joystick analog pin
  // Left servo
  PIN[1] = 6;
  MIN[1] = 40; 
  MAX[1] = 180;
  INITANGLE[1] = initAng[1];
  ANA[1] = 2;
  // Right servo
  PIN[2] = 5;
  MIN[2] = 60;
  MAX[2] = 180;
  INITANGLE[2] = initAng[2];
  ANA[2] = 0;
  // Grip servo
  PIN[3] = 9;
  MIN[3] = 0;
  MAX[3] = 180;
  INITANGLE[3] = initAng[3];
  ANA[3] = 1;
  
  // 초기 위치
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]); // 서보모터 attach <-> dettach
    moveSingleMotorWithSpeed(i, INITANGLE[i], 1000); // (motor, angle, speed) -> speed가 높을수록 느려짐
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i]=INITANGLE[i];
  }
 
}

// 구역 별 이동
void A_move(int speed){
  moveWithSpeed(currentAngle[0], initAng[1], initAng[2], currentAngle[3], speed);
  moveWithSpeed(0, 160, 150, currentAngle[3], speed);
}
void B_move(int speed){
  moveWithSpeed(currentAngle[0], initAng[1], initAng[2], currentAngle[3], speed);
  moveWithSpeed(60, 160, 150, currentAngle[3], speed);
}

void C_move(int speed){
  moveWithSpeed(currentAngle[0], initAng[1], initAng[2], currentAngle[3], speed);
  moveWithSpeed(120, 160, 150, currentAngle[3], speed);
}

void D_move(int speed){
  moveWithSpeed(currentAngle[0], initAng[1], initAng[2], currentAngle[3], speed);
  moveWithSpeed(180, 160, 150, currentAngle[3], speed);
}

void move(int t1, int t2, int t3, int t4){
  Servo servos[SERVOS] = {myservo[0], myservo[1], myservo[2], myservo[3]};
  int targetAngles[SERVOS] = {t1, t2, t3, t4};
  
  for(int i = 0; i < SERVOS; i++){
    int currentAngle = servos[i].read();
    if(currentAngle != targetAngles[i]){
      int step = (currentAngle < targetAngles[i]) ? 1 : -1; // 위치의 스탭 방향을 결정
      while(currentAngle != targetAngles[i]){
        currentAngle += step;
        servos[i].write(currentAngle);
        delay(10);
//        Serial.print("Servo ");
//        Serial.print(i);
//        Serial.print(" Angle: ");
//        Serial.println(currentAngle);
      }
    }
  }
}

// base, left, right, grip 각도
void moveWithSpeed(int t1, int t2, int t3, int t4, int speed) {
  Servo servos[SERVOS] = {myservo[0], myservo[1], myservo[2], myservo[3]};
  int targetAngles[SERVOS] = {t1, t2, t3, t4};
  
  for (int i = 0; i < SERVOS; i++) {
    int currentAngle = servos[i].read();
    if (currentAngle != targetAngles[i]) {
      int step = (currentAngle < targetAngles[i]) ? 1 : -1;
      int delayTime = speed / abs(targetAngles[i] - currentAngle); // 속도에 따른 딜레이 계산
      
      while (currentAngle != targetAngles[i]) {
        currentAngle += step;
        servos[i].write(currentAngle);
        delay(delayTime);
//        Serial.print("Servo ");
//        Serial.print(i);
//        Serial.print(" Angle: ");
//        Serial.println(currentAngle);
      }
    }
  }
}
// void moveWithSpeed(int t1, int t2, int t3, int t4, int speed) {
//   Servo servos[SERVOS] = {myservo[0], myservo[1], myservo[2], myservo[3]};
//   int targetAngles[SERVOS] = {t1, t2, t3, t4};
  
//   for (int i = 0; i < SERVOS; i++) {
//     int currentAngle = servos[i].read();
//     if (currentAngle != targetAngles[i]) {
//       int step = (currentAngle < targetAngles[i]) ? 1 : -1;
//       int delayTime = speed / abs(targetAngles[i] - currentAngle); // 속도에 따른 딜레이 계산
      
//       unsigned long previousTime = millis();
//       while (currentAngle != targetAngles[i]) {
//         unsigned long currentTime = millis();
//         if (currentTime - previousTime >= delayTime) {
//           previousTime = currentTime;
//           currentAngle += step;
//           servos[i].write(currentAngle);
//           Serial.print("Servo ");
//           Serial.print(i);
//           Serial.print(" Angle: ");
//           Serial.println(currentAngle);
//         }
//       }
//     }
//   }
// }

/*
*motor index
0 - base motor
1 - left motor
2 - right motor
3 - gripper motor
*/
void moveSingleMotorWithSpeed(int motorIndex, int targetAngle, int speed){
  if(motorIndex >= 0 && motorIndex < SERVOS){
    Servo servo = myservo[motorIndex]; 
    int currentAngle = servo.read(); // 직전 servo.write를 한 각도를 얻음

    if(currentAngle != targetAngle) {
      // int ans = (a > b) ? x : y; -> true일 때 x, false일 때 y
      int step = (currentAngle < targetAngle) ? 1 : -1; // 방향 설정

      int delayTime = speed / abs(targetAngle - currentAngle); // 멀수록 speed는 빠르게
      while(currentAngle != targetAngle){
        currentAngle += step;
        servo.write(currentAngle);
        delay(delayTime);
//        Serial.print("Servo ");
//        Serial.print(motorIndex);
//        Serial.print(" Angle : ");
//        Serial.println(currentAngle);
      }
    }
  }
}

void openGrip(){
  int currentAngle = myservo[3].read();
  if(currentAngle < 150) {
    int step = (currentAngle < 150) ? 1 : -1;
    while(currentAngle != 150){
      currentAngle += step;
      myservo[3].write(currentAngle);
      delay(10);
//      Serial.print("Servo Gripper Open");
//      Serial.print(" Angle : ");
//      Serial.println(currentAngle);
    }
  }
}
void closeGrip(){
  // 현재 각도를 구해서 step만큼 이동
  int currentAngle = myservo[3].read();
  if(currentAngle != 0){
    int step = (currentAngle < 0) ? 1 : -1;
    while(currentAngle != 0){
      currentAngle += step;
      myservo[3].write(currentAngle);
      delay(10);
//      Serial.print("Servo Gripper Close");
//      Serial.print(" Angle : ");
//      Serial.println(currentAngle);
    }
  }
}

void loop() {
  delay(20); // 로봇팔 속도조정을 위한 딜레이

  // joystick (수동 조작)

  for (int i = 0; i < SERVOS; i++){
    value[i] = analogRead(ANA[i]);
    currentAngle[i] = myservo[i].read();
    angleDatas[i] = currentAngle[i];
    if (value[i] > 612) {
      idle[i] = 0;
    
      if (currentAngle[i] < MAX[i]) ++currentAngle[i];
      if (!myservo[i].attached()){ // attach가 안된 경우 들어감
        myservo[i].attach(PIN[i]); // servo 시동 건다
      }
      myservo[i].write(currentAngle[i]);  
    } else if (value[i] < 412) {
      idle[i] = 0;
      if (currentAngle[i] > MIN[i]) --currentAngle[i];
      if (!myservo[i].attached()){
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);    
    } else {
      ++idle[i];
    }
    // if (idle[i] > 100){
    //   myservo[i].detach(); //서보모터를 일정시간 사용하지 않으면 연결을 끊어둔다.
    //   idle[i] = 0;
    // }  
  }

  // 리액트 버튼 API 구역 데이터를 수신받았을 때
  if(Serial.available() > 0){
    char input = Serial.read();
    if(input == 'A'){
      A_move(1000);
    } else if (input == 'B'){
      B_move(1000);
    } else if (input == 'C'){
      C_move(1000);
    } else if (input == 'D'){
      D_move(1000);
    } else if (input == 'E'){ // close
      closeGrip();
    } else if (input == 'F'){ // open
      openGrip();
    }
  }

   // 
   unsigned long currentTime = millis();
  
   if (currentTime - previousTime >= interval) {
     String result;
     String strS = "{\"data\":[";
     for (int i = 0; i < SERVOS; i++){
       // 원하는 작업 수행
       String str1;
       if(i == 0){
         str1 = "{\"servo\":";
       }else {
         str1 = ",{\"servo\":";
       }
       String str2 = String(i);
       String str3 = ",\"angle\":";
       String str4 = String(angleDatas[i]);
       String str5 = "}";
      
       result += str1+str2+str3+str4+str5;
     }
     String strE = "]}";
     Serial.println(strS+result+strE); // JSON data 시리얼로 전송!
     previousTime = currentTime; // 현재 시간으로 갱신
   }
}