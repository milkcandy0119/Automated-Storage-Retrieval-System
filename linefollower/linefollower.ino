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


cint spd=255;  //0-255 speed
cint control=255; //lift motor speed
cint gangan_timer=370; //node
cint timer=10; //ms *1ms=0.001s
//RECV
cint RECV_PIN = 9;
//Sensor
cint LineFollower1=10;  //SensorLeft
cint LineFollower2=11;  //SensorRight
cint LineFollower3=13;  //SensorMark
//L298N
cint In1=3; //motor input1(right)
cint In2=4; //motor input2(right)
cint In3=5; //motor input3(left)
cint In4=6; //motor input4(left)
cint In5=7; //lift input1
cint In6=8; //lift input2

cint rgb=2;

double is_item=1/8;
int init_speed=40;

IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構

int task,SM=1;

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
  pinMode(rgb,OTP);
  //RECV
  irrecv.enableIRIn(); // 啟動接收
}

void loop() {
  SM=1;
  digitalWrite(rgb,1);
  delay(1000);
  digitalWrite(rgb,0);
  In_Client();
  if(task == 1){
    for(int i=0;i<20;i++){
      m_up();
      delay(5);
      mstop();
      delay(40);
    }
    mstop();
  }else if(task == 3){
    for(int i=0;i<20;i++){
      m_down();
      delay(5);
      mstop();
      delay(40);
    }
    mstop();
  }else if(task == 2){
    mforward();
    delay(1000);
    mstop();
  }else if(task == 8){
    mback();
    delay(1000);
    mstop();
  }else if(task == 4){
    mleft();
    delay(1000);
    mstop();
  }else if(task == 6){
      analogWrite(rgb,1);
      delay(2000);
      analogWrite(rgb,0);
    /*
    mright();
    delay(1000);
    mstop();
    \*/
  }else if(task == 5){
    mstop();
    while(SM){
      SM=digitalRead(LineFollower3);  //SensorMark
      linefollower();
      //Serial.println (SR);
    }
    mstop();
    delay(1000);
    turnleft();
    mstop();
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
  irrecv.resume();
  while(!results.value!=botton_0){
    if(irrecv.decode(&results)){
      CheckCode();
      irrecv.resume(); // 重複偵測
      if(results.value==botton_0){
        Serial.println ("Out!");
        return;
      }
      delay(1000);
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
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);
      break;
    case botton_1:
      Serial.println ("Button 1");
      task=1;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);      
      break;
    case botton_2:
      Serial.println ("Button 2");      
      task=2;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);     
      break;
    case botton_3:
      Serial.println ("Button 3");
      task=3;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);     
      break;
    case botton_4:
      Serial.println ("Button 4");
      task=4;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);     
      break;
    case botton_5:
      Serial.println ("Button 5");
      task=5;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);      
      break;
    case botton_6:
      Serial.println ("Button 6");
      task=6;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);
      break;
    case botton_7:
      Serial.println ("Button 7");
      task=7;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);      
      break;
    case botton_8:
      Serial.println ("Button 8");
      task=8;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);
      break;
    case botton_9: 
      Serial.println ("Button 9");
      task=9;
      digitalWrite(rgb,1);
      delay(2000);
      digitalWrite(rgb,0);      
      break;
        
    default:
      Serial.println(results.value, HEX);
      break;
  }
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
