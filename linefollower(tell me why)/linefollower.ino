#include <SoftwareSerial.h>
#define cint const int
#define H HIGH
#define L LOW
#define INP INPUT
#define OTP OUTPUT

cint spd=255;  //0-255 speed
cint control=255; //lift motor speed
cint gangan_timer=370; //node
cint timer=10; //ms *1ms=0.001s

//Sensor
cint LineFollower1=10;  //SensorLeft
cint LineFollower2=11;  //SensorRight
cint LineFollower3=13;  //SensorMark
cint LineFollower4=2; //updown

//L298N
cint In1=3; //motor input1(right)
cint In2=4; //motor input2(right)
cint In3=5; //motor input3(left)
cint In4=6; //motor input4(left)
cint In5=7; //lift input1
cint In6=8; //lift input2

//cint rgb=2;

double is_item=1/8;
int init_speed=40;

int task=0,SM=1;

int data[10];

SoftwareSerial BT(9,10);

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("bot is ready");
  //Line Follower
  pinMode(LineFollower1,INP);
  pinMode(LineFollower2,INP);
  pinMode(LineFollower3,INP);
  pinMode(LineFollower4,INP);
  //Main motor
  pinMode(In1,OTP);
  pinMode(In2,OTP);
  pinMode(In3,OTP);
  pinMode(In4,OTP);
  //lift motor
  pinMode(In5,OTP);
  pinMode(In6,OTP);
  //pinMode(rgb,OTP);
  
}

void loop() {
  SM=1;
  //digitalWrite(rgb,1);
  //delay(1000);
  //digitalWrite(rgb,0);
  Serial.println("ouob");
  In_Client();
  if(task == 5){
    for(int i=0;i<5;i++){
      m_up();
      delay(80);
      mstop();
      delay(10);
    }
    mstop();
  }else if(task == 8){
    for(int i=0;i<20;i++){
      m_down();
      delay(5);
      mstop();
      delay(40);
    }
    mstop();
  }else if(task == 1){
    mforward();
    delay(1000);
    mstop();
  }else if(task == 4){
    mback();
    delay(1000);
    mstop();
  }else if(task == 2){
    mleft();
    delay(1000);
    mstop();
  }else if(task == 3){
    mright();
    delay(1000);
    mstop();
  }else if(task == 9){
    mstop();
    while(SM){
      SM=digitalRead(LineFollower3);  //SensorMark
      linefollower();
      //Serial.println (SR);
    }
    mstop();
    delay(1000);
    turnright();
    mstop();
  }else if(task==6){
    for(int i=0;i<10;i++){
      mleft();
      delay(500);
      mstop();
      mright();
      delay(500);
      mstop();
    }
  }else{
    mstop();
  }
  
  /*
  mstop();
  In_Client();
  Serial.println (task);
  //do task
  
  //data[task]=(data[task]+1)%2;// 1 in 0 out
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
  int val;
  while(1){
    if(BT.available()){
      val=BT.read()-48;
      if(val==0){
        //Serial.print(val);
        break;
      }
      task=val;
      Serial.print(task);
    }
  }
}

void up_and_down(int op){
  int layer=digitalRead(LineFollower4);
  if(op==0){ //0 down
    while(layer){
      m_down();
      delay(5);
      mstop();
      delay(40);
    }
    mstop();
  }
  else if(op==1){ //1 up
    while(layer){
      m_up();
      delay(5);
      mstop();
      delay(40);
    }
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

//1=white 0=black
void linefollower(){
  int l=digitalRead(LineFollower1);  //SensorLeft
  int r=digitalRead(LineFollower2);  //SensorRight
  
  if(l==0 && r==0){
    mforward();
  }
  if(l==0 && r==1){
    mstop();
    delay(timer);
    mleft();
    delay(timer);
  }
  if(l==1 && r==0){
    mstop();
    delay(timer);
    mright();
    delay(timer);
  }
  if(l==1 && r==1){
    mstop();
    delay(timer);
  }
}

int turnleft(){
  mforward();
  delay(gangan_timer);
  mstop();
  mleft();
  delay(400);
  mstop();
  delay(1000);
  int l=1,r=1;
  while(l==1 or r==1){
    int l=digitalRead(LineFollower1);  //SensorLeft
    int r=digitalRead(LineFollower2);  //SensorRight
    sleft();
    mstop();
    if(l==0 and r==0) break;
  }
}

int turnright(){
  mforward();
  delay(gangan_timer);
  mstop();
  mright();
  delay(400);
  mstop();
  delay(1000);
  int l=1,r=1;
  while(l==1 or r==1){
    int l=digitalRead(LineFollower1);  //SensorLeft
    int r=digitalRead(LineFollower2);  //SensorRight
    sright();
    mstop();
    if(l==0 and r==0) break;
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
  analogWrite(In4,spd);
}

int mright(){//1000
  analogWrite(In1,0);
  analogWrite(In2,spd);
  analogWrite(In3,spd);
  analogWrite(In4,0);
}

int mstop(){//0000
  digitalWrite(In1,L);
  digitalWrite(In2,L);
  digitalWrite(In3,L);
  digitalWrite(In4,L);
  digitalWrite(In5,L);
  digitalWrite(In6,L);
}

int m_up(){
  analogWrite(In5,control);
  analogWrite(In6,0);
}

int m_down(){
  analogWrite(In5,0);
  analogWrite(In6,control);
}

int sright(){
  mright();
  delay(10);
  mstop();
  delay(40);
}

int sleft(){
  mleft();
  delay(10);
  mstop();
  delay(40);
}
