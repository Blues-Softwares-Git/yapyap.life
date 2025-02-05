
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
