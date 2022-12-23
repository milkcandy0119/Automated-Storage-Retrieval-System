#include <IRremote.h> 

#define cint const int
#define H HIGH
#define L LOW
#define INP INPUT
#define OTP OUTPUT
//car MP3
#define botton_0 0xFF6897
#define botton_0a C101E57B
#define botton_1 0xFF30CF
#define botton_1a 9716BE3F
#define botton_2 0xFF18E7
#define botton_2a 3D9AE3F7
#define botton_3 0xFF7A85
#define botton_3a 6182021B
#define botton_4 0xFF10EF
#define botton_4a 8C22657B
#define botton_5 0xFF38C7
#define botton_5a 488F3CBB
#define botton_6 0xFF5AA5
#define botton_6a 449E79F
#define botton_7 0xFF42BD
#define botton_7a 32C6FDF7
#define botton_8 0xFF4AB5
#define botton_8a 1BC0157B
#define botton_9 0xFF52AD
#define botton_9a 3EC3FC1B

cint spd=255;  //0-255 speed
cint control=180; //lift motor speed
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

int task;

int data[10];

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
  
  In_Client();
  Serial.println (task);
  //do task
  /*
  data[task]=(data[task]+1)%2;// 1 in 0 out
  while(SM!=1){
    linefollower(SL,SR);
  }
  mstop();
  turnright(SL,SR);
  int count=0;
  while(count != (task/3==0)? task/3 : (task+3)/3){  //待改task==count 怪怪的 OK
    if(SM==1){
      mstop();
      count++;
      delay(1000);
    }
    else{
      linefollower(SL,SR);
    }
  }
  turnright(SL,SR);
  up_and_down(1); //get 1~3 4~6 7~9
  while(SM!=1){
    linefollower(SL,SR);
  }
  mstop();
  up_and_down(3);
  */
}

void In_Client(){
  irrecv.resume();
  while(!results.value!=botton_0){
    if(irrecv.decode(&results)){
      CheckCode();
      irrecv.resume(); // 重複偵測
      if(results.value==botton_0){
        Serial.println ("Out!");
        return;
      }
      delay(100);
    }
  } 
}

void up_and_down(int op){
  if(op==0){ //0 down
    m_down();
    delay(1000);
    //待調整...
    //待調整...
    //待調整...
    mstop();
  }
  else if(op==1){ //1 up
    m_up();
    delay(1000);
    //待調整...
    //待調整...
    //待調整...
    mstop();
  }
  else{ //3 put in
     m_up();
     m_down();
     mforward();
     mback();
    //待調整...
    //待調整...
    //待調整...
    mstop();
  }
  mback();
}

void CheckCode(){
  switch(results.value){
    case botton_0:
      Serial.println ("Button 0");
      break;
    case botton_1:
      Serial.println ("Button 1");
      task=1;
      break;
    case botton_2:
      Serial.println ("Button 2");      
      task=2;
      break;
    case botton_3:
      Serial.println ("Button 3");
      task=3;
      break;
    case botton_4:
      Serial.println ("Button 4");
      task=4;
      break;
    case botton_5:
      Serial.println ("Button 5");
      task=5;
      break;
    case botton_6:
      Serial.println ("Button 6");
      task=6;
      break;
    case botton_7:
      Serial.println ("Button 7");
      task=7;
      break;
    case botton_8:
      Serial.println ("Button 8");
      task=8;
      break;
    case botton_9: 
      Serial.println ("Button 9");
      task=9;
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
  analogWrite(In5,0);
  analogWrite(In6,0);
}

int m_up(){
  analogWrite(In5,control);
  analogWrite(In6,0);
}

int m_down(){
  analogWrite(In5,0);
  analogWrite(In6,control);
}
