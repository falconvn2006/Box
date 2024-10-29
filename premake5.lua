workspace "Box"
    architecture "x64"

    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}.%{cfg.system}.%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Box/vendor/GLFW/include"
IncludeDir["Glad"] = "Box/vendor/Glad/include"
IncludeDir["ImGui"] = "Box/vendor/imgui/"

include "Box/vendor/GLFW"
include "Box/vendor/Glad"
include "Box/vendor/imgui"

project "Box"
    location "Box"
    kind "SharedLib"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "boxpch.h"
    pchsource "Box/src/boxpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "BOX_PLATFORM_WINDOWS",
            "BOX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines "BOX_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "BOX_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "BOX_DIST"
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Box/vendor/spdlog/include",
        "Box/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "BOX_PLATFORM_WINDOWS",
        }

    links
    {
        "Box"
    }

    filter "configurations:Debug"
        defines "BOX_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "BOX_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "BOX_DIST"
        runtime "Release"
        optimize "On"
