-- premake5.lua
workspace "slam"
   configurations { "Debug", "Release" }

project "slam"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"

   files { "src/*.cpp", "slam/**.cpp", "slam/**.hpp", "slam/**.c", "slam/**.h" }

   filter "system:windows" 
      includedirs { "slam/ext/SDL/include" }
      libdirs { "slam/ext/SDL/lib" }
   filter {  }

   links { "SDL3", "m", }



   filter "configurations:Debug"
      defines { "DEBUG" }
      optimize "Full"
      linktimeoptimization "On"
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "Full"
      linktimeoptimization "On"
      optimize "On"