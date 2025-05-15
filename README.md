# Orbit
Minimal  3D Rendering Engine Built in Pure C++

![Screenshot 2025-05-13 035255](https://github.com/user-attachments/assets/ba21a307-9cb6-4e8f-819a-210505c63ae4)


## 🌌 Overview

**Orbit** is a lightweight 3D rendering engine written from scratch in pure C++. It demonstrates the core concepts of rendering 3D models without relying on GPU shaders or advanced graphics libraries.

---

## ✨ Features

*  **OBJ file parsing**
*  **Implementation of Rotation Matrix and Perspective Divide**
*  **Rudimentary triangle rasterization**
*  **SDL2 for window and framebuffer display**
*  **No external rendering APIs like OpenGL or Vulkan**

---

## 📁 Structure

```
Orbit/
├── main.cpp          # Entry point, render loop
├── ObjUtils.{h,cpp}  # OBJ file loader
├── utils.{h,cpp}     # Vector math and rendering helpers
├── run.sh            # Build and run script
├── makefile          # Build instructions
```

---

## 🧰 Requirements

* **C++17 or later**
* **SDL2**

### 🔧 Install SDL2

* **Ubuntu/Debian**:
  `sudo apt install libsdl2-dev`

* **macOS (Homebrew)**:
  `brew install sdl2`

* **Windows**:
  Install from [SDL2 Downloads](https://www.libsdl.org/download-2.0.php) and link properly in your IDE or compiler.

---

## ⚙️ Build & Run

```bash
git clone https://github.com/rs0125/Orbit.git
cd Orbit
./run.sh
```

This should open a window displaying a rendered 3D model loaded from an `.obj` file.


---

## 📌 Notes

* No camera movement or lighting system yet
* Models must be in simple `.obj` format
* Future improvements could include:

  * Z-buffer
  * Camera control
  * Gouraud/Phong shading

---

## 📄 License

This project is licensed under the MIT License.
