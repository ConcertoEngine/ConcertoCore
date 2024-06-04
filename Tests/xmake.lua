target("ConcertoCoreTestsDummyLib")
    set_kind("shared")
    set_languages("cxx20")
    add_files("$(buildir)/$(plat)/$(arch)/dummy.cpp")
    set_warnings("none")
    on_load(function(target)
        if is_host("windows") then
            io.writefile("$(buildir)/$(plat)/$(arch)/dummy.cpp", [[
            extern "C" {
                __declspec(dllexport) void __cdecl Dummy() {}
                __declspec(dllexport) int __cdecl DummyInt() { return 42;}
				__declspec(dllexport) int __cdecl Increment(int v) { return v + 1;}
                __declspec(dllexport) int __cdecl GlobalInt = 42;
            }
            ]])
        elseif is_host("linux") or  is_host("macos") then
            io.writefile("dummy.cpp", [[
            extern "C" {
                void Dummy() {}
                int DummyInt() { return 42;}
				int Increment(int v) { return v + 1;}
                int GlobalInt = 42;
            }
            ]])
        end
    end)

target("ConcertoCoreTests")
    add_deps("ConcertoCoreTestsDummyLib")
    set_kind("binary")
    if (is_mode('debug')) then
        set_symbols("debug")
    end
    set_warnings("allextra")
    set_languages("cxx20")

    add_files('*.cpp')
    add_packages('gtest')
    add_deps('ConcertoCore')

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
    end

     if is_plat("linux") then
        add_syslinks("dl")
    end

    after_build(function(target)
        print("Copying resources...")
        local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
        os.cp("./goodConfig.json", binaryPath .. "/goodConfig.json")
        print("Copying resources... Done !")
    end)
