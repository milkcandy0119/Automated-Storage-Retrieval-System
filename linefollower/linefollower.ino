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
cint LineFollower1=11;  //SensorLeft
cint LineFollower2=12;  //SensorRight
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
  Serial.println("ouob");
  In_Client();
  //(task%3)==0 ? 3 : task%3
  int opkey=(task%3)==0 ? 3 : task%3;
  mstop();
  for(int i=0;i<opkey;i++){
    while(SM){
      SM=digitalRead(LineFollower3);  //SensorMark 右
      Serial.println(SM);
      linefollower();
      //Serial.println (SR);
    }
    if(i<opkey-1){
      SM=digitalRead(LineFollower3);
      while(SM==0){
        mforward();
        SM=digitalRead(LineFollower3);
      }
      mstop();   
    }
    SM=digitalRead(LineFollower3);
  }
  mstop();
  delay(1000);
  turnright();
  mstop();
  

  if((task-1)/3==0){
    //put in
  }else if((task-1)/3==1){
    up_and_down(1);
    mstop();
    int layer=0;
    delay(1000);
    //m_down();
    delay(25);
    mstop();
    delay(1000);
    //put in
  }else if((task-1)/3==2){
    up_and_down(1);
    mstop();
    delay(1000);
    up_and_down(1);
    mstop();
    delay(1000);
    //put in
  }
  //shaking();
  delay(1000);
  SM=digitalRead(LineFollower3);
  while(SM!=0){
    linefollower();
    SM=digitalRead(LineFollower3);
  }
  mstop(); 
  mforward();
  delay(300);
  mstop();
  delay(1000);
  m_down();
  delay(100);
  mstop();
  delay(3000);
  mback();
  delay(400);
  mstop();
  //回程
  mback();
  delay(500);
  SM=digitalRead(LineFollower3);
  while(SM){
      SM=digitalRead(LineFollower3);  //SensorMark 右
      Serial.println(SM);
      mback();
      //Serial.println (SR);
  }
  delay(10);
  turnright();
  delay(1000);
  mforward();
  delay(300);
  shaking();
  SM=digitalRead(LineFollower3);
  while(SM){
      SM=digitalRead(LineFollower3);  //SensorMark 右
      Serial.println(SM);
      linefollower();
      //Serial.println (SR);
  }
  mstop();
  
  //歸零
  if((task-1)/3==0){
    up_and_down(1);
    mstop();
    delay(1000);
  }else if((task-1)/3==1){
    up_and_down(0);
    mstop();
    delay(1000);
    //put in
  }else if((task-1)/3==2){
    up_and_down(0);
    mstop();
    delay(1000);
    up_and_down(0);
    mstop();
    delay(1000);
    //put in
  }
  shaking();
  delay(1000);
  turnleft();
  mstop();
  
  
  /*
  if(task == 5){
    up_and_down(1);
    mstop();
  }else if(task == 8){
    up_and_down(0);
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
  }else if(task == 6){
    for(int i=0;i<5;i++){
      m_up();
      delay(80);
      mstop();
      delay(10);
    }
  }else if(task == 7){
    for(int i=0;i<20;i++){
      m_down();
      delay(5);
      mstop();
      delay(40);
    }
  }else if(task == 9){
    mstop();
    for(int i=0;i<3;i++){
      while(SM){
        SM=digitalRead(LineFollower3);  //SensorMark 右
        Serial.println(SM);
        linefollower();
        //Serial.println (SR);
      }
      if(i<2){
        SM=digitalRead(LineFollower3);
        while(SM==0){
           mforward();
           SM=digitalRead(LineFollower3);
        }
        mstop();
      }
      SM=digitalRead(LineFollower3);
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
    layer=digitalRead(LineFollower4);
    while(!layer){
      m_down();
      delay(6);
      mstop();
      delay(1);
      layer=digitalRead(LineFollower4);
    }
    while(layer){
      layer=digitalRead(LineFollower4);
      m_down();
      layer=digitalRead(LineFollower4);
      delay(1);
      layer=digitalRead(LineFollower4);
      mstop();
      layer=digitalRead(LineFollower4);
      delay(6);
      layer=digitalRead(LineFollower4);
    }
    mstop();
  }
  else if(op==1){ //1 up
    layer=digitalRead(LineFollower4);
    while(!layer){
      m_up();
      delay(6);
      mstop();
      delay(1);
      layer=digitalRead(LineFollower4);
    }
    while(layer){
      layer=digitalRead(LineFollower4);
      m_up();
      delay(6);
      layer=digitalRead(LineFollower4);
      mstop();
      delay(1);
      layer=digitalRead(LineFollower4);
    }
    mstop();
  }
  else if(op==2){ //3 put in
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

int sdown(){
  m_down();
  delay(10);
  mstop();
  delay(40);
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

void shaking(){
  mstop();
  delay(500);
  mleft();
  delay(100);
  mstop();
  mright();
  delay(100);
  mstop();
}
