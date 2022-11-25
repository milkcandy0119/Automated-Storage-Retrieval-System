# linefollower
For CSHS maker class(by 307)

## resource
allways download IRremote by shirriff \
if not found \
https://github.com/coopermaa/Arduino-IRremote.git => if dont have IRremote in arduino

## update
> 2022/11/22 -> basic linefollower / motor control(L298N) / Sensor control / basic movement / some val \
> 2022/11/23 -> motor_test \
> 2022/11/24 -> debug(motor left&right) / include <IRremote.h> / REVC / CAR MP3 \
> 2022/11/25 -> debug(REVC / CAR MP3)

## function
> CheckCode() //Car MP3 1~9 \
> linefollower(SensorLeft, SensorRight) \

## robot main movement
> turnleft(SensorLeft, SensorRight) -> 90 degree \
> turnright(SensorLeft, SensorRight) -> 90 degree \
> mforward() -> forward \
> mback() -> backword \
> mleft() -> left \
> mright() -> right \
> mstop() -> stop \

## lift system motor control
> m_up() -> up \
> m_down -> down \
