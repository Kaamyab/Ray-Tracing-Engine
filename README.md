# Raytracing Engine

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

This is a simple raytracing project written in **C++**. It renders images based on user input for image **width** and **samples per pixel**. The rendered image is saved in `output.ppm`.

![1920x1080 1000 Samples per pixel](https://i.imgur.com/1juiqzF.png)
![1920x1080 1000 Samples per pixel](https://i.imgur.com/WarwGoH.png)

## Getting Started

### Prerequisites

- C++ compiler (supporting C++11)
- Git

### Compilation

Clone the repository:

```bash
git clone https://github.com/your-username/your-raytracing-repo.git
cd your-raytracing-repo
```

```bash
g++ main.cpp -o main -std=c++17
```

## Running the Program

Run the compiled program:

```bash
./main
```

Follow the prompts to enter the image width and samples per pixel.

## How Raytracing Works

Raytracing is a technique used in computer graphics to simulate the way light interacts with objects in a scene. The basic steps involve shooting rays from the camera into the scene, calculating the intersections with objects, and determining the color of the intersected points.

In this project:

- The user provides the image width and samples per pixel.
- The program shoots rays through each pixel, adjusting for the aspect ratio.
- For each pixel, multiple rays are traced (samples per pixel).
- The program calculates the color of each pixel by simulating the interaction of light with objects in the scene.

## Contributing

If you'd like to contribute to this project, please follow the standard GitHub fork and pull request workflow.

## License

This project is licensed under the MIT License
