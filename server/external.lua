
project "pistache"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"
    location "vendor/pistache"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "vendor/pistache/include/**.h",
        "vendor/pistache/src/**.cc",
        "vendor/pistache/src/**.h"
    }

    includedirs {
        "vendor/pistache/include",
        "vendor/pistache/src",
        "vendor/date"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"