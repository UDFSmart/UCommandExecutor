/*
 *    Copyright 2026 UDFOwner
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    More details: https://udfsoft.com/
 */

#include <Arduino.h>
#include "UCommandExecutor.h"

// 1. Define functions that will execute the commands
void cmdPrintHelloWorld(const char* param, CommandResultCallback callback) {
  Serial.println("--- Executing: Hello World ---");

  if (param && strlen(param) > 0) {
    Serial.print("Command parameter: ");
    Serial.println(param);
  }

  // Send the response back via callback
  if (callback) {
    callback("PRINT_HELLO", param, "Success");
  }
}

void cmdBlink(const char* param, CommandResultCallback callback) {
  int times = param ? atoi(param) : 1;

  // 1. Create a buffer to hold the formatted string
  char buffer[50];

  // 2. Format the string into the buffer
  snprintf(buffer, sizeof(buffer), "Blinking LED %d time(s)", times);

  // 3. Print the buffer
  Serial.println(buffer);

  if (callback) {
    callback("BLINK", param, "Done");
  }
}

// 2. Create the command table
const UCommand myCommands[] = {
  { "HELLO", cmdPrintHelloWorld },
  { "BLINK", cmdBlink }
};

// Calculate the number of commands automatically
const size_t commandsCount = sizeof(myCommands) / sizeof(myCommands[0]);

// 3. Initialize the executor
UCommandExecutor commandExecutor(myCommands, commandsCount);

// 4. Our callback for outputting results (e.g., to Serial)
void loggerCallback(const char* cmd, const char* param, const char* status) {
  Serial.print("[System] Command: ");
  Serial.print(cmd);
  Serial.print(" | Status: ");
  Serial.println(status);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("System ready.\n");

  // Example 1: Calling a command with a string parameter
  // If CMD_PRINT_HELLO_WORLD is a macro or a constant:
  const char* CMD_PRINT_HELLO_WORLD = "HELLO";
  commandExecutor.execute(CMD_PRINT_HELLO_WORLD, "some_data", loggerCallback);

  Serial.println("---");

  // Example 2: Calling with a number (passed as a string)
  commandExecutor.execute("BLINK", "3", loggerCallback);

  Serial.println("---");

  // Example 3: Error handling (unknown command)
  commandExecutor.execute("UNKNOWN", "", loggerCallback);
}

void loop() {
  // Nothing to do here
}