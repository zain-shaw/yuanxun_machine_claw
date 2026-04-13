#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 25;      // 舵机接在 GPIO 5
const int buttonPin = 34;    // 按键接在 GPIO 34

int currentAngle = 0;        // 记录当前舵机的角度
bool buttonState;            // 当前按键状态
bool lastButtonState = HIGH;// 上一次的按键状态（默认高电平，未按下）
unsigned long lastDebounceTime = 0; // 消抖计时器
unsigned long debounceDelay = 50;   // 消抖延时 50ms

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);           // 绑定舵机
  pinMode(buttonPin, INPUT_PULLUP);   // 设置按键引脚为输入上拉模式
}

void loop() {
  int reading = digitalRead(buttonPin); // 读取按键值

  // --- 按键消抖逻辑 ---
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 如果状态稳定了 debounceDelay 毫秒以上
    if (reading != buttonState) {
      buttonState = reading;

      // 只有在按键按下（从高变低）的瞬间执行动作
      if (buttonState == LOW) {
        // 切换舵机角度
        if (currentAngle == 0) {
          currentAngle = 120;
        } else {
          currentAngle = 0;
        }
        myServo.write(currentAngle);
        Serial.print("舵机角度切换至: ");
        Serial.println(currentAngle);
      }
    }
  }

  lastButtonState = reading; // 更新上一次状态
}