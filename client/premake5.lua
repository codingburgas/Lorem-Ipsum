workspace "Lorem-Ipsum"
    configurations { 
        "Debug", 
        "Release" 
    }

    startproject "Lorem-Ipsum"

    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Core"
include "Lorem-Ipsum"
include "external.lua"