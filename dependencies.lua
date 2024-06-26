VendorDir = "../vendor";

IncludeDir = {}
IncludeDir["assimp"]	= "%{VendorDir}/assimp/include/"
IncludeDir["fmt"]		= "%{VendorDir}/fmt/"
IncludeDir["glad"]		= "%{VendorDir}/glad/include/"
IncludeDir["glfw"]		= "%{VendorDir}/glfw/include/"
IncludeDir["glm"]		= "%{VendorDir}/glm/include/"
IncludeDir["rapidjson"] = "%{VendorDir}/rapidjson/"
IncludeDir["stb"]		= "%{VendorDir}/stb/"

LibraryDir={}
LibraryDir["assimp"]	= "%{VendorDir}/assimp/lib/windows"
LibraryDir["glfw"]		= "%{VendorDir}/glfw/lib-vc2019"

Library={}
Library["opengl"]		= "opengl32.lib"
Library["assimp"]		= "%{LibraryDir.assimp}/assimp.lib"
Library["glfw"]			= "%{LibraryDir.glfw}/glfw3.lib"