workspace "Server"
    configurations { 
        "Debug", 
        "Release" 
    }

    startproject "Server"

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Server"