# Post Office Package Management System

![C](https://img.shields.io/badge/C-Programming-blue)
![Linked Lists](https://img.shields.io/badge/Data%20Structures-Linked%20Lists-green)
![CO223](https://img.shields.io/badge/Module-CO223-orange)

A C program that simulates a post office package management system using linked lists, developed for the CO223 module milestone project.

## Table of Contents
- [Features](#features)
- [Data Structures](#data-structures)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Input Format](#input-format)
  - [Operations](#operations)
- [Example](#example)
- [Memory Management](#memory-management)
- [Contributing](#contributing)
- [License](#license)

## Features
- Hierarchical organization of packages within post offices and divisions
- Package transfer between post offices with weight validation
- Reporting functions:
  - Print all packages in a division
  - Find division with most packages
- Comprehensive memory management

## Data Structures
The program uses three levels of linked lists:
1. **Division List**: Contains division nodes
2. **Post Office List**: Within each division node
3. **Package List**: Within each post office node

## Getting Started

### Prerequisites
- GCC compiler
- Basic understanding of C programming

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/post-office-system.git
   cd post-office-system
