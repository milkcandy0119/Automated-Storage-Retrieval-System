#define cint const int
#define H HIGH
#define L LOW
#define INP INPUT
#define OTP OUTPUT
cint In1=13;
cint In2=12;
cint In3=11;
cint In4=10;
cint spd=75;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(In1,OTP);
  pinMode(In2,OTP);
  pinMode(In3,OTP);
  pinMode(In4,OTP);
}

void loop() {
  // put your main code here, to run repeatedly:

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
