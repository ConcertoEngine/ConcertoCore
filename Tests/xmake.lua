add_requires("gtest")

target("concerto-core-dummy")
    set_kind("shared")
    set_languages("cxx20")
    add_files("$(buildir)/$(plat)/$(arch)/dummy.cpp")
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

    add_files("*.cpp")
    add_packages("gtest")

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
    end

    if is_plat("linux") then
        add_syslinks("dl")
    end

    add_cxxflags("cl::/wd4251") -- needs to have dll-interface to be used by clients of
