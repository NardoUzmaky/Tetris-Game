workspace "tetris_game"
    configurations {"Debug", "Release"}
    platforms {"Win64"}
    filter {"platforms:Win64"}
        system "Windows"
        architecture "x64"

project "main"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin"
    objdir "bin/%{cfg.buildcfg}"

    files {"src/*.cpp", "include/*.hpp"}

    includedirs {"include"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"
    filter "action:gmake2"
        cppdialect "gnu++20"
        