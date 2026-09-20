# Gamma Toggle

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows-blue)]()
[![Language](https://img.shields.io/badge/Language-C-orange)]()

A lightweight, lightning-fast Windows command-line utility written in pure C to instantly toggle monitor gamma (brightness/contrast). It is specifically designed for gamers who need to brighten up dark scenes on the fly without altering in-game settings or physical monitor controls.

## 🚀 Features

- **Instant Toggle:** Switches between a bright gamma curve (0.45) and the default system gamma (1.0) instantly.
- **Multi-Monitor Support:** Precisely targets specific displays by their system index.
- **Smart State Detection:** Automatically detects the current gamma state and toggles it to the opposite state when run without arguments.
- **Zero Dependencies:** Built entirely with native Windows API (WinAPI). No .NET, Java, or external runtime libraries required.
- **Tiny Footprint:** The compiled executable is under 50 KB.

## 📦 Usage

Download the latest compiled version from the [Releases](../../releases) page.

### Command Line Arguments

Open your terminal (Command Prompt or PowerShell) and use the following syntax:

```bash
# Toggle gamma on the primary monitor (default behavior)
gamma-toggle.exe

# Force ENABLE bright gamma on Monitor #1
gamma-toggle.exe 1

# Force DISABLE (reset) gamma on Monitor #2
gamma-toggle.exe 2 2

# List all available active monitors and their system names
gamma-toggle.exe list
```

> 💡 Pro Tip: Always run gamma-toggle.exe list first if you have multiple monitors, to ensure you are targeting the correct display index.

## 🛠️ Building from Source

To build this project, you need a MinGW-w64 compiler toolchain (e.g., [w64devkit](https://github.com/skeeto/w64devkit) or MSYS2).

1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/gamma-toggle.git
   cd gamma-toggle
   ```

2. Compile the project using the provided Makefile:
   ```bash
   make
   ```

3. The final executable `gamma-toggle.exe` will be generated in the root directory.

To clean up build artifacts (object files and the executable), run:
```bash
make clean
```

##  Project Structure

```text
gamma-toggle/
├── include/       # Header files (gamma.h)
├── src/           # Source code (main.c, gamma.c)
├── res/           # Application resources (icon.ico, app.rc)
├── Makefile       # Automated build script
├── .gitignore     # Git ignore rules
└── README.md      # Project documentation
```

## 📜 License

This project is open-source and available under the [MIT License](LICENSE).

---
*Built with ❤️ using pure C and WinAPI.*
