project "Server"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")
 
    postbuildcommands { ("{COPY} /usr/lib/x86_64-linux-gnu/libpq.so.5 ../bin/" .. outputdir .. "/Server") }

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
        "/usr/include/postgresql",
	    "../vendor/jwt-cpp/include"
    }

    libdirs {
        "../vendor/pistache/lib",
	    "../vendor/soci/lib",
        "../vendor/phc-winner-argon2/lib",
        "/usr/local/lib"
    }

    links {
        "pistache",
        "soci_postgresql",
        "soci_core",
        "pq",
        "argon2",
        "crypto",
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
