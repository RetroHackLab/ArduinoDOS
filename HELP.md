# ❓ HELP & Troubleshooting Guide — ArduinoDOS

Welcome to the official operation and maintenance center for **ArduinoDOS**. This guide covers the command-line interface, system navigation, and critical troubleshooting procedures. 🛠️

---

## 🖥️ Command-Line Interface (CLI) & Console Modes

The system operates based on a **State Machine** architecture. Your interaction varies depending on the active `OperatingMode`.

### 1. Navigation & Modes
* **`arduino@uno$` (Console Mode):** The default operational environment for general file management and system maintenance.
* **`arduino@uno(SETUP)#` (Setup Mode):** Access this by typing `cd SETUP`. This mode is dedicated to configuring system variables like `LG` (Language) and `COUNTRY`.
* **`base_use$` (User Mode):** A restricted environment for standard file operations (`copie`, `deplace`). Enter via `cd ~/user` or by exiting Console mode.

### 2. Essential CLI Commands
| Command | Mode | Description |
| :--- | :--- | :--- |
| `cd SETUP` | Console | Enters the Configuration/System mode. |
| `su -C` | Shared | Requests SuperUser elevation. Requires `adminPassword`. |
| `touch [file]` | Shared | Opens the editor buffer to write into `[file]`. |
| `#end#` | Editor | Saves the current editor buffer and exits write mode. |
| `set [path] [perm]` | Shared | Sets permission profiles (e.g., `root/mine`, `main/tree`). |
| `@reset & unmount` | Console | Performs a deep factory wipe of the physical EEPROM. |
| `DEVICE.mvbx` | Setup | Returns the firmware and hardware metadata. |

---

## 🛠️ Required System Scripts & Architecture
To ensure the OS is fully functional, confirm the following core components are present:

* **🧠 `System.ino`:** The brain of the operation. It processes all serial inputs and triggers the `executeCommand()` function.
* **⚡ `avr/eeprom.h`:** Uses `__builtin_avr` macros for direct hardware memory manipulation.
* **📏 `avr/stddef.h`:** Essential for memory pointer safety (`NULL`) and type definitions (`size_t`).
* **📋 `System.json`:** The metadata manifest that the system reads during the boot sequence.

---

## 🔧 Troubleshooting & Bug Fixes

If you encounter issues, consult this checklist before opening an Issue on GitHub.

### 🛑 Memory Overflows (System Freezes)
**Symptom:** The system stops responding or reboots unexpectedly during execution.
**Cause:** SRAM exhaustion on the ATmega328P. 
**Fix:** Ensure that every string literal is wrapped in the `F()` macro (e.g., `Serial.println(F("Hello World"));`). This forces the text into Flash memory rather than occupying precious volatile RAM.

### 🔑 Authentication Failures
**Symptom:** `su -C` always returns "Incorrect Password" despite entering `retrohack`.
**Cause:** Residual `\r` (Carriage Return) characters from the serial monitor.
**Fix:** The code uses `pass.trim()` to clean input. Ensure your Serial Monitor settings are set to **"Both NL & CR"** to match the system's expected input buffer.

### 📺 Hardware Output Issues (VGA/TV)
**Symptom:** Display shows static, or the screen remains dark.
**Cause:** Improper synchronization timing or incorrect pin resistance.
**Fix:** Double-check your hardware connections:

Ensure you are using the correct resistors ($470\ \Omega$ for video, $680\ \Omega$ for sync) to maintain the required analog signal levels.

### ⌨️ Keyboard Unresponsiveness
**Symptom:** The system does not register key presses from the PS/2 keyboard.
**Cause:** The keyboard clock wire is not on an interrupt pin.
**Fix:** The `PS2Keyboard` library requires Pin 3 (on the Uno) to process incoming pulses via `INT1`. Verify that your CLK wire is physically moved to **Pin 3**.

---

## 💀 Emergency Recovery
If the system becomes completely locked due to corrupted EEPROM data:
1. Access the console via Serial/Keyboard.
2. Elevate to root: `su -C`.
3. Execute the wipe command: `@reset & unmount`.
4. The system will purge all memory blocks and perform a hard reboot. 🚀
