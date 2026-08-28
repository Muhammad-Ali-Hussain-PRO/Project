# QuantumForge: Low-Latency Rollback Networking Engine for Multiplayer Systems

A high-performance, real-time multiplayer game engine server built from scratch in modern C++17. QuantumForge demonstrates deterministic simulation, combat state machines, and rollback reconciliation for fast-paced competitive environments.

## Technical Architecture Highlights

- **Deterministic Physics Loop:** A rendering-independent state machine processes movement, attacks, hit stun, and collision hitboxes.
- **State Snapshot History Buffer:** Bounded frame snapshots preserve enough simulation history to rewind a match without unbounded memory growth.
- **Rollback and Reconciliation Netcode:** Late inputs restore a historical state, replay the corrected input timeline, and bring the live simulation back to the current frame.

## Repository Structure

```text
QuantumForge-Engine/
├── CMakeLists.txt
├── main.cpp
├── engine.hpp
├── network.hpp
└── README.md
```

## Build and Run

```bash
mkdir build && cd build
cmake ..
cmake --build .
./QuantumForgeEngine
```

## Why This Project Stands Out

QuantumForge focuses on core multiplayer infrastructure problems: deterministic state transitions, bounded snapshot storage, delayed input handling, and reproducible simulation. The small, dependency-free codebase makes the reconciliation flow straightforward to inspect and extend.