# UCommandExecutor

[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/UDFSmart/UCommandExecutor/releases/tag/v1.0.0)

A lightweight, memory-efficient command executor for **Arduino**, **ESP8266**, and **ESP32**. 

It allows you to map string-based commands (like "LED_ON", "GET_TEMP") to specific C++ functions using a simple callback system. Perfect for building Serial consoles, MQTT control interfaces, or WebSocket-based IoT devices.

## Features
- **Low Memory Footprint**: Uses standard C-strings (`const char*`) and function pointers. No heavy `std::string` or `String` objects.
- **Case-Insensitive**: Commands are matched regardless of case (e.g., `Help` == `HELP`).
- **Decoupled Architecture**: Easily switch between Serial, MQTT, or HTTP by providing different result callbacks.
- **Cross-Platform**: Works on AVR (Uno, Nano, Mega) and 32-bit controllers (ESP32, ESP8266).

## Installation

### How to include in your project

### Option 1: Using Arduino IDE (GUI)
  1. Download: Click the green Code button on GitHub and select Download ZIP.
  2. Install:
    * Open Arduino IDE.
    * Go to Sketch -> Include Library (Скетч -> Подключить библиотеку).
    * Select Add .ZIP Library... (Добавить .ZIP библиотеку...).
    * Choose the downloaded .zip file.
    
  3. Verify: Now you can find the library under Sketch -> Include Library -> Contributed libraries.
  
### Option 2: PlatformIO (Advanced)

If you are using PlatformIO, add the library to your platformio.ini:
```Ini
lib_deps = 
    https://github.com/javavirys/UCommandExecutor.git
```

### Using Git
```bash
cd ~/Documents/Arduino/libraries
git clone [https://github.com/javavirys/UCommandExecutor.git](https://github.com/javavirys/UCommandExecutor.git)
```

## Quick Start
```cpp
#include <UCommandExecutor.h>

// 1. Define command functions
void cmdHello(const char* param, CommandResultCallback callback) {
    if (callback) callback("HELLO", param, "Success: World!");
}

// 2. Map commands to functions
const UCommand myCommands[] = {
    {"HELLO", cmdHello}
};

// 3. Initialize the executor
UCommandExecutor executor(myCommands, sizeof(myCommands) / sizeof(myCommands[0]));

// 4. Result handler
void onResult(const char* cmd, const char* param, const char* status) {
    Serial.printf("[%s] Result: %s\n", cmd, status);
}

void setup() {
    Serial.begin(115200);
    // Execute a command
    executor.execute("HELLO", "optional_data", onResult);
}

void loop() {}
```

## API Reference
UCommand Structure

  * const char* name: The string trigger for the command.
  * CommandFunction function: Pointer to the function to execute.

UCommandExecutor Methods

  * UCommandExecutor(commands, count): Constructor.

  * execute(cmd, param, callback): Searches for cmd in the table and runs the associated function.
  
### `execute` Method
  `void execute(const char* cmd, const char* param, CommandResultCallback callback)`
  - **cmd**: The command name to look for (case-insensitive).
  - **param**: A string parameter passed to the command function (can be a value, JSON, etc.).
  - **callback**: The function that handles the execution result (use `nullptr` if no response is needed).

## Example: Creating a new release

```bash
# Push changes to main
git add .
git commit -m "Commit message"
git push origin main

# Tag a new release
git tag vX.X.X
git push origin vX.X.X
```

## License

Copyright 2026 javavirys.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0


## Author
Developed by javavirys (UDFSOFT).


