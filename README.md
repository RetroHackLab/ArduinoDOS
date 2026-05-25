# 💻 ArduinoDOS v1.5.0

An educational, lightweight micro-operating system engine written in C++ for the Arduino Uno (ATmega328P). It emulates a 32-bit execution environment and provides a multi-mode command-line interface (CLI) to interact directly with hardware registers and persistent EEPROM storage. 🚀

## 🌟 Features
* **⚙️ Multi-Mode Engine:** Toggle between `MODE_CONSOLE` (standard user space), `MODE_SETUP` (system configuration), and Root Access.
* **💾 Persistent Storage:** Native integration with hardware EEPROM to save localization and environment variables.
* **🧠 Optimized Memory Footprint:** String literals are strictly mapped to Flash Memory using the `F()` macro to preserve the ATmega328P's limited 2KB SRAM.
* **🎨 ANSI Color Support:** Built-in support for terminal escape sequences (Green/White themes).

---

## 🛠️ Project Structure
To ensure proper compilation without toolchain conflicts, organize your project workspace as follows:

```text
📁 ArduinoDOS/
├── 📄 System.ino         # 🧠 Main core execution script
├── 📄 System.h           # ⚙️ Global OS state headers and enums
├── 📄 EEPROM.h           # 💾 High-level Arduino EEPROM class mapping
├── 📄 stdint.h           # 🔢 Exact-width integer definitions (32-bit engine)
├── 📄 System.json        # 📋 Project metadata and configuration manifest
└── 📁 avr/
    ├── 📄 .io            # 🌐 Deployment anchor file
    ├── 📄 eeprom.h       # ⚡ Low-level builtin hardware macros
    └── 📄 stddef.h       # 📏 Standard size types and definitions
