# YapYap

# Video Capture Optimization with GStreamer and LuaJIT

This project provides a Lua script to capture video from your camera and encode it using hardware-accelerated video encoders for various platforms (NVIDIA, Intel, AMD). The script uses **GStreamer** with optimizations for low-latency video capture and high-quality encoding. It supports **Linux**, **Windows**, and **MacOS** platforms.

## Features
- Hardware-accelerated encoding using **NVIDIA NVENC**, **Intel Quick Sync (VA-API)**, and **AMD VA-API**.
- Optimized for low latency and high-quality video capture.
- Supports video resolution up to **1280x720** with **30fps**.
- Configurable bitrate for encoding.
- Output to **MP4** file format.
- Cross-platform support: **Linux**, **Windows**, and **MacOS**.

## Requirements

Before using the script, ensure that you have the following installed on your system:

### GStreamer
GStreamer is the core multimedia framework that the script uses for video capture and encoding.

- **Linux**:
  For **Ubuntu/Debian-based** systems, install the necessary packages using the following commands:

  ```bash
  sudo apt-get install gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-vaapi
  ```

- **Windows/MacOS**:
  Download the GStreamer binaries from the official GStreamer website:
  - [GStreamer download page](https://gstreamer.freedesktop.org/download/)

  Follow the platform-specific installation instructions provided on the download page.

### LuaJIT with FFI
LuaJIT is used for the **Foreign Function Interface (FFI)**, which allows the Lua script to interact with GStreamer.

- Install **LuaJIT** by following the instructions on the official LuaJIT website: [LuaJIT installation](https://www.lua.org).

- Make sure **FFI** is enabled (it is by default in LuaJIT).

### Video Encoder Dependencies
The script supports hardware-accelerated video encoding via **NVIDIA NVENC**, **Intel Quick Sync** (VA-API), and **AMD VA-API**.

For each platform:
- **Linux**: Ensure that you have the necessary drivers and VA-API support installed.
- **Windows**: Ensure that the appropriate hardware drivers for **NVIDIA** or **Intel** are installed.
- **MacOS**: VA-API and hardware encoding via Intel Quick Sync are supported on macOS with the right GStreamer plugins.

## Configuration

You can configure the video capture settings such as the encoder choice, resolution, framerate, and output file. The script currently supports **NVIDIA NVENC**, **Intel Quick Sync** (VA-API), and **AMD VA-API** for hardware acceleration.

### Available Encoder Choices:
- **NVIDIA**: `nvh264enc`
- **Intel**: `vaapih264enc` (Intel Quick Sync)
- **AMD**: `vaapih264enc` (using VA-API)

### Configurable Options:
- **Resolution**: `1280x720`
- **Framerate**: `30 fps`
- **Bitrate**: `4000000` (4 Mbps)
- **Max Buffer Size**: `1048576` (1 MB)
- **Queue Buffers**: `5` (for low latency)

You can adjust these options at the beginning of the **`video_capture.lua`** script.

### Example:
```lua
local encoder_choice = "nvh264enc"  -- Choose: "nvh264enc", "vaapih264enc", "vaapih264enc" for Intel/AMD
local bitrate = 4000000  -- 4 Mbps for better quality
local width = 1280
local height = 720
local framerate = 30
local output_file = "output.mp4"
local max_buffer_size = 1048576  -- 1 MB buffer for low latency
local max_queue_buffers = 5      -- Limit queue buffers to 5 for low latency
```

## Usage

### Steps to Run the Video Capture Script:

1. **Clone or Download** this repository.
2. **Install GStreamer**:
   - On **Linux**, use the instructions above to install GStreamer and required plugins.
   - On **Windows/MacOS**, download and install GStreamer from the official website.
3. **Install LuaJIT** and ensure the **FFI** library is available.
4. Open the **`video_capture.lua`** file in a text editor and configure the encoder, resolution, framerate, and other options as needed.
5. **Run the Script**:
   - Open a terminal or command prompt in the repository directory.
   - Run the script using **LuaJIT**:

   ```bash
   luajit video_capture.lua
   ```

This will start the video capture using the specified encoder and settings, and output the encoded video to the `output.mp4` file.

### Example of Usage:
If you want to capture video using **NVIDIA NVENC**, modify the script to use `nvh264enc`:

```lua
local encoder_choice = "nvh264enc"  -- Choose: "nvh264enc", "vaapih264enc" for Intel/AMD
```

The script will capture video from your camera, encode it with **NVIDIA NVENC** hardware acceleration, and save the output to `output.mp4`.

## Notes on Latency and Quality

The video capture script is designed to offer **low latency** and **high video quality**. To achieve this, the following optimizations have been implemented:

### Low Latency:
- **Low latency buffers**: The GStreamer pipeline is optimized for minimal buffering to ensure fast processing and reduced delays.
- **Small queue buffers**: By limiting the number of buffers in the GStreamer pipeline, the script minimizes any potential delay that may occur between capturing and encoding.

### Video Quality:
- **Constant Bitrate (CBR)**: The video is encoded with a constant bitrate, which helps maintain a stable and consistent quality throughout the video. The bitrate is configurable (default is 4 Mbps), and you can adjust it for better quality or lower bandwidth usage.
- **Hardware-accelerated Encoding**: By using hardware-accelerated video encoders (such as **NVIDIA NVENC** and **Intel Quick Sync**), the script ensures that video encoding is done efficiently without overloading the CPU, resulting in smoother video capture.

### Recommended Settings for Best Quality:
- For **NVIDIA NVENC**, use `nvh264enc` with a bitrate of at least **4 Mbps**.
- For **Intel VA-API**, use `vaapih264enc` with a **similar bitrate** (adjustable based on your needs).
- Lower bitrates may result in reduced video quality, while higher bitrates can improve the clarity of the video but may require more bandwidth or system resources.

### Hardware Acceleration:
- **NVIDIA**: Ensure that your system has an **NVIDIA GPU** that supports NVENC, and that you have installed the appropriate **NVIDIA drivers**.
- **Intel**: Ensure that your system has an **Intel GPU** supporting **Intel Quick Sync**, and that you have **VA-API** installed and properly configured.
- **AMD**: Ensure that your system has an **AMD GPU** and **VA-API** installed to enable hardware encoding.

# TEST Alpha Version 0.0.1a #
Rédiger et fournir

Je m'efforce de créer un fichier README.md complet avec toutes les explications nécessaires, y compris des instructions sur l'installation des dépendances, l'exécution du projet via Love2D et Geany, la compilation de la fonction de capture en C, et la mention de la licence.

Below is the updated README.md file that includes all of the explanations, installation instructions, usage details, and license information.

# Video Capture Optimization with GStreamer and LuaJIT
**Version: 0.0.1a**

This project provides a Lua script to capture video from your camera and encode it using hardware-accelerated video encoders (NVIDIA, Intel, AMD). The script leverages **GStreamer** with optimizations for low-latency video capture and high-quality encoding. It supports **Linux**, **Windows**, and **MacOS** platforms.

## Features

- **Hardware-accelerated encoding** using:
  - **NVIDIA NVENC**
  - **Intel Quick Sync (VA-API)**
  - **AMD VA-API**
- **Optimized for low latency** and **high video quality**.
- Supports video resolution up to **1280x720** at **30fps**.
- Configurable bitrate for encoding.
- Output in **MP4** file format.
- Cross-platform support: **Linux**, **Windows**, and **MacOS**.

## Requirements & Installation on Ubuntu 24.04 LTS

### 1. Install GStreamer and Required Plugins

GStreamer is the core multimedia framework used for video capture and encoding. On Ubuntu 24.04 LTS, install the necessary packages using:

```bash
sudo apt-get update
sudo apt-get install gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-vaapi

2. Install LuaJIT

LuaJIT is needed to run your Lua scripts with the Foreign Function Interface (FFI):

sudo apt-get install luajit

3. Install Love2D

Love2D provides the graphical framework that serves as the container for your project. To install Love2D on Ubuntu:

sudo apt-get install love

4. (Optional) Install Geany

Geany is a lightweight text editor/IDE with support for Lua. Install it via:

sudo apt-get install geany

Project Structure

Place the following files in your project directory:

    main.lua – The Love2D entry point that integrates the video capture module.
    video_capture.lua – The Lua module that executes the GStreamer command for video capture.
    (Optionally) other modules such as libgst_lib.lua if used.

Configuration

You can configure the video capture parameters in video_capture.lua. The default settings are as follows:

local encoder_choice = "nvh264enc"  -- Options: "nvh264enc" for NVIDIA or "vaapih264enc" for Intel/AMD.
local bitrate = 4000000            -- Bitrate in bps (default: 4 Mbps).
local width = 1280               -- Video width.
local height = 720               -- Video height.
local framerate = 30             -- Frames per second.
local output_file = "output.mp4" -- Output file name.
local max_buffer_size = 1048576  -- Buffer size in bytes (1 MB) for low latency.
local max_queue_buffers = 5      -- Limit the queue to 5 buffers to minimize latency.

Adjust these values as needed based on your hardware and performance requirements.
Usage
Running the Project via Love2D

    Organize Files:
    Ensure that main.lua and video_capture.lua are in the same directory.

    Launch the Project:
    Open a terminal in your project directory and run:

    love .

    This command will launch a Love2D window. The project automatically calls the video capture function, and a message is displayed indicating that video capture has started. The captured video will be saved as output.mp4 in your project folder.

Running the Project via Geany

If you prefer using Geany:

    Open Geany and load your project folder (containing main.lua).

    Configure a custom "Execute" command:

        In Geany, go to Build → Set Build Commands.

        Set the "Execute" command to:

        love "%d"

    This configuration lets you run your project directly from Geany.

(Optional) Compiling & Testing the C Capture Function

If you wish to test the C function capture_video() (found in capture_video.c), follow these instructions:

    Compilation (Linux):

gcc -o capture_video capture_video.c `pkg-config --cflags --libs gstreamer-1.0`

Execution:

    ./capture_video

For Windows, use a compatible compiler (e.g., MinGW), replace v4l2src with dshow in the source element, and adjust compilation flags as needed.
Notes on Latency and Video Quality

This project is optimized for both low latency and high video quality:
Low Latency:

    Small Buffers: The GStreamer pipeline is configured with small buffers to minimize delay between capture and encoding.
    Limited Queue Buffers: Restricting the number of buffers in the queue (default is 5) further reduces latency.

Video Quality:

    Constant Bitrate (CBR): Using a constant bitrate (default 4 Mbps) ensures stable video quality.
    Hardware-accelerated Encoding: Leveraging hardware encoders (NVIDIA NVENC, Intel Quick Sync, AMD VA-API) offloads encoding from the CPU, resulting in smoother capture and improved clarity.

Recommended Settings:

    For NVIDIA NVENC, use "nvh264enc" with a bitrate of at least 4 Mbps.
    For Intel/AMD VA-API, use "vaapih264enc" with a similar bitrate.
    Adjust the bitrate according to your needs—lower values may reduce quality, while higher values can improve clarity at the cost of increased resource usage.

License

This project is licensed under the GPL-3.0 License.
See the LICENSE file for more details.
Summary of Instructions

    Install Dependencies:
        GStreamer and required plugins.
        LuaJIT.
        Love2D.
        (Optional) Geany.

    Configure the Project:
        Adjust the settings in video_capture.lua as needed.

    Run the Project:
        From the terminal: love .
        Or directly via Geany with a custom execute command.

    Optional C Function Testing:
        Compile and run capture_video.c for testing purposes.

This documentation provides all the necessary steps and information to set up and run the project in version 0.0.1a on Ubuntu 24.04 LTS, ensuring that it is accessible to the widest audience possible.


---

### How to Use This README

1. Copy the content above into a file named **README.md**.
2. Place this file in the root of your GitHub repository.
3. Ensure that the [LICENSE](LICENSE) file is included with the proper GPL-3.0 text.

This README now contains all the explanations—including dependency installation for Ubuntu 24.04 LTS, configuration, usage via Love2D and Geany, optional instructions for testing the C capture function, and the license information—making it accessible for the broadest audience.

Feel free to update any section as needed.

Vous avez dit :
Créé le 2. 3. 4. Project Stucture Configuration Usage Notes on Latency and Video Quality Licence et summary of instruction
ChatGPT

Préparant la structure du projet

Je suis en train de créer un document markdown en suivant les instructions données pour la section 2, 3, 4, etc., en détaillant l'installation, la structure du projet, la configuration, et plus.

Below is the updated README.md content with the requested sections: "Project Structure", "Configuration", "Usage", "Notes on Latency and Video Quality", "License", and "Summary of Instructions".

You can copy the content into your README.md file.

# Video Capture Optimization with GStreamer and LuaJIT
**Version: 0.0.1a**

This project provides a Lua script to capture video from your camera and encode it using hardware-accelerated video encoders (NVIDIA, Intel, AMD). The script leverages **GStreamer** with optimizations for low-latency video capture and high-quality encoding. It supports **Linux**, **Windows**, and **MacOS** platforms.

## 1. Features

- **Hardware-accelerated encoding** using:
  - **NVIDIA NVENC**
  - **Intel Quick Sync (VA-API)**
  - **AMD VA-API**
- **Optimized for low latency** and **high video quality**.
- Supports video resolution up to **1280x720** at **30fps**.
- Configurable bitrate for encoding.
- Output in **MP4** file format.
- Cross-platform support for **Linux**, **Windows**, and **MacOS**.

## 2. Project Structure

Place the following files in your project directory:

- **main.lua**
  The Love2D entry point that integrates the video capture module and provides a simple GUI.

- **video_capture.lua**
  The Lua module that executes the GStreamer command for video capture. It contains all the configuration parameters for the capture pipeline.

- *(Optional)* Other modules such as **libgst_lib.lua** if you have additional functionality.

## 3. Configuration

The video capture parameters are defined in **video_capture.lua**. You can adjust these options to suit your hardware and performance requirements:

```lua
local encoder_choice = "nvh264enc"  -- Options: "nvh264enc" for NVIDIA or "vaapih264enc" for Intel/AMD.
local bitrate = 4000000            -- Bitrate in bps (default: 4 Mbps).
local width = 1280               -- Video width.
local height = 720               -- Video height.
local framerate = 30             -- Frames per second.
local output_file = "output.mp4" -- Output file name.
local max_buffer_size = 1048576  -- Buffer size in bytes (1 MB) for low latency.
local max_queue_buffers = 5      -- Limit the queue to 5 buffers to minimize latency.

Adjust these values as needed.
4. Usage
Running the Project via Love2D

    Organize Files:
    Ensure that main.lua and video_capture.lua are in the same directory.

    Launch the Project:
    Open a terminal in your project directory and run:

    love .

    This command will launch a Love2D window. The project automatically calls the video capture function, and a message is displayed indicating that video capture has started. The captured video is saved as output.mp4 in your project folder.

Running the Project via Geany

    Open Geany and load your project folder (the one containing main.lua).

    Configure a custom "Execute" command in Geany:

        Go to Build → Set Build Commands.

        Set the "Execute" command to:

        love "%d"

    This lets you run your project directly from Geany.

(Optional) Testing the C Capture Function

If you wish to test the C function capture_video() (from capture_video.c):

    Compile (Linux):

gcc -o capture_video capture_video.c `pkg-config --cflags --libs gstreamer-1.0`

Execute:

    ./capture_video

For Windows, use a compatible compiler (such as MinGW), replace v4l2src with dshow, and adjust the compilation flags accordingly.
Notes on Latency and Video Quality

This project is optimized to deliver both low latency and high video quality:

    Low Latency:
        Small Buffers: The GStreamer pipeline is configured with small buffers to minimize the delay between capture and encoding.
        Limited Queue Buffers: Restricting the number of buffers (default is 5) further reduces latency.

    Video Quality:
        Constant Bitrate (CBR): Using a constant bitrate (default 4 Mbps) ensures stable quality throughout the capture.
        Hardware-accelerated Encoding: Offloading encoding to hardware encoders (NVIDIA NVENC, Intel Quick Sync, AMD VA-API) reduces CPU load and improves video clarity.

Recommended Settings:

    For NVIDIA NVENC, use "nvh264enc" with a bitrate of at least 4 Mbps.
    For Intel/AMD VA-API, use "vaapih264enc" with a similar bitrate.
    Adjust bitrate as necessary; lower values may reduce quality, while higher values can enhance clarity at the cost of increased resource usage.

License

This project is licensed under the GPL-3.0 License.
See the LICENSE file for details.
Summary of Instructions

    Install Dependencies:
        GStreamer and required plugins.
        LuaJIT.
        Love2D.
        (Optional) Geany.

    Configure the Project:
        Adjust settings in video_capture.lua according to your hardware and needs.

    Run the Project:
        Launch via terminal with love . or use Geany with a custom execute command.

    (Optional) Test the C Capture Function:
        Compile and run capture_video.c for additional testing.

## License

This project is licensed under the **GPL-3.0 License**. See the [LICENSE](LICENSE) file for more details.
