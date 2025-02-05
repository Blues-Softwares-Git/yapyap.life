# yapyap.life
Yap Yap your favorite virtuel social life

## XMPP Video Conference with Love2D and Prosody

This project implements an **XMPP-based video conference system** with a custom **Love2D client** and a **Prosody server**. It supports video capture and streaming via GStreamer and allows video calls between clients.

## Dependencies

### Common Dependencies

- **Love2D**: Used to create the client application with an interactive GUI.
  - Download: [https://love2d.org/](https://love2d.org/)
  
- **GStreamer**: A multimedia framework used for video capture and encoding.
  - Installation:
    - Linux: `sudo apt-get install libgstreamer1.0-dev`
    - Windows: Download and install from [GStreamer website](https://gstreamer.freedesktop.org/download/).
    - macOS: `brew install gstreamer`
  
### Platform-Specific Dependencies

#### Linux

- **GStreamer Development Libraries**:
  ```bash
  sudo apt-get install libgstreamer1.0-dev
  ```

- **Compiling the C library**:
  ```bash
  gcc -shared -fPIC -o libgstcapture.so gstcapture.c $(pkg-config --cflags --libs gstreamer-1.0)
  ```

#### Windows

- **GStreamer**:
  - Download from [GStreamer website](https://gstreamer.freedesktop.org/download/).
  - Install and set the GStreamer paths in your environment variables.

- **Compiling the C library**:
  If you are using **MinGW** or **MSYS2**, compile the library as follows:
  ```bash
  gcc -shared -o gstcapture.dll gstcapture.c -IC:/path/to/gstreamer/include -LC:/path/to/gstreamer/lib -lgstreamer-1.0
  ```

#### macOS

- **GStreamer**:
  - Install GStreamer via **Homebrew**:
    ```bash
    brew install gstreamer
    ```

- **Compiling the C library**:
  ```bash
  gcc -shared -o libgstcapture.dylib gstcapture.c $(pkg-config --cflags --libs gstreamer-1.0)
  ```

---

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/yourproject.git
   cd yourproject
   ```

2. **Set up the C library**:
   - Compile the C library for your platform (see dependencies above).
   - Place the compiled library (`libgstcapture.so`, `gstcapture.dll`, or `libgstcapture.dylib`) in the root of the repository.

3. **Run the Love2D client**:
   - Open the project folder with Love2D.
   - You should now be able to see the video capture in the Love2D window.

---

## Example Code (Step 2: LuaJIT FFI Integration)

Here is the Lua code to load the compiled GStreamer library and capture video using LuaJIT FFI:

```lua
local ffi = require("ffi")

-- Detect the operating system and load the appropriate library
local libgst_lib
if love.system.getOS() == "Windows" then
    libgst_lib = ffi.load("gstcapture.dll")
elseif love.system.getOS() == "OS X" then
    libgst_lib = ffi.load("libgstcapture.dylib")
else
    libgst_lib = ffi.load("libgstcapture.so")
end

-- Declare the C function
ffi.cdef[[
    void capture_video();
]]

-- Call the function to start video capture
libgst_lib.capture_video()
```

This code dynamically loads the appropriate GStreamer library based on the operating system and starts capturing video. You can then display the video in Love2D using textures.

---

## Future Plans

- **Video Conferencing**: Integrate RTP streaming with Prosody and create a server for multi-party video conferencing.
- **Optimization**: Improve video encoding and network handling to support real-time video calls.
- **Cross-platform compatibility**: Improve support and test on various systems to ensure seamless operation across platforms.

---

## License

This project is licensed under the **GPLv3** License - see the [LICENSE](LICENSE) file for details.
