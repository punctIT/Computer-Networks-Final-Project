# NetworkDevicesMonitor
**NetworkDevicesMonitor** is a client-server application designed to monitor IT infrastructure traffic and endpoints. I built this project to explore high-concurrency server architecture using modern C++23 and asynchronous GUI development with Qt6.

It unifies standard **Syslog** messages with custom telemetry from **Agents** into a single dashboard, featuring a custom-built security layer to filter traffic.

---

## 🧐 What is it?

The system solves the problem of monitoring disparate network sources. Instead of just logging text files, it parses incoming data, checks against a security whitelist/blacklist, filters out noise, and pushes real-time alerts to a connected GUI client.

It consists of three main parts:
1.  **The Backend Server:** A multi-threaded C++ engine that handles TCP connections, parses protocols, and manages the SQLite database.
2.  **The Agents:** Lightweight scripts/apps running on endpoints sending JSON metrics (CPU/RAM/Disk).
3.  **The Client:** A Qt6 Desktop application for visualization and administration.

---

## ⚙️ Architecture & Technical Highlights

I wanted to ensure the server could handle multiple streams without blocking, so the architecture relies heavily on decoupling I/O from processing.

### The Server (C++23)
* **I/O Multiplexing:** Uses `poll()` to handle incoming connections on ports 1514 (Syslog), 9000 (Agents), and 8080 (Admin).
* **Producer-Consumer Pattern:** Network threads push raw data into thread-safe queues. Worker threads pop data, parse it, and store it. This prevents the network layer from freezing during heavy database writes.
* **Database:** Uses SQLite3 in **WAL (Write-Ahead Logging)** mode to allow concurrent reads (for the dashboard) and writes (from the logs).
* **Security:** Implements an in-memory `SourceManager` protected by shared mutexes to instantly drop traffic from blacklisted IPs before any processing occurs.

### The Client (Qt6)
* **Asynchronous Networking:** The UI runs on the main thread, while all network communication happens in background workers using Qt Signals & Slots. The interface never freezes, even when fetching thousands of logs.
* **Custom Protocol:** Communication between Client and Server uses a custom protocol I designed called **JUNK** (*Just Useful Notation Kinda*). It's a hybrid binary/text protocol (Length Header + Key-Value ASCII payload) that is easy to parse but robust against fragmentation.

---

## 🚀 Features

* **Hybrid Collection:**
    * Standard Syslog (RFC 5424) support.
    * Custom JSON-based agent telemetry.
* **Real-time Dashboard:** Live updates for logs and resource usage charts (Donut/Line charts).
* **Security Management:**
    * **Whitelist:** "Known" devices are tagged with hostnames.
    * **Blacklist:** Malicious IPs are dropped immediately.
* **Smart Filtering:**
    * Filter by log severity.
    * Filter by message content (keyword).
* **Alerting:** Set custom keywords (e.g., "Panic", "Error"). If the server sees them, it triggers an instant pop-up on the client.

---

## 🛠️ Tech Stack

* **Core:** C++23 (Modules, `std::expected`, Smart Pointers).
* **GUI:** Qt 6.5+ (Widgets, Charts).
* **Storage:** SQLite3.
* **Concurrency:** `std::thread`, `std::mutex`, `std::condition_variable`, `std::shared_mutex`.
* **Build System:** CMake.

---

## 📥 Getting Started

### Prerequisites
* A C++ compiler supporting C++23 (GCC 12+, Clang 15+, or MSVC 2022).
* Qt 6 SDK installed.
* CMake.

### Build Instructions

1.  **Clone the repo:**
    ```bash
    git clone [https://github.com/your-username/NetworkDevicesMonitor.git](https://github.com/your-username/NetworkDevicesMonitor.git)
    cd NetworkDevicesMonitor
    ```

2.  **Build using CMake:**
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

3.  **Run:**
    * First, start the **Server** (it will initialize the DB).
    * Then, start the **Client** and connect to `127.0.0.1` (or your server IP).

---

## 🧪 Testing Scenarios

To verify it works, you can try:
1.  **Agent Simulation:** Run the provided Python script `mock_agent.py` to send dummy JSON metrics to port 9000. Watch the graphs update in real-time.
2.  **Security Check:** Add your own IP to the Blacklist via the GUI. Try to connect—the server should immediately sever the connection.
3.  **JUNK Protocol:** Use Wireshark on port 8080 to see the custom Key-Value packets in action.

---

## 📝 Author

**Ivaniciuc Teodor-Arsenie**
*Faculty of Computer Science, "Alexandru Ioan Cuza" University of Iasi*

*This project was developed for the Computer Networks course.*