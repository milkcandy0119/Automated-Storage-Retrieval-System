#define cint const int
#define H HIGH
#define L LOW
#define INP INPUT
#define OTP OUTPUT

cint spd=75;  //0-255 speed
cint control=50; //lift motor speed
cint gangan_timer=500; //node
cint timer=100; //ms *1ms=0.001s
cint LineFollower1=13;  //SensorLeft
cint LineFollower2=12;  //SensorRight
cint LineFollower3=11;  //SensorMark

//L298N
cint In1=1; //motor input1
cint In2=2; //motor input2
cint In3=3; //motor input3
cint In4=4; //motor input4
cint In5=5; //lift input1
cint In6=6; //lift input2

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
}

void loop() {
  int SL=digitalRead(LineFollower1);  //SensorLeft
  int SR=digitalRead(LineFollower2);  //SensorRight
  int SM=digitalRead(LineFollower3);  //SensorMark
  linefollower(SL,SR);
}

//1=white 0=black
void linefollower(int l,int r){
  if(l==1 && r==1){
    mforword();
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
  mforword()
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
  mforword()
  delay(gangan_timer);
  while(!(l==0 && r==0)){
    mright();
  }
  while(!(l==1 && r==1)){
    mright();
  }
  mstop();
}

int mforword(){//1010
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
  analogWrite(In1,0);
  analogWrite(In2,0);
  analogWrite(In3,spd);
  analogWrite(In4,0);
}

int mright(){//1000
  analogWrite(In1,spd);
  analogWrite(In2,0);
  analogWrite(In3,0);
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
