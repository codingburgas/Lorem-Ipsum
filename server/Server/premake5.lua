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
        "../vendor/phc-winner-argon2/include",
        "../vendor/soci/include",
        "/usr/include/postgresql"
    }

    libdirs {
        "../vendor/pistache/lib",
        "/usr/local/pgsql/lib",
	    "../vendor/soci/lib",
        "../vendor/phc-winner-argon2/lib",
        "/usr/local/lib"
    }

    links {
        "pistache",
        "pq",
        "soci_postgresql",
        "soci_core",
        "argon2",
        "soci_empty"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
