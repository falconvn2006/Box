workspace "Box"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Box"
	location "Box"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "bph.h"
	pchsource "Box/src/bph.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"BOX_PLATFORM_WINDOWS",
			"BOX_BUILD_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BOX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BOX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BOX_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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

	links 
	{
		"Box"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"BOX_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BOX_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BOX_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "BOX_DIST"
		optimize "On"