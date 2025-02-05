-- File: libgst_lib.lua
--[[
Video Capture Optimization with GStreamer and LuaJIT
Copyright (C) 2025 Major_Ghz

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
]]--

local libgst_lib = {}

-- Capture video using GStreamer with configurable parameters.
-- Parameters (all optional):
--   encoder_choice: "nvh264enc" (default) or "vaapih264enc" (pour Intel/AMD)
--   bitrate: en bits par seconde (par défaut 4000000 pour 4 Mbps)
--   width: largeur de la vidéo (par défaut 1280)
--   height: hauteur de la vidéo (par défaut 720)
--   framerate: images par seconde (par défaut 30)
--   output_file: nom du fichier de sortie (par défaut "output.mp4")
--   max_buffer_size: taille maximale du buffer en octets (par défaut 1048576, soit 1 MB)
--   max_queue_buffers: nombre maximum de buffers dans la file (par défaut 5)
function libgst_lib.capture_video(encoder_choice, bitrate, width, height, framerate, output_file, max_buffer_size, max_queue_buffers)
  encoder_choice   = encoder_choice   or "nvh264enc"
  bitrate          = bitrate          or 4000000
  width            = width            or 1280
  height           = height           or 720
  framerate        = framerate        or 30
  output_file      = output_file      or "output.mp4"
  max_buffer_size  = max_buffer_size  or 1048576
  max_queue_buffers= max_queue_buffers or 5

  local gst_command = ""

  if encoder_choice == "nvh264enc" then
    gst_command = string.format(
      "gst-launch-1.0 v4l2src ! video/x-raw, width=%d, height=%d, framerate=%d/1 ! " ..
      "queue max-size-buffers=%d max-size-time=5000000 max-size-bytes=%d ! " ..
      "nvh264enc bitrate=%d preset=high-quality ! h264parse ! mp4mux ! filesink location=%s",
      width, height, framerate, max_queue_buffers, max_buffer_size, bitrate, output_file
    )
  elseif encoder_choice == "vaapih264enc" then
    gst_command = string.format(
      "gst-launch-1.0 v4l2src ! video/x-raw, width=%d, height=%d, framerate=%d/1 ! " ..
      "queue max-size-buffers=%d max-size-time=5000000 max-size-bytes=%d ! " ..
      "vaapih264enc rate-control=cbr bitrate=%d ! h264parse ! mp4mux ! filesink location=%s",
      width, height, framerate, max_queue_buffers, max_buffer_size, bitrate, output_file
    )
  else
    print("Unsupported encoder choice: " .. encoder_choice)
    return
  end

  -- Affichage de la commande pour le débogage
  print("Executing GStreamer pipeline:")
  print(gst_command)

  -- Exécute la commande GStreamer
  os.execute(gst_command)

  -- Affiche la configuration utilisée
  print("Video capture pipeline executed with the following settings:")
  print("Encoder: " .. encoder_choice)
  print("Resolution: " .. width .. "x" .. height)
  print("Framerate: " .. framerate)
  print("Bitrate: " .. bitrate)
  print("Buffer Size: " .. max_buffer_size .. " bytes")
  print("Queue Buffer Limit: " .. max_queue_buffers)
  print("Output File: " .. output_file)
end

return libgst_lib
