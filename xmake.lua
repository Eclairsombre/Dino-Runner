add_rules("mode.debug", "mode.release")

add_requires("libsdl", "libsdl_ttf", "libsdl_image", "libsdl_mixer")

target("DinoRunner")
    set_kind("binary")

    add_files("src/**.cpp")

    set_rundir("$(projectdir)")

    -- Libraries
    add_packages("libsdl", "libsdl_ttf", "libsdl_image", "libsdl_mixer")