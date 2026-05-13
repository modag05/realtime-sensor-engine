# 🏭 Industrial Edge Simulator

> A real-time, event-driven sensor simulation system built in modern C++17 — designed from the ground up with industrial systems thinking.

---

## 📌 What Is This?

This project simulates the data pipeline found in real industrial edge devices — from raw sensor readings, through JSON encoding, into a thread-safe event queue, and finally through a control decision engine.

It is not a toy example. Every design decision reflects how production systems in PLC, automotive, and IoT environments are actually built.

```
Sensor → JSON → Parser → Event → Queue → Controller → Action
```

---

## 🎯 What You Will Learn

This project is built **bottom-up** — starting from real data, then building the architecture around it. This is how professional engineers approach unknown systems.

### C++17 Skills

| Concept | Where You See It |
|---------|-----------------|
| `std::ostringstream` | Building JSON strings cleanly |
| `std::string::find` + `substr` | Parsing structured text |
| `std::stoi` / `std::stof` | Converting string to numeric types |
| `std::optional` | Handling parse failures without exceptions |
| `std::function` | Storing and passing callbacks |
| Lambda functions | Inline behavior without named functions |
| `std::thread` | Running producer and consumer in parallel |
| `std::mutex` + `lock_guard` | Protecting shared data |
| `std::condition_variable` + `unique_lock` | Efficient thread coordination |
| `std::atomic<bool>` | Thread-safe shutdown flag |
| `std::mt19937` + distributions | Professional random number generation |
| Initializer lists | Clean and efficient object construction |
| `enum class` | Type-safe state representation |
| `struct` composition | Lightweight data modeling |

### Systems Engineering Skills

- **Bottom-Up Design** — start from data, build architecture around it
- **Producer-Consumer Pattern** — decouple data generation from processing
- **Event-Driven Architecture** — react to events instead of polling
- **Thread Safety** — understand race conditions and prevent them
- **Clean Shutdown** — stop multi-threaded systems without crashes
- **Separation of Concerns** — every class has one job
- **Industrial Data Flow** — how sensors talk to controllers in real systems

---

## 🏗️ Architecture

```
┌──────────────────────────────────────────────────────────────┐
│                      SYSTEM PIPELINE                         │
│                                                              │
│  ┌───────────────┐     ┌───────────────┐                    │
│  │ JsonGenerator │────▶│  JsonParser   │                    │
│  │               │     │               │                    │
│  │ ch0: temp     │     │ JSON string   │                    │
│  │ ch1: pressure │     │      ↓        │                    │
│  │ ch2: proximity│     │   Event{}     │                    │
│  └───────────────┘     └──────┬────────┘                    │
│     (Thread 1)                │                             │
│                               ▼                             │
│                      ┌────────────────┐                     │
│                      │   EventQueue   │                     │
│                      │  [E][E][E]...  │                     │
│                      │ (Thread-Safe)  │                     │
│                      └───────┬────────┘                     │
│                              │          (Thread 2)          │
│                              ▼                              │
│                      ┌────────────────┐                     │
│                      │   Controller   │                     │
│                      │  ch0 → temp    │                     │
│                      │  ch1 → press   │                     │
│                      │  ch2 → prox    │                     │
│                      └───────┬────────┘                     │
│                              │                              │
│                              ▼                              │
│                      ┌────────────────┐                     │
│                      │     Action     │                     │
│                      │  OK / WARNING  │                     │
│                      │  ALERT / STOP  │                     │
│                      │  EMERGENCY     │                     │
│                      └────────────────┘                     │
└──────────────────────────────────────────────────────────────┘
```

---

## 📁 Project Structure

```
industrial-edge-simulator/
├── Event.h              ← Core data unit (channelNr + value)
├── JsonGenerator.h      ← Simulates sensor hardware output
├── JsonParser.h         ← Parses raw JSON into Events
├── EventQueue.h         ← Thread-safe FIFO event buffer
├── Controller.h         ← Decision logic per channel
├── Engine.h             ← Orchestrates all components
└── main.cpp             ← Entry point
```

---

## 🚀 Sensor Channels

| Channel | Sensor | Range | Type |
|---------|--------|-------|------|
| 0 | 🌡️ Temperature | 20–100 °C | `float` |
| 1 | 📊 Pressure | 1–20 bar | `float` |
| 2 | 📡 Proximity | Detected / Clear | `float` (1.0 / 0.0) |

---

## ⚡ Control Logic

| Condition | Action |
|-----------|--------|
| Temperature > 80 °C | 🚨 EMERGENCY STOP |
| Temperature > 60 °C | 🟡 WARNING |
| Pressure > 15 bar | 🟠 ALERT |
| Proximity detected | 🔴 STOP |
| All normal | 🟢 OK |

---

## 📊 Sample Output

```
CH0 | 87.3 | EMERGENCY STOP 🚨 | Temperature critical!
CH1 | 17.1 | ALERT          🟠 | Pressure too high!
CH2 | 0.0  | OK             🟢 | No object detected.
CH0 | 45.2 | OK             🟢 | Temperature normal.
CH1 | 9.3  | OK             🟢 | Pressure normal.
CH2 | 1.0  | STOP           🔴 | Object detected!
```

---

## 🛠️ Build & Run

**Requirements:** C++17 compiler, POSIX threads

```bash
# Clone
git clone https://github.com/your-username/industrial-edge-simulator
cd industrial-edge-simulator

# Build
g++ -std=c++17 -pthread main.cpp -o sim

# Run
./sim
```

---

## 🔗 Real-World Mapping

Every component in this project maps directly to real industrial systems:

| This Project | Real Industrial Equivalent |
|--------------|---------------------------|
| `JsonGenerator` | Physical sensor hardware output |
| `JsonParser` | Edge device message decoder |
| `EventQueue` | OPC UA notification buffer / MQTT queue |
| `Controller` | Structured Text logic in TwinCAT / Siemens S7 |
| `Engine` | PLC cyclic runtime task |
| `Action` | Output signals to motors, valves, relays |

---

## 🧠 Why Bottom-Up?

Most tutorials hand you the architecture first, then fill it in.

This project does the opposite — it starts by asking: **what does the data actually look like?**

```
Step 1 — Run the sensor, see the raw output
Step 2 — Shape the Event around the real data
Step 3 — Build the Queue the Event needs
Step 4 — Build the Controller the Queue feeds
Step 5 — Build the Engine that runs it all
```

This is how engineers work on real systems where requirements are discovered, not handed to you.

---

## 📚 Build Order

```
1. JsonGenerator   → fake sensor JSON every 10 seconds
       ↓
2. JsonParser      → JSON string to Event struct
       ↓
3. EventQueue      → thread-safe storage between threads
       ↓
4. Controller      → decision logic per channel
       ↓
5. Engine          → clean startup and shutdown of all threads
```

---

## 📄 License

MIT

---

> *"Real engineers don't start with architecture. They start with data."*
