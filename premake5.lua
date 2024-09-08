workspace "tetris_game"
    configurations {"Debug", "Release"}
    platforms {"Win64", "Linux", "MacOS"}
    location "bin"

    filter {"platforms:Win64"}
        system "Windows"
        architecture "x64"

    filter {"platforms:Linux"}
        system "Linux"
        architecture "x64"

    filter {"platforms:MacOS"}
        system "MacOS"
        architecture "x64"

project "main"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}-%{cfg.platform}"
    objdir "bin/obj/%{cfg.buildcfg}-%{cfg.platform}"

    files {"src/*.cpp", "include/*.hpp"}
    includedirs {"include"}

    staticruntime "On"

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
    filter "action:gmake2"
        cppdialect "gnu++20"
   