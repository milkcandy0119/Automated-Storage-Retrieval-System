# Automated Storage & Retrieval System
For CSHS maker class (by 307)

## Resource
allways download IRremote by shirriff \
if not found \
https://github.com/coopermaa/Arduino-IRremote.git => if dont have IRremote in arduino

## Update
> 2022/11/22 -> basic linefollower / motor control (L298N) / Sensor control / basic movement / some val \
> 2022/11/23 -> motor_test \
> 2022/11/24 -> debug (motor left&right) / include <IRremote.h> / REVC / CAR MP3 \
> 2022/11/25 -> debug (REVC / CAR MP3) \
> 2022/11/26 -> debug (In_Client()) / add main step / function add up_and_down & In_Client / easy task contral \
> 2022/11/26 -> found a bug let us confuse???

## Function
> CheckCode() //Car MP3 1~9 \
> linefollower(SensorLeft, SensorRight) \
> up_and_down(int op) \
> In_Client() 

## Robot Main Movement
> turnleft(SensorLeft, SensorRight) -> 90 degree \
> turnright(SensorLeft, SensorRight) -> 90 degree \
> mforward() -> forward \
> mback() -> backword \
> mleft() -> left \
> mright() -> right \
> mstop() -> stop 

## Lift System Motor Control
> m_up() -> up \
> m_down -> down 
