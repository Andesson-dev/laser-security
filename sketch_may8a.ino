#define LASER 2    // Define pin 2 for the laser module
#define BUZZER 12  // Define pin 12 for the buzzer
#define LDR A1     // Define analog pin A1 for the LDR (light sensor)

unsigned long buzzerStartTime = 0; // Variable to store the time when the buzzer starts
bool buzzerActive = false;         // Flag to track whether the buzzer is currently active

void setup() {
  Serial.begin(9600);              // Initialize serial communication at 9600 baud

  pinMode(LASER, OUTPUT);          // Set laser pin as output
  pinMode(BUZZER, OUTPUT);         // Set buzzer pin as output
  pinMode(LDR, INPUT);             // Set LDR pin as input

  delay(500);                      // Short delay to stabilize the system
  digitalWrite(LASER, HIGH);       // Turn on the laser by setting the pin HIGH
}

void loop() {
  int ldr = analogRead(LDR);       // Read the analog value from the LDR sensor
  Serial.println("Light sensor: " + String(ldr)); // Print the LDR value to the serial monitor

  unsigned long currentTime = millis(); // Get the current time in milliseconds since program start

  // If the LDR detects strong light (value > 900) and the buzzer is not already active
  if (ldr > 900 && !buzzerActive) {
    tone(BUZZER, 100);             // Turn on the buzzer with a tone of 100 Hz
    buzzerStartTime = currentTime; // Store the time the buzzer started
    buzzerActive = true;           // Mark the buzzer as active
    Serial.println("Buzzer activé pour 1 minute."); // Print activation message
  }

  // If the buzzer has been active for more than 60,000 milliseconds (1 minute)
  if (buzzerActive && currentTime - buzzerStartTime >= 60000) {
    noTone(BUZZER);                // Stop the buzzer
    buzzerActive = false;          // Reset the buzzer active flag
    Serial.println("Buzzer désactivé."); // Print deactivation message
  }

  delay(100);                      // Wait 100 milliseconds before the next loop cycle
}
