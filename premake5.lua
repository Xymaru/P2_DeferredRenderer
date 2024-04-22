workspace "deferred_renderer"
    architecture "x64"
    configurations { "Debug", "Release", "Dist" }
    startproject "deferred_renderer"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "dependencies.lua"
include "deferred_renderer"