#define Rec 0

void setup() {
Serial.begin(9600);
}

void loop() {

Serial.println(analogRead(Rec));

}