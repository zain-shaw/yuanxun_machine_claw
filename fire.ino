// --- 电机控制引脚 (沿用之前的配置) ---
#define MOTOR_IN1 14
#define MOTOR_IN2 15

// --- 火焰传感器引脚 ---
#define FLAME_DIGITAL_PIN 18 // D0 -> GPIO 18 (用于触发报警/灭火)
#define FLAME_ANALOG_PIN 36  // A0 -> GPIO 36 (用于读取火焰强度，可选)

void setup() {
  // 1. 初始化串口通信 (用于调试查看状态)
  Serial.begin(115200);
  Serial.println("🔥 火焰探测机器人 2.0 启动...");

  // 2. 初始化电机引脚
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  
  // 初始状态：电机停止
  stopMotor();

  // 3. 初始化火焰传感器引脚
  pinMode(FLAME_DIGITAL_PIN, INPUT);
  // 注意：GPIO 36 是纯输入引脚，不需要设置 pinMode，直接读取即可
}

void loop() {
  // 读取数字引脚状态
  // 注意：大多数模块检测到火焰输出 LOW (0)，无火焰输出 HIGH (1)
  int flameState = digitalRead(FLAME_DIGITAL_PIN);

  if (flameState == LOW) { 
    // --- 检测到火焰！启动电机 ---
    Serial.println("🔥 发现火焰！启动电机！");
    runMotorForward();
  } else {
    // --- 无火焰，停止电机 ---
    Serial.println("✅ 安全，电机停止");
    stopMotor();
  }

  // --- 可选：读取模拟值用于调试 ---
  // 如果你想看火焰有多强，可以取消下面注释
  // int analogValue = analogRead(FLAME_ANALOG_PIN);
  // Serial.print("火焰强度模拟值: ");
  // Serial.println(analogValue);

  delay(100); // 稍微延时，防止串口刷屏太快
}

// --- 电机控制函数 ---

void runMotorForward() {
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
}

void runMotorBackward() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, HIGH);
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
}