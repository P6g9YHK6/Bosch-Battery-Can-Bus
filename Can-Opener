#include <SPI.h>
#include <mcp2515.h>

// Define the CAN message structure for opening BMS
struct can_frame bmsMsg;
MCP2515 mcp2515(10); // MCP2515 instance on CS pin 10

void setup() {
  // Setup CAN message to open BMS (allow power draw from + and - terminals)
  bmsMsg.can_id  = 0x09A;  // CAN ID specific to opening BMS
  bmsMsg.can_dlc = 4;       // Data length: 4 bytes
  bmsMsg.data[0] = 0x04;    // Command to open BMS (allow power flow)
  bmsMsg.data[1] = 0x00;    // Additional data (not used, set to 0)
  bmsMsg.data[2] = 0x00;    // Additional data (not used, set to 0)
  bmsMsg.data[3] = 0x00;    // Additional data (not used, set to 0)

  // Initialize serial communication for debugging and status output
  Serial.begin(115200);
  while (!Serial);

  // Initialize MCP2515 CAN controller
  mcp2515.reset();                              // Reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);    // Set CAN bus speed to 500kbps for an 8MHz clock
  mcp2515.setNormalMode();                      // Set MCP2515 to normal operation mode
  
  Serial.println("BMS Controller Initialized. Ready to open battery circuit.");
}

void loop() {
  // Send CAN message to open BMS (allow current flow from battery)
  mcp2515.sendMessage(&bmsMsg);
  
  // Output status to serial monitor
  Serial.println("BMS command sent: Battery terminals are open for power draw");

  // Delay before sending the next message to keep BMS open
  delay(200);
}
