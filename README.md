# LanParty

LanParty is an exercise in organizing and managing a team competition following a set of specific rules. The project leverages various data structures—such as lists, queues, stacks, binary search trees (BST), and AVL trees—to simulate match scheduling and determine the winning teams.

## Overview

In this tournament simulation, each team accumulates a score throughout the competition. The project involves:

- **Input Processing:** Reading team data from a file (`d.in`) and creating a list by inserting elements at the beginning in constant time.
- **Elimination Rounds:** Removing teams with the lowest scores (with ties broken by list order) until only a power-of-2 number of teams remain.
- **Match Scheduling:** Forming matches by queuing teams in order, then using two stacks (one for winners and one for losers) to record match outcomes. Winners receive an additional point.
- **Re-queuing Winners:** After each round, winners are re-queued to form new matches, repeating the process until the top 8 teams are determined.
- **Ranking:** Creating a ranking using a BST—ordered by team score in descending order (and by name in descending order if scores are equal)—and building an AVL tree from the top teams to display teams on its second level.

## Key Features

- **Efficient Data Handling:** Utilizes lists for constant-time insertions and queues for match scheduling.
- **Dynamic Elimination:** Iteratively removes teams with the lowest scores to maintain a competitive field.
- **Structured Tournament:** Organizes teams through rounds using stacks for winners and losers.
- **Advanced Ranking:** Implements BST and AVL trees to sort and display the final team rankings.

## Technical Details

- **Language:** The project is primarily implemented in C, with Shell scripts and Makefiles to automate the build process.
- **Input:** Team data is read from the `d.in` file.
- **Build:** The project uses a Makefile for compilation.

## Getting Started

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/bogdan624/LanParty.git
   ```

2. **Build the Project:**

   Use the provided Makefile:

   ```bash
   make
   ```

3. **Run the Application:**

   Execute the compiled application to run the tournament simulation.


