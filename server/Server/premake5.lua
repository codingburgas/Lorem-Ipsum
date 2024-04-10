project "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "../vendor/pistache/include",
        "../vendor/rapidjson/include",
        "../vendor/pgfe/src",
        "/usr/include/postgresql"
    }

    libdirs {
        "../vendor/pistache/lib",
        "/usr/local/pgsql/lib"
    }

    links {
        "pistache",
        "pq"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
