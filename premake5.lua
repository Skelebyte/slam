-- premake5.lua
workspace "slam"
   configurations { "Debug", "Release" }

project "slam"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/*.cpp", "slam/**.cpp", "slam/**.hpp", "slam/**.c", "slam/**.h" }

    links { "SDL3", "m", }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"