# Pakistan Autonomous Digital Voting Architecture (ADVANCE)

A high-integrity, console-based Digital Voting and Electoral Management System custom-engineered in C++ from the ground up. This system mirrors the strategic operations of the Election Commission (ECP) and NADRA workflows, facilitating fast voter verification, biometric authentication simulation, live ballot queue management, and instantaneous consolidated result generation (Form-47 simulation).

To demonstrate low-level memory layout control and algorithmic optimization, **this project strictly avoids the C++ Standard Template Library (STL)** and utilizes self-implemented data structures.

---

## 🏛️ System Architecture & Data Structures

The backend architecture is engineered around specific data structures to handle heavy workloads with high speed and zero memory leaks:

1. **`VoterHashMap` (Custom Chained Hash Map)** Utilizes an optimized hashing algorithm on the CNIC string to provide near $O(1)$ time complexity for voter verification. Handles collisions via Linked-List Chaining.
2. **`Queue<T>` (Custom FIFO Linked-Queue)** Manages the real-time flow of voters waiting outside a verified polling booth booth to prevent identity or sequence spoofing.
3. **`ArrayList<T>` (Custom Resizing Vector)** A dynamically resizing contiguous array block handling safe registration scaling for candidates and constituencies.
4. **Form-47 Sorting Engine (Custom Bubble Sort)** An in-place sorting mechanism running over multidimensional structures to categorize and rank candidates globally according to highest vote counts.

---

##  Key Features & Modules

###  1. ECP Administration Control Panel
* **Constituency Profiling:** Map out national (`NA-XX`) and provincial (`PP-XX`) electoral domains dynamically.
* **Candidacy Archiving:** Seamless enrollment of candidates with customized metadata (Symbol, Legal Name, Party Affiliation).
* **Live Freezing Engine:** Admins can lock or pull down live voting nodes globally to maintain data integrity before official transmissions.
* **Security Compliance Audits:** Generates real-time chronological event streaming inside automated `election_audit_log.txt` storage logs.

###  2. Biometric Polling Station Controller
* **NADRA Verification Intersect:** Verifies if a voter is enrolled or if their CNIC structural format is recognized.
* **Double Voting Prevention:** Immediate lockout flags triggered automatically if a voter tries to access a Green (NA) or White (PP) ballot paper twice.
* **Biometric Hash Matcher:** Simulates verification tokens comparing left-thumb blueprint string patterns against encrypted dataset indices.

###  3. Consolidated Transmission Engine (Form-47 Engine)
* On-demand parsing of multi-constituency ballots.
* Generates live seat ranking analytics highlighting the clear absolute winners instantly.

---

##  File Storage Matrix (Flat-File DB)

The system automatically spins up, reads, and updates state persistently across multiple cross-referenced storage blocks:
* `voters.txt` - Flat-file database housing identities, enrollment keys, and vote execution states.
* `candidates.txt` - Holds localized candidate statistics and absolute ballot tallies.
* `constituencies.txt` - Keeps total population density maps and demographic boundaries.
* `election_audit_log.txt` - Append-only tamper-evident transactional log tracking administrative actions.

---

##  How to Compile and Run Locally

### Prerequisites
Ensure you have a modern C++ compiler installed (e.g., GCC/MinGW compiler toolchain) and added to your operating system's environment variables (`PATH`).

### Commands to Run

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YOUR_USERNAME/pakistan-digital-voting-system.git](https://github.com/YOUR_USERNAME/pakistan-digital-voting-system.git)
   cd pakistan-digital-voting-system
