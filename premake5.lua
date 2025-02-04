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
IncludeDir["ImGui"] = "Box/vendor/imgui"
IncludeDir["glm"] = "Box/vendor/glm"
IncludeDir["stb_image"] = "Box/vendor/stb_image"

include "Box/vendor/GLFW"
include "Box/vendor/Glad"
include "Box/vendor/imgui"

project "Box"
    location "Box"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "boxpch.h"
    pchsource "Box/src/boxpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
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
        systemversion "latest"

        defines
        {
            "BOX_PLATFORM_WINDOWS",
            "BOX_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "BOX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BOX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "BOX_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

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
        "Box/vendor/",
        "Box/src",
        "%{IncludeDir.glm}"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "BOX_PLATFORM_WINDOWS",
        }

    links
    {
        "Box",
        --"ImGui"
    }

    filter "configurations:Debug"
        defines "BOX_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "BOX_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        kind "WindowedApp"
        defines "BOX_DIST"
        runtime "Release"
        optimize "on"
        symbols "off"
