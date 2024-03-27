project "Lorem-Ipsum"
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
        "../vendor/raylib/include",
        "../vendor/imgui",
        "../Core/src",
        "../vendor/glm",
        "../vendor/rlImGui",
        "../vendor/entt",
        "../vendor/box2d/include"
    }

    libdirs {
        "../vendor/raylib/lib"
    }

    postbuildcommands { ("{COPY} ..\\vendor\\raylib\\lib\\raylib.dll ..\\bin\\" .. outputdir .. "\\Lorem-Ipsum") }

    links {
        "Core",
        "raylibdll",
        "ImGui",
        "Box2D"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
