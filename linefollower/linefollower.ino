#include <IRremote.h> 

#define cint const int
#define H HIGH
#define L LOW
#define INP INPUT
#define OTP OUTPUT
//car MP3
#define botton_0 0xFF6897
#define botton_1 0xFF30CF
#define botton_2 0xFF18E7
#define botton_3 0xFF7A85
#define botton_4 0xFF10EF
#define botton_5 0xFF38C7
#define botton_6 0xFF5AA5
#define botton_7 0xFF42BD
#define botton_8 0xFF4AB5
#define botton_9 0xFF52AD

cint spd=75;  //0-255 speed
cint control=50; //lift motor speed
cint gangan_timer=500; //node
cint timer=100; //ms *1ms=0.001s
//RECV
cint RECV_PIN = 10;
//Sensor
cint LineFollower1=13;  //SensorLeft
cint LineFollower2=12;  //SensorRight
cint LineFollower3=11;  //SensorMark
//L298N
cint In1=1; //motor input1(right)
cint In2=2; //motor input2(right)
cint In3=3; //motor input3(left)
cint In4=4; //motor input4(left)
cint In5=5; //lift input1
cint In6=6; //lift input2

IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構

void setup() {
  Serial.begin(9600);
  //Line Follower
  pinMode(LineFollower1,INP);
  pinMode(LineFollower2,INP);
  pinMode(LineFollower3,INP);
  //Main motor
  pinMode(In1,OTP);
  pinMode(In2,OTP);
  pinMode(In3,OTP);
  pinMode(In4,OTP);
  //lift motor
  pinMode(In5,OTP);
  pinMode(In6,OTP);
  //RECV
  irrecv.enableIRIn(); // 啟動接收
}

void loop() {
  int SL=digitalRead(LineFollower1);  //SensorLeft
  int SR=digitalRead(LineFollower2);  //SensorRight
  int SM=digitalRead(LineFollower3);  //SensorMark
  //linefollower(SL,SR);
  if(irrecv.decode(&results)){
    CheckCode();
    irrecv.resume();
    delay(100);
  }
  
}

void CheckCode(){
  switch(results.value){
    case botton_0:
      Serial.println ("Button 0");
      Serial.println(results.value, HEX);
      break;
    case botton_1:
      Serial.println ("Button 1");
      Serial.println(results.value, HEX);
      break;
    case botton_2:
      Serial.println ("Button 2");
      Serial.println(results.value, HEX);
      break;
    case botton_3:
      Serial.println ("Button 3");
      Serial.println(results.value, HEX);
      break;
    case botton_4:
      Serial.println ("Button 4");
      Serial.println(results.value, HEX);
      break;
    case botton_5:
      Serial.println ("Button 5");
      Serial.println(results.value, HEX);
      break;
    case botton_6:
      Serial.println ("Button 6");
      Serial.println(results.value, HEX);
      break;
    case botton_7:
      Serial.println ("Button 7");
      Serial.println(results.value, HEX);
      break;
    case botton_8:
      Serial.println ("Button 8");
      Serial.println(results.value, HEX);
      break;
    case botton_9:
      Serial.println ("Button 9");
      Serial.println(results.value, HEX);
      break;
      
    default:
      Serial.println(results.value, HEX);
      break;
  }
}

//1=white 0=black
void linefollower(int l,int r){
  if(l==1 && r==1){
    mforward();
  }
  else if(l==0 && r==1){
    //mstop();
    //delay(timer);
    mleft();
    //delay(timer);
  }
  else if(l==1 && r==0){
    //mstop();
    //delay(timer);
    mright();
    //delay(timer);
  }
  else if(l==0 && r==0){
    mstop();
    delay(timer);
  }
}

int turnleft(int l,int r){
  mforward();
  delay(gangan_timer);
  while(!(l==0 && r==0)){
    mleft();
  }
  while(!(l==1 && r==1)){
    mleft();
  }
  mstop();
}

int turnright(int l,int r){
  mforward();
  delay(gangan_timer);
  while(!(l==0 && r==0)){
    mright();
  }
  while(!(l==1 && r==1)){
    mright();
  }
  mstop();
}

int mforward(){//1010
  analogWrite(In1,spd);
  analogWrite(In2,0);
  analogWrite(In3,spd);
  analogWrite(In4,0);
}

int mback(){//0101
  analogWrite(In1,0);
  analogWrite(In2,spd);
  analogWrite(In3,0);
  analogWrite(In4,spd);
}

int mleft(){//0010
  analogWrite(In1,spd);
  analogWrite(In2,0);
  analogWrite(In3,0);
  analogWrite(In4,0);
}

int mright(){//1000
  analogWrite(In1,0);
  analogWrite(In2,0);
  analogWrite(In3,spd);
  analogWrite(In4,0);
}

int mstop(){//0000
  analogWrite(In1,0);
  analogWrite(In2,0);
  analogWrite(In3,0);
  analogWrite(In4,0);
}

int m_up(){
  analogWrite(In5,control);
  analogWrite(In6,0);
}

int m_down(){
  analogWrite(In5,0);
  analogWrite(In6,control);
}
