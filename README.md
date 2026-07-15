# 🐦 Advanced Chidi Udi (Fly / Not Fly) Multiplayer Tournament Simulation

A multithreaded C++ simulation of the traditional **Chidi Udi (Fly / Not Fly)** game using POSIX Threads (Pthreads), Mutexes, and Semaphores.

---

## 📖 Project Overview

This project simulates the traditional **Chidi Udi (Fly / Not Fly)** game as a multiplayer tournament. An announcer randomly announces the name of a bird or a non-bird, while multiple player threads respond simultaneously. A referee thread evaluates each response, eliminates players who answer incorrectly, and declares the final winner.

This project demonstrates the practical use of multithreading, synchronization, mutexes, and semaphores in C++.

---

## ✨ Features

- 🧵 Multithreaded gameplay using POSIX Threads (Pthreads)
- 👥 5 Concurrent Player Threads
- 📢 Dedicated Announcer Thread
- ⚖️ Referee Thread for Evaluation
- 🎲 Random Bird / Non-Bird Announcements
- ❌ Automatic Player Elimination
- 🏆 Winner Detection
- 📊 Survival Statistics
- 🔒 Thread Synchronization using Mutexes and Semaphores

---

## 🛠 Technologies Used

- C++
- POSIX Threads (pthread)
- Mutex
- Semaphores
- Object-Oriented Programming Concepts

---

## 📂 Project Structure

```
Advanced-Chidi-Udi/
│
├── main.cpp
└── README.md
```

---

## ▶️ How to Compile

```bash
g++ main.cpp -o game -pthread
```

---

## ▶️ How to Run

```bash
./game
```

---

## 💻 Sample Output

```text
===== Round 1 =====
Announcement: Eagle
Player 1 -> Fly
Player 2 -> Fly
Player 3 -> Not Fly
Player 4 -> Fly
Player 5 -> Fly

Referee Result:
Player 3 Eliminated
Active Players: 4

===== Round 2 =====
Announcement: Dog
Player 1 -> Not Fly
Player 2 -> Not Fly
Player 4 -> Fly
Player 5 -> Not Fly

Referee Result:
Player 4 Eliminated
Active Players: 3

===== Final Result =====
Winner: Player 2

Survival Statistics:
Player 1 survived 4 rounds (Eliminated)
Player 2 survived 5 rounds (Active)
Player 3 survived 1 rounds (Eliminated)
Player 4 survived 2 rounds (Eliminated)
Player 5 survived 4 rounds (Eliminated)
```

---

## 🎯 Learning Outcomes

This project helped in understanding:

- Multithreading in C++
- POSIX Threads (Pthreads)
- Mutex Synchronization
- Semaphores
- Thread Coordination
- Concurrent Programming
- Operating System Synchronization Concepts

---

## 👨‍💻 Author

**Muhammad Sharjeel Abbasi**

Software Engineering Student | C++ Developer | Learning Operating Systems & Concurrent Programming

---

⭐ If you found this project useful, consider giving it a **Star** on GitHub.
