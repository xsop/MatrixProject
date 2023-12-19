# Arduino Bomberman Matrix Game

![Bomberman Matrix Game](src/bomberman-logo.png)

## Table of Contents

- [Introduction](#introduction)
- [Components](#components)
- [Code overview](#code-overview)
- [Usage](#usage)
- [Gameplay](#gameplay)

## Introduction

This project brings the popular Bomberman game to life on an LED matrix using Arduino. It combines hardware and software to create a fun and interactive gaming experience. The game features include player movement, bomb placement, and enemy interaction, among others.

<video width="200" loop autoplay controls>
    <source src="src/gameplay.mp4" type="video/mp4">
</video>

## Components

- Arduino Uno
- Medium Breadboard
- Small Breadboard
- 8x8 LED Matrix
- Joystick
- MAX7219 Driver
- 10k Ohm Resistor
- C104 Capacitor
- C4 10μF Capacitor
- LCD Display
- Buzzer
- 220 Ohm Resistor
- Potentiometer
- wires

## Code overview

- The code is written in many different files to make it easier to read and understand
- MatrixProject.ino is the main file that runs the game and calls functions from other files
- Consts.h contains all the constants used in the game and Variables.h contains all the variables that will change during the game
- Code is modularised so it could accept additional features in the future, such as a bigger map than the matrix size (which I wish it was already done)

## Usage

- The menu screen is displayed on the LCD display
- The game screen is displayed on the LED matrix
- Use the joystick to navigate the menu
- Press the joystick to select an option

## Gameplay

- [Video Showcase](https://www.youtube.com/watch?v=QRQNpLwF-fY)
- Move the player character using the joystick
- Place bombs strategically to destroy enemies as quickly as possible
- Avoid enemies as they will kill you, they get faster over time so be careful!
- The game ends when all enemies are defeated, or the player loses all lives
- Score is calculated by how many and how quick you kill enemies
- You can choose the amount of enemies in the game for a potential higher score

Have fun! 🎮