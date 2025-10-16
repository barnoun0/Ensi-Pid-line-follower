# ⚙️ PID Controller Explained

> **PID (Proportional–Integral–Derivative)** is a control algorithm that continuously calculates and adjusts its output to minimize the difference between a desired set point and the actual process value for stable and accurate control.

---

## 🧠 Before We Begin: Key PID Terms

### 🔸 Set Point
The **set point** is a user-entered target value.  
- For **cruise control**, it’s the desired vehicle speed.  
- For a **heating system**, it’s the desired temperature.  

### 🔸 Process Value
The **process value** is the current value being controlled.  
- In cruise control: the **actual vehicle speed**.  
- In a heating system: the **current temperature**.

### 🔸 Error
The **error** is the difference between the set point and the process value.  
It determines how the controller should react to bring the process closer to the target.

\[
\text{Error} = \text{Set Point} - \text{Process Value}
\]

---

## ⚙️ Let’s Get Dirty: The PID Components

### 🅿️ Proportional (P)
The **Proportional** term reacts immediately to the error value to reduce the gap between the process value and the set point.

**Formula:**
\[
P = K_p \times \text{Error}
\]

**Example:**
Kp = 20
Error = 100
P = 20 * 100 = 2000

This causes the robot to overshoot and turn too hard.  
The proportional part applies a large correction when far from the target but doesn’t know when to stop.

**Tuning:**
- 🔺 **Too High:** Causes **overshoot** (too aggressive correction)  
- 🔻 **Too Low:** Controller reacts **too slowly** and may become unstable

---

### 🧮 Integral (I)
The **Integral** term continuously accumulates the error over time until the set point is reached.  
It helps eliminate steady-state error by adjusting output based on past performance.

**Formula:**
\[
I = K_i \times \text{Integral of Error}
\]

It converts accumulated error into a usable correction that fine-tunes the system output.

---

### ⚡ Derivative (D)
The **Derivative** term predicts system behavior by measuring how quickly the error is changing — it acts as a **brake** to prevent overshooting.

**Formula:**
\[
D = \text{Current Error} - \text{Last Error}
\]

**Behavior:**
- 🔻 **Too Low:** Controller may react normally but lacks braking power  
- 🔺 **Too High:** Controller becomes unstable and overreacts to small distortions

---

## 🧩 Summary
- **P** → Reacts to current error (speed of correction)  
- **I** → Reacts to accumulated error (accuracy over time)  
- **D** → Reacts to change in error (stability and braking)

Together, they form a balanced control system capable of precise, stable, and smooth adjustments.

---

## 💡 Example Use Cases
- Cruise control systems  
- Heating/cooling systems  
- Robotics and motor control  
- Drones and flight controllers  

---

*Created by [@barnoun](https://github.com/barnoun) 🧠*
