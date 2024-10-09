#include <CAN.h>

void setup() {
  // Initialize serial communication for debugging and status output
  Serial.begin(115200); // Set baud rate
  delay(100); // Allow time for the serial buffer to clear
  Serial.println("Setup started.");

  // Start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!"); // Print error to Serial Monitor
    while (true); // Halt execution if CAN bus fails to initialize
  }

  Serial.println("CAN bus started successfully.");
}

void loop() {
  // Attempt to send a CAN message to open BMS (allow current flow from battery)
  if (CAN.beginPacket(0x09A) && 
      CAN.write(0x04) && 
      CAN.write(0x00) && 
      CAN.write(0x00) && 
      CAN.write(0x00) && 
      CAN.endPacket()) {
    
    Serial.println("CAN message sent successfully.");
    okBlink();  // Blink LED to indicate successful message sent
    Serial.println("BMS command sent: Battery terminals are open for power draw");
  } else {
    Serial.println("Error sending CAN message!"); // Print error to Serial Monitor
    // No blinking indication for errors
  }

  // Delay before sending the next message to keep BMS open
  delay(200);
}

// Function to blink LED normally to indicate success
void okBlink() {
  digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on
  delay(100);                       // Wait for 100ms
  digitalWrite(LED_BUILTIN, LOW);   // Turn LED off
}
