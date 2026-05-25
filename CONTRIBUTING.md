# 🤝 Contributing to ArduinoDOS

Thank you for taking the time to contribute! We welcome all developers, system tinkerers, and computer science students to help optimize this micro-kernel engine. 🚀

---

## 🛠️ How Can I Contribute?

### 🐛 Reporting Bugs
* 🔍 Check the existing GitHub Issues tab to ensure the bug hasn't been reported yet.
* 📝 Open a new issue describing the exact command or wiring configuration that triggered the fault, along with your Serial Monitor or hardware logs.

### 💻 Submitting Code Modifications (Pull Requests)
1. **🍴 Fork** this repository to your personal GitHub profile.
2. **🌿 Create a separate branch** for your feature or optimization (e.g., `git checkout -b feature/optimized-buffers`).
3. **✅ Test your code** to make sure your changes compile clean on standard AVR compilers and standard hardware configurations.
4. **⚠️ Memory Optimization:** Keep memory safety in mind! **SRAM safety is critical** on the ATmega328P. Always pack raw text inside `F()` macros to prevent memory overflows.
5. **🚀 Push & Open:** Commit your changes with clear, descriptive English messages and open a Pull Request against our main branch.

---

## 📜 Code of Conduct
Please be respectful, helpful, and collaborative in all issues, pull requests, and communication channels. Let's keep the retro-hardware exploration and software development space educational, clean, and awesome for everyone! ✨
