workspace "tetris_game"
    configurations {"Debug", "Release"}
    platforms {"Win64"}
    location "bin"
    filter {"platforms:Win64"}
        system "Windows"
        architecture "x64"

project "main"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin/obj/%{cfg.buildcfg}"

    files {"src/*.cpp", "include/*.hpp"}
    includedirs {"include"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"
        optimize "Off"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    filter {}
    buildoptions {
        "-static-libgcc",
        "-static-libstdc++",
        "-static"
    }
    linkoptions {
        "-static-libgcc",
        "-static-libstdc++",
        "-static",
        "-Wl,-Bstatic,--whole-archive",
        "-lwinpthread",
        "-Wl,--no-whole-archive"
    }
    
    flags {"StaticRuntime"}

    links {
        "mingw32",
        "pthread",
        "kernel32",
        "user32",
        "gdi32",
        "comdlg32",
        "advapi32",
        "shell32",
        "ole32",
        "oleaut32",
        "uuid",
        "winmm"
    }