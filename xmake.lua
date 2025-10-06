add_rules("mode.debug", "mode.release", "mode.coverage")
add_rules("plugin.vsxmake.autoupdate")

option("unitybuild", { description = "Build using unity build", default = false })
option("tests", { description = "Enable unit tests", default = false})
option("examples", { description = "Enable examples", default = false})
option("static", { description = "Build static library", default = false })
option("override_runtime", { description = "Override vs runtime to MD in release and MDd in debug", default = true })
option("asserts", { description = "Enable asserts", default = false })
option("enet", { description = "Enable ENet support", default = true })

if is_plat("windows") and has_config("override_runtime") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

if is_mode("coverage") then
	if not is_plat("windows") then
		add_links("gcov")
	end
end

if has_config("enet") then
    add_requires("enet", {configs = {shared = false}})
end

function add_files_to_target(p, hpp_as_files, install)
    for _, dir in ipairs(os.filedirs(p)) do
        relative_dir = path.relative(dir, "Src/")
        if os.isdir(dir) then
            add_files(path.join("Src", relative_dir, "*.cpp"))
            if hpp_as_files then
                add_files(path.join("Src", relative_dir, "*.hpp"))
            end
            install = path.basename(dir) ~= "Private"
            add_headerfiles(path.join("Src", "(" .. relative_dir .. "/*.hpp)"), {install = install})
            add_headerfiles(path.join("Src", "(" .. relative_dir .. "/*.inl)"), {install = install})
        else
            local ext = path.extension(relative_dir)
            if ext == ".hpp" or ext == ".inl" then
                add_headerfiles(path.join("Src", "(" .. relative_dir .. ")"), {install = install})
            elseif ext == ".cpp" then
                add_files(path.join("Src", relative_dir))
            end
        end
    end
end

target("concerto-core")
    set_kind("$(kind)")

    if is_kind("static") then
        add_defines("CCT_CORE_LIB_STATIC", {public = true})
    end

    if is_mode("debug") then
        set_symbols("debug")
    end

    set_warnings("allextra")
    set_languages("cxx20")
    if has_config("enet") then
        add_packages("enet", {public = true})
        add_defines("CCT_ENABLE_ENET")
    end
    add_files("Src/Concerto/Core/**.cpp")
    add_defines("CCT_CORE_BUILD")
    add_cxxflags("cl::/Zc:preprocessor", { public = true })
    add_includedirs("Src", {public = true}) 
    add_files_to_target("Src/Concerto/Core/**", false, true)

    add_cxxflags("cl::/wd4251")

    if is_plat("windows", "mingw") then
        add_syslinks("ws2_32", "Kernel32")
    end

    if is_plat("linux") then
        add_syslinks("dl")
    end

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CCT_UNITY_BUILD_ID"})
    end

    if has_config("asserts") then
        add_defines("CCT_ENABLE_ASSERTS")
    end
target_end()

if has_config("tests") then
    includes("Examples/xmake.lua")
end

if has_config("tests") then
    add_requires("gtest")
    
    target("concerto-core-dummy")
        set_kind("shared")
        set_languages("cxx20")
        set_warnings("none")
        add_deps("concerto-core")
        on_config(function(target)
            local dummy_file = path.join(target:autogendir(), "dummy.cpp")
            target:add("files", dummy_file)
            io.writefile(dummy_file, [[
#include <Concerto/Core/Types/Types.hpp>
extern "C" {
    void CCT_EXPORT Dummy() {}
    int CCT_EXPORT DummyInt() { return 42;}
    int CCT_EXPORT Increment(int v) { return v + 1;}
    int CCT_EXPORT GlobalInt = 42;
}
]])
        end)

    target("concerto-core-tests")
        add_deps("concerto-core", "concerto-core-dummy")
        set_kind("binary")
        if (is_mode("debug")) then
            set_symbols("debug")
        end
        set_warnings("allextra")
        set_languages("cxx20")

        add_files("Src/Tests/*.cpp")
        add_packages("gtest")

        if has_config("unitybuild") then
            add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
        end

        if is_plat("linux") then
            add_syslinks("dl")
        end

        add_cxxflags("cl::/wd4251") -- needs to have dll-interface to be used by clients of
end
