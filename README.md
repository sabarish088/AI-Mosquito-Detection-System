# 🦟 Smart AI Mosquito Detection and Control System Using Acoustic Analysis

[![Platform](https://img.shields.io/badge/platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Language](https://img.shields.io/badge/firmware-C%2B%2B-00599C.svg)](https://www.arduino.cc/)
[![AI](https://img.shields.io/badge/AI-CNN%20%7C%20BiLSTM-orange.svg)]()
[![Status](https://img.shields.io/badge/status-Mini%20Project-success.svg)]()

An IoT + AI system that detects mosquitoes in real time from their wingbeat acoustic signature and automatically triggers an eco-friendly control mechanism — no chemicals, no manual monitoring.

> 🎓 Mini Project — B.Tech Information Technology, K.S.R. College of Engineering (Autonomous), Anna University, Chennai. May 2026.

---

## 📑 Table of Contents

- [Overview](#-overview)
- [How It Works](#-how-it-works)
- [System Architecture](#-system-architecture)
- [Tech Stack](#-tech-stack)
- [Hardware Components](#-hardware-components)
- [Hardware Wiring](#-hardware-wiring)
- [Repository Structure](#-repository-structure)
- [Getting Started](#-getting-started)
- [Build and CI](#-build-and-ci)
- [Applications](#-applications)
- [Limitations](#-limitations)
- [Future Enhancements](#-future-enhancements)
- [Authors](#-authors)
- [References](#-references)

---

## 🔍 Overview

Mosquito-borne diseases such as dengue, malaria, and chikungunya remain serious public health threats, especially in tropical regions. This project automates mosquito surveillance by analyzing the wingbeat frequency unique to each mosquito species.

**Key capabilities:**

| Capability | Description |
|---|---|
| 🎙️ Real-time acoustic sensing | Captures ambient sound continuously via I2S microphone |
| 📊 Signal processing | FFT + MFCC feature extraction from raw audio |
| 🧠 AI classification | CNN / BiLSTM models classify mosquito presence and species |
| ⚙️ Automated control | Servo-actuated eco-friendly repellent/trap mechanism |
| 📟 Live monitoring | Real-time status and detection results on LCD |

---

## ⚙️ How It Works

1. Capture — The INMP441 I2S microphone continuously samples ambient audio.
2. Preprocess — Noise filtering and normalization clean up the signal.
3. Feature Extraction — FFT converts the signal to the frequency domain; MFCC extracts key spectral features.
4. Peak Detection — The dominant frequency in the 300–600 Hz mosquito wingbeat range is identified.
5. Classification — The peak frequency is matched against known species bands.
6. Confirmation — A detection must be confirmed across multiple consecutive reads.
7. Control Activation — On confirmed detection, a servo-driven eco-friendly spray/trap mechanism is triggered.
8. Feedback — Detection results and system status are displayed live on the LCD and logged over Serial.

---

## 🏗️ System Architecture

```text
┌────────────────────┐     ┌──────────────────────┐     ┌───────────────────┐
│  Acoustic Sensing   │ --> │  Signal Processing    │ --> │   AI Processing    │
│  (INMP441 I2S Mic)  │     │  (Noise Filter, FFT,   │     │  (CNN / BiLSTM     │
│                     │     │   MFCC Extraction)     │     │   Classification)  │
└────────────────────┘     └──────────────────────┘     └─────────┬─────────┘
                                                                    │
                            ┌──────────────────────┐               ▼
                            │   User Interface      │     ┌───────────────────┐
                            │   (16x2 LCD + Serial)  │ <-- │  Decision Making   │
                            └──────────────────────┘     │  (Threshold Logic)  │
                                                          └─────────┬─────────┘
                                                                    │
                                                                    ▼
                                                          ┌───────────────────┐
                                                          │   Control System    │
                                                          │  (Servo-Actuated    │
                                                          │  Eco-Friendly Spray)│
                                                          └───────────────────┘
```

---

## 🧰 Tech Stack

**Firmware (this repo)**
- C++ (Arduino framework, ESP32)
- `arduinoFFT` — Fast Fourier Transform
- `ESP32Servo` — Servo control for the control mechanism
- `LiquidCrystal_I2C` — LCD status display
- I2S driver — digital audio capture from the INMP441

**AI / Model Training**
- Python
- TensorFlow / Scikit-learn — CNN & BiLSTM model training
- Librosa, NumPy — audio preprocessing and feature extraction

---

## 🔌 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Development Board | Main microcontroller — runs detection logic |
| INMP441 I2S Microphone | Captures mosquito wingbeat sound |
| Servo Motor | Actuates the eco-friendly spray/trap mechanism |
| 16x2 I2C LCD | Displays live detection status |
| LED Indicator | Visual alert on mosquito detection |
| Relay Module *(optional)* | Drives higher-power control devices |

## 🔧 Hardware Wiring

| ESP32 Pin | Connected To |
|---|---|
| GPIO 15 | INMP441 `WS` |
| GPIO 14 | INMP441 `SCK` |
| GPIO 32 | INMP441 `SD` |
| GPIO 18 | Servo signal |
| GPIO 25 | LED indicator |
| GPIO 21 / 22 | LCD `SDA` / `SCL` (I2C) |

---

## 📁 Repository Structure

```text
AI-Mosquito-Detection-System/
├── firmware/
│   └── firmware.ino          # ESP32 firmware entrypoint
├── .github/
│   └── workflows/
│       └── arduino-build.yml # CI compile workflow for ESP32
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support installed
- Libraries (install via Library Manager):
  - `arduinoFFT`
  - `ESP32Servo`
  - `LiquidCrystal_I2C`

### Build locally

```bash
# 1. Clone the repository
git clone https://github.com/sabarish088/AI-Mosquito-Detection-System.git
cd AI-Mosquito-Detection-System

# 2. Open firmware/firmware.ino in Arduino IDE
# 3. Select Board: ESP32 Dev Module
# 4. Select the correct COM Port
# 5. Upload the sketch and open Serial Monitor (115200 baud)
```

### Command-line compile check

```bash
arduino-cli core update-index --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli core install esp32:esp32 --additional-urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
arduino-cli lib install "arduinoFFT" "ESP32Servo" "LiquidCrystal_I2C"
arduino-cli compile --fqbn esp32:esp32:esp32 firmware/firmware.ino
```

---

## 🔁 Build and CI

This repository includes a GitHub Actions workflow at [.github/workflows/arduino-build.yml](.github/workflows/arduino-build.yml) that compiles the firmware on every push and pull request.

The workflow installs the ESP32 board package and required libraries, then runs:

```bash
arduino-cli compile --fqbn esp32:esp32:esp32 firmware/firmware.ino
```

---

## 🌍 Applications

- Residential homes & hostels — chemical-free mosquito control
- Hospitals & healthcare centers — hygiene-critical environments
- Agricultural fields — sustainable pest monitoring
- Smart city / IoT infrastructure — centralized large-scale monitoring
- Schools, colleges, and public spaces

---

## ⚠️ Limitations

- Detection accuracy depends on the quality/diversity of training data
- Sensitive to background noise (fans, speech, other insects)
- Limited detection range (proximity to microphone)
- Requires periodic calibration across environments

---

## 🔮 Future Enhancements

- Hybrid CNN-LSTM / transformer-based models for improved classification
- IoT/cloud integration for remote monitoring via mobile/web app
- Adaptive learning for varying environmental conditions
- Smart, density-based control intensity adjustment
- Energy-efficient hardware for continuous large-scale deployment

---

## 👥 Authors

| Name |
|---|---|
| Sabarish S |
| Sujitha S |
| Kanagapriya R |

---

## 📚 References

Full literature survey and reference list are available in the project report (to be added in the `docs/` folder for the final submission).

---

## 📄 License

This project is released for academic and educational purposes. Add a LICENSE file if you intend to open-source it formally.
