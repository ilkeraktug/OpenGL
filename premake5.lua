workspace "OpenGL"
	architecture "x64"
	startproject "OpenGL"

	configurations 
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glad"] =	"OpenGL/vendor/glad/include" 
IncludeDir["GLFW"] =	"OpenGL/vendor/GLFW/include" 
IncludeDir["glm"] =		"OpenGL/vendor/glm" 
IncludeDir["imgui"] =   "OpenGL/vendor/imgui" 
IncludeDir["stb"] =		"OpenGL/vendor/stb" 
IncludeDir["assimp"] =  "OpenGL/vendor/assimp/include" 

include "OpenGL/vendor/glad"
include "OpenGL/vendor/GLFW"
--include "OpenGL/vendor/imgui"

	project "OpenGL"
		location "OpenGL"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/imgui/**.h",
		"%{prj.name}/vendor/imgui/**.cpp"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.assimp}"
	}

	links
	{
		"glad",
		"GLFW",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines "GLFW_INCLUDE_NONE"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		runtime "Release"
		optimize "on"