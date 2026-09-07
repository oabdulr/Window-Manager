# Desktop Windowing Prototype

A C++ desktop simulation built with GLFW and OpenGL. It implements a small windowing interface inside an application, including desktop icons, movable and resizable windows, custom cursors, and text and simulation views.

## Features

- Desktop icons that open text and simulator windows.
- Custom title bars, close controls, and resize handles.
- Mouse and keyboard input handling.
- Bitmap-font rendering and texture loading.
- Custom mouse and text cursors.
- A simulation view updated through the application's main loop.

This project explores GUI behavior and rendering within a single application. It does not manage operating-system windows.

## Build and run

Requirements:

- Windows with an OpenGL-capable graphics driver.
- Visual Studio 2022 with **Desktop development with C++**.
- MSVC v143 and a Windows 10 SDK.

```bash
git clone https://github.com/oabdulr/Window-Manager.git
```

1. Open `2D Engine.sln` in Visual Studio.
2. Select **x64** and **Debug** or **Release**. The x64 configurations contain the C++20 and GLFW/OpenGL linker settings.
3. Set the debugger's working directory to `$(ProjectDir)` so relative font and image paths resolve inside `2D Engine/`.
4. Build and launch from Visual Studio.

GLFW headers and library files are included under `2D Engine/includes/`. If the bundled library does not match your toolchain, replace it with a compatible GLFW build and update the project paths.

## Try the interface

- Select **Create Window** to open a text window.
- Select **Simulator** to open the simulation view.
- Drag a window by its title bar.
- Drag the lower-right resize handle to change its dimensions.
- Use the close control to dismiss a window.

## Code organization

- [main.cpp](2D%20Engine/main.cpp): initialization, desktop setup, and render loop.
- [engine/game_engine.cpp](2D%20Engine/engine/game_engine.cpp): GLFW/OpenGL integration.
- [engine/types/window](2D%20Engine/engine/types/window): window behavior and content views.
- [engine/types/desktop](2D%20Engine/engine/types/desktop): desktop icons.
- [engine/types/drawing](2D%20Engine/engine/types/drawing): drawing and texture operations.
- [engine/types/simulator](2D%20Engine/engine/types/simulator): simulation objects and updates.

## Current scope

The implementation is a Windows-focused prototype. Resource ownership and build portability need further work, and the repository does not yet include automated tests. The solution's historical `2D Engine` name is retained in the build files.

## Dependencies

GLFW supplies window creation and input; OpenGL supplies rendering; stb_image supports image loading. Third-party source and assets retain their respective terms and attribution.
