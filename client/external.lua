project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"
    location "vendor/imgui"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "vendor/imgui/imconfig.h",
        "vendor/imgui/imgui.cpp",
        "vendor/imgui/imgui_demo.cpp",
        "vendor/imgui/imgui_draw.cpp",
        "vendor/imgui/imgui.h",
        "vendor/imgui/imgui_internal.h",
        "vendor/imgui/imgui_tables.cpp",
        "vendor/imgui/imgui_widgets.cpp",
        "vendor/imgui/imstb_rectpack.h",
        "vendor/imgui/imstb_textedit.h",
        "vendor/imgui/imstb_truetype.h",

        "vendor/rlImGui/rlImGui.cpp",
        "vendor/rlImGui/rlImGui.h",
        "vendor/rlImGui/imgui_impl_raylib.h",
    }

    includedirs {
        "vendor/imgui",
        "vendor/rlImGui",
        "vendor/raylib/include"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

project "Box2D"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    systemversion "latest"
    location "vendor/box2d"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "vendor/box2d/src/**.h",
        "vendor/box2d/src/**.cpp",
        "vendor/box2d/include/**.h"
    }

    includedirs {
        "vendor/box2d/include"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"