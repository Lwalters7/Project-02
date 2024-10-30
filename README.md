# Asteroid Game

An SDL2-based game where a player controls a character that avoids incoming asteroids. The game implements core game mechanics such as gravity, jumping, collision detection, and object spawning. 

## Overview

This game is inspired by Flappy Bird mechanics where the player must avoid obstacles to survive. The player controls a spaceship that moves upwards with each jump and falls back down due to gravity. The objective is to avoid colliding with the asteroids that spawn and move from right to left.

## Features

- **Player Movement**: Basic controls allow the player to move left and right and jump.
- **Gravity**: Gravity constantly pulls the player down, requiring the player to jump to avoid falling.
- **Asteroids**: Asteroids spawn at random intervals on the right side of the screen, moving to the left.
- **Collision Detection**: The player can collide with asteroids, ending the game.
- **Component-Based Architecture**: Modular components like `SpriteComponent`, `BodyComponent`, and `AsteroidComponent` add flexibility and scalability to game objects.
- **XML Level Configuration**: Game objects and components can be configured using an XML file.

## Game Screenshot ![Screenshot 2024-10-30 182003](https://github.com/user-attachments/assets/786ae0de-ea7d-4ca9-b552-564646567202)
