project "deferred_renderer"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    
    files
    {
		"src/**.h",
		"src/**.cpp",
		"vendor/imgui-docking/**.h",
		"vendor/imgui-docking/**.cpp"
    }

    includedirs
    {
      "src",
	  "vendor/imgui-docking",
	  "%{IncludeDir.assimp}",
	  "%{IncludeDir.fmt}",
	  "%{IncludeDir.glad}",
	  "%{IncludeDir.glfw}",
	  "%{IncludeDir.glm}",
	  "%{IncludeDir.rapidjson}",
	  "%{IncludeDir.stb}"
    }
	
    links
    {
      "%{Library.opengl}",
	  "%{Library.assimp}",
	  "%{Library.glfw}"
    }
	
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
    debugdir("$(SolutionDir)/Editor")

    filter "system:windows"
		systemversion "latest"
		postbuildcommands
		{
			"{COPY} \"%{cfg.buildtarget.relpath}\" \"%{wks.location}Editor\""
		}

    filter "configurations:Debug"
		defines "EM_DEBUG"
		runtime "Debug"
		symbols "On"

    filter "configurations:Release"
		defines "EM_RELEASE"
		runtime "Release"
		optimize "On"
		symbols "On"

    filter "configurations:Dist"
      defines "EM_DIST"
      runtime "Release"
      optimize "On"
      symbols "Off"