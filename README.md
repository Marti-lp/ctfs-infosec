# CTF Challenges
This repository contains a collection of CTF-style challenges developed for cybersecurity community events.

The challenges were designed for two distinct contexts. First, an **introductory event** aimed at IT students with the goal of providing their first hands-on exposure to cybersecurity concepts. On the other hand, a **technical security conference** (Ekoparty) featuring more competitive challenges targeting an experienced audience.

The main goals behind these challenges were:
- Introduce foundational security concepts through hands-on problem solving.
- Encourage interest in cybersecurity among students and early practitioners.
- Provide technically engaging, malware-oriented challenges for advanced conference attendees.


## Overview

### Introductory Event Challenges

#### **A plena vista**
- **Difficulty:** Beginner
- **Category:** Steganography / Encoding
- **Description:** A set of images containing hidden encoded strings in different places, like metadata. Each string can be extracted using common steganography tools and decoded using classic encoding schemes.  When combined, the decoded strings form the final flag.
- **Focus:** Familiarization with basic steganography concepts and common encoding techniques.


#### **Get the Plant**
- **Difficulty:** Intermediate
- **Category:** Reverse Engineering / Memory Inspection
- **Description:** A Linux executable that initially presents itself as a simple game. As the user progresses, an in-game dialog allows user input that contains a buffer overflow vulnerability. When exploited, the interrupt handler stores the flag in a CPU register, which can be observed using a debugger.
- **Focus:** Introduction to binary execution flow, memory corruption concepts, and debugger-assisted analysis.

---

### Conference CTF Challenges

#### **Atrapame**
- **Difficulty:** Intermediate
- **Category:** Reverse Engineering
- **Description:** An obfuscated malicious executable that creates and deletes an `.asm` file at runtime. Recovering this file, linking, compiling, and executing it reveals the flag in binary form.
- **Focus:** Dynamic analysis, behavior inspection, Windows event monitoring.


#### **MicMic**
- **Difficulty:** Advanced
- **Category:** Malware Analysis 
- **Description:** A Linux-only executable that spawns multiple threads. While the main thread performs disruptive actions, a secondary thread writes the flag into memory. If execution continues normally, the main thread deletes the binary.
- **Focus:**  Dynamic analysis, thread behavior inspection, memory monitoring, and timing-based analysis techniques.


## Note
Some challenges intentionally provide **only binaries** to participants, reflecting realistic malware analysis and reverse engineering scenarios. When source code is present, it is provided strictly for educational purposes. As always, pwd for the zipped binaries is **infected**.


