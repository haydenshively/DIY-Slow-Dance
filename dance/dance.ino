// the setup function runs once when you press reset or power the board
unsigned long lastNineToggle;
unsigned long lastTenToggle;
bool nine = false;
bool ten = false;
String number = "";

int lightOffTime = 26500;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  lastNineToggle = micros();
  lastTenToggle = micros();
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available() > 0) {
    int digit = Serial.read();
    if (isDigit(digit)) {
      number += (char)digit;
    }else if (digit == '.') {
      number += '.';
    }
    if (digit == '\n') {
      lightOffTime = 1000*number.toFloat();
      Serial.println(number);
      number = "";
    }
  }
  
  if (nine) {
    if (micros() - lastNineToggle > 800) {//1000, electromagnet on time
      digitalWrite(9, LOW);
      lastNineToggle = micros();
      nine ^= 1;//toggle boolean
    }
  }else {
    if (micros() - lastNineToggle > 30000) {//30000, electromagnet off time
      digitalWrite(9, HIGH);
      lastNineToggle = micros();
      nine ^= 1;//toggle boolean
    }
  }

  if (ten) {
    if (micros() - lastTenToggle > 5000) {//5000, light on time
      digitalWrite(10, LOW);
      lastTenToggle = micros();
      ten ^= 1;//toggle boolean
    }
  }else {
    if (micros() - lastTenToggle > lightOffTime) {//26500, light off time
      digitalWrite(10, HIGH);
      lastTenToggle = micros();
      ten ^= 1;//toggle boolean
    }
  }
}


