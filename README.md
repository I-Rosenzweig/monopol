**Monopoly**.

**Project Goal:**

To experiment with object-oriented programming.
A Monopoly game actually consists of a number of different elements. 
The project includes various clasess, some of which demonstrate the benefits of "inheritance".

Finally, it was important to run a simulation of the game to see that the rules were balanced.
After running it, I discovered that the game was unbalanced in the sense that it was impossible to lose.


![image](https://github.com/user-attachments/assets/c5bbba06-97bf-4d63-8bcc-e79e6e7996f8)

A C++ project implementing an Object-Oriented Programming (OOP) approach to a board game simulation.
The project features classes such as Board, Player, Slot, Asset, and Queue, following principles like encapsulation, inheritance, and polymorphism.

📌 Features.

A board game simulation where players can move, buy assets, and interact with slots.
OOP concepts like dynamic memory management, operator overloading, and encapsulation.
Debug and Release configurations for both x86 and x64 platforms.

🏗️ Class Overview

🏛️ Board Class (Board.h)

Represents the game board, consisting of multiple slots where players can land.

🏃 Player Class (Player.h)

Represents a game participant.


📦 Queue Class (Queue.h)

Represents a FIFO (First In, First Out) queue that stores Asset objects. Each player has a Queue to manage their owned assets.


🎰 Slot Class and Derived Classes (Slot.h)

Slot (Abstract Base Class)

Represents a generic slot on the board. This is a pure virtual class that serves as a base for all slot types.


🏠 Asset (Derived from Slot)

Represents a purchasable property on the board.

🚦 GO (Derived from Slot)

Represents the "Go" slot where players collect money.

🚔 Jail (Derived from Slot)

Represents the jail slot where players might get stuck.

🎲 Chance (Derived from Slot)

Represents a chance slot where players receive a random effect.

🛠️ Installation & Setup

Prerequisites:

  Visual Studio 2019 (or later) with C++ development tools installed.
  Steps
  Clone the repository:
  sh
  Copy
  Edit
  
git clone https://github.com/yourusername/ooptesting.git

Open ooptesting.sln in Visual Studio.

Select the desired build configuration (Debug/Release, x86/x64).

Build and run the project.

📂 Project Structure

css
Copy
Edit
ooptesting/
├── ooptesting.sln
├── ooptesting/
│   ├── ooptesting.vcxproj
│   ├── src/
│   ├── include/
│   └── tests/
└── README.md
