# 🚀 Maze Solver System on LPC1768 (LandTiger Board)

This is a **real-time maze solver system** developed for the **LPC1768 microcontroller**, implemented in **C and ARM Assembly**. The project was inspired by the **Computer Architecture Master's Course at Politecnico di Torino** and was developed under the guidance of **Prof. Renato Ferrero**.

## 🔹 Project Overview  
This system allows real-time **maze generation and solving** on the **LandTiger LPC1768 board**, featuring **dynamic maze resizing, random maze generation, shortest path solving, and button debouncing using the Repetitive Interrupt Timer (RIT).**  

### 🎮 **How It Works**  
- **Use Joystick** → Dynamically adjust the maze size.  
- **Press `KEY1`** → Generates a random maze using **Timer0 (LPC_TIM0->TC)** as a seed for randomness.  
- **Press `KEY2`** → Runs the **maze solver algorithm** to find the shortest path. If a solution exists, it displays the number of iterations required.  
- **Press `INT0` (3rd key from the left)** → Toggles **uppercase/lowercase** directional indicators.  

### 🧭 **Maze Legend (Directional Indicators)**  
| Symbol | Meaning |  
|---------|-------------------|  
| **N** / **n** | Move **North** |  
| **S** / **s** | Move **South** |  
| **E** / **e** | Move **East** |  
| **W** / **w** | Move **West** |  

*Lowercase letters indicate normal directions, uppercase letters are toggled using INT0.*  

---

## 🛠 **Technologies Used**  
- **Languages**: C, ARM Assembly  
- **Microcontroller**: LPC1768 (ARM Cortex-M3)  
- **LCD Display**: ILI9325  
- **Development Tools**: Keil uVision  
- **Timer & Interrupts**:  
  - **Timer0** → Generates random seed for maze creation  
  - **RIT (Repetitive Interrupt Timer)** → Handles button debouncing  

---

## 📌 **Demo Videos**  
### 🎥 **LinkedIn Video**  
Watch the project demo on **LinkedIn**:  

🔗 **[Watch on LinkedIn](YOUR_LINKEDIN_VIDEO_URL)**  

### 🎥 **YouTube Video**  
Click below to watch the demo on **YouTube**:  

[Watch the video](https://www.youtube.com/watch?v=YOUR_YOUTUBE_VIDEO_ID)  

---

## 🚀 **Getting Started**  
### 🔹 **1. Clone the Repository**  
```sh
git clone https://github.com/Mrquestioner/Maze-Solver-LPC1768.git
cd Maze-Solver-LPC1768
