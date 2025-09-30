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
    add_files("Src/Concerto/**.cpp")
    add_defines("CCT_CORE_BUILD")
    add_cxxflags("cl::/Zc:preprocessor", { public = true })

    add_includedirs("Include", {public = true})
    add_includedirs("Src", {public = false})

    add_headerfiles("Include/(Concerto/Core/*.hpp)",
                    "Include/(Concerto/Core/Math/*.hpp)",
                    "Include/(Concerto/Core/Network/*.hpp)",
                    "Include/(Concerto/Core/Network/ENet/*.hpp)",
                    "Include/(Concerto/Core/*.h)")

    add_headerfiles("Src/(Concerto/Core/Network/IpAddress/*.hpp)",
                    "Src/(Concerto/Core/Network/Socket/*.hpp)",
                    {install = false})

    add_headerfiles("Include/(Concerto/Core/*.inl)",
                    "Include/(Concerto/Core/Math/*.inl)",
                    "Include/(Concerto/Core/Network/*.inl)",
                    "Include/(Concerto/Core/Network/ENet/*.inl)",
                    "Include/(Concerto/Core/Profiler/*.inl)")
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

if has_config("tests") then
    includes("Examples/xmake.lua")
end

if has_config("tests") then
    add_requires("gtest")
    
    target("concerto-core-dummy")
        set_kind("shared")
        set_languages("cxx20")
        add_files("$$(builddir)/$(plat)/$(arch)/dummy.cpp")
        set_warnings("none")
        on_load(function(target)
            if is_host("windows") then
                io.writefile("$(builddir)/$(plat)/$(arch)/dummy.cpp", [[
                extern "C" {
                    __declspec(dllexport) void __cdecl Dummy() {}
                    __declspec(dllexport) int __cdecl DummyInt() { return 42;}
                    __declspec(dllexport) int __cdecl Increment(int v) { return v + 1;}
                    __declspec(dllexport) int __cdecl GlobalInt = 42;
                }
                ]])
            elseif is_host("linux") or  is_host("macos") then
                io.writefile("$(builddir)/$(plat)/$(arch)/dummy.cpp", [[
                extern "C" {
                    void Dummy() {}
                    int DummyInt() { return 42;}
                    int Increment(int v) { return v + 1;}
                    int GlobalInt = 42;
                }
                ]])
            end
        end)

    target("concerto-core-tests")
        add_deps("concerto-core-dummy", "concerto-core")
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
