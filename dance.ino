// the setup function runs once when you press reset or power the board
unsigned long lastNineToggle;
unsigned long lastTenToggle;
bool nine = false;
bool ten = false;
String number = "";

int lightOffTime = 38;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  lastNineToggle = millis();
  lastTenToggle = millis();
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available() > 0) {
    int digit = Serial.read();
    if (isDigit(digit)) {
      number += (char)digit;
    }
    if (digit == '\n') {
      lightOffTime = number.toInt();
      Serial.println(lightOffTime);
      number = "";
    }
  }
  
  if (nine) {
    if (millis() - lastNineToggle > 1) {//1, electromagnet on time
      digitalWrite(9, LOW);
      lastNineToggle = millis();
      nine ^= 1;//toggle boolean
    }
  }else {
    if (millis() - lastNineToggle > 40) {//40, electromagnet off time
      digitalWrite(9, HIGH);
      lastNineToggle = millis();
      nine ^= 1;//toggle boolean
    }
  }

  if (ten) {
    if (millis() - lastTenToggle > 1) {//1, light on time
      digitalWrite(10, LOW);
      lastTenToggle = millis();
      ten ^= 1;//toggle boolean
    }
  }else {
    if (millis() - lastTenToggle > lightOffTime) {//38, light off time
      digitalWrite(10, HIGH);
      lastTenToggle = millis();
      ten ^= 1;//toggle boolean
    }
  }
}


