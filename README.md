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

🔗 **[Watch on LinkedIn](https://www.linkedin.com/posts/amirhossein-shirvani-dastgerdi-358136219_embeddedsystems-microcontroller-arm-activity-7303092515753058304-_oI_?utm_source=share&utm_medium=member_desktop&rcm=ACoAADcDuXQB4CVCm_GvXTnpu6nZF7eTd2DXMj4)**  

### 🎥 **YouTube Video**  
Click below to watch the demo on **YouTube**:  

[Watch the video](https://youtu.be/p9cDnvQmLTc?si=FjwSWftgKeCkODOn)  


