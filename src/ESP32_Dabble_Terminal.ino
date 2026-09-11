#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>

void setup() {
  // Disable TX timeout to prevent native USB CDC blocking
  Serial.setTxTimeoutMs(0); 
  Serial.begin(115200); 

  // Initialize Dabble BLE
  Dabble.begin("ESP32_Dabble"); 
  
  // Printed right after the bootloader finishes
  Serial.println("\n-------------------------------------------");
  Serial.println("ESP32-S3 Ready! Connect using Dabble App.");
  Serial.println("-------------------------------------------");
}

void loop() {
  Dabble.processInput();  

  if (Terminal.available()) {
    String message = "";
    
    while (Terminal.available()) {
      message += Terminal.readString();
    }

    // 1. Output to Arduino Serial Monitor
    Serial.print("Received from phone: ");
    Serial.println(message);

    // 2. Output back to phone screen
    Terminal.print("ESP32: ");
    Terminal.println(message);
  }

  delay(100);  
}
