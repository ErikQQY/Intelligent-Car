#include<Servo.h>
#define kp 0.05
#define ki 0.1
#define kd 0.1

#define adpinright A0
#define adpinleft A1

float result = 0;

int PWMLEFT = 0.0;
int PWMRIGHT = 0.0;

#define pwm 0.0
Servo motor;
Servo myservo;

int pos=50;

struct PID{
  float err0;
  float err1;
  float err2;
  float P;
  float I;
  float D;
  float delt;
};

PID pid = {0.0, 0.0, 0.0, 0.0, kp, ki, kd};

float updatepwm(int vleft, int vright)
{
  pid.err2 = pid.err1;
  pid.err1 = pid.err0;
  pid.err0 = vleft - vright;
  pid.delt = pid.P*(pid.err0-pid.err1+pid.I*pid.err0+pid.D*(pid.err0-2*pid.err1+pid.err2));
  PWMLEFT = PWMLEFT-pid.delt;
  PWMRIGHT = PWMRIGHT+pid.delt;

  return pwm+pid.err0;
}


void setup() {
  // 调节频率Atmel
  //TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000011;    // set timer 0 divisor to    64 for PWM frequency of   976.56 Hz (The DEFAULT)
  //TCCR0B = TCCR0B & B11111000 | B00000100;    // set timer 0 divisor to   256 for PWM frequency of   244.14 Hz
  //TCCR0B = TCCR0B & B11111000 | B00000101;    // set timer 0 divisor to  1024 for PWM frequency of    61.04 Hz
  motor.attach(6);
  myservo.attach(3);

  Serial.begin(115200);              //设置波特率

  TCCR0B = TCCR0B & B11111000 | B00000010;
  int servo_pwm = 0.0;
}

void loop() {
  // put your main code here, to run repeatedly:
//    motor.write(pos);
//      delay(15);
      //int vleft=analogRead(adpinleft);
      //int vright=analogRead(adpinright);
      //Serial.println(vleft);
      //Serial.println(vright);
      //舵机输出
      for(int i=0;i<10;i++)
      {
        int vright=analogRead(adpinright);
        result+=vright;
      }
      result = result/12;
      analogWrite(6, 35);
      //myservo.write(1.2*(60-result));
      analogWrite(3, 100);
      result=0;
      delay(10);
}
