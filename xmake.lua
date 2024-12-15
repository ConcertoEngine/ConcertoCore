add_rules("mode.debug", "mode.release", "mode.coverage")
add_rules("plugin.vsxmake.autoupdate")
add_requires("gtest", "enet")

option("unitybuild", { description = "Build using unity build", default = false })

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

if is_mode("coverage") then
	if not is_plat("windows") then
		add_links("gcov")
	end
end

option("tests", { default = false, description = "Enable unit tests"})

target("ConcertoCore")
    set_kind("shared")
    if (is_mode("debug")) then
        set_symbols("debug")
    end
    set_warnings("allextra")
    set_languages("cxx20")
    add_packages("enet", {public = false})
    add_files("Src/**.cpp")
    add_defines("CCT_CORE_BUILD")
    add_cxxflags("cl::/Zc:preprocessor", { public = true })

    add_includedirs("Include", {public = true})
    add_includedirs("Src", {public = false})

    add_headerfiles("Include/(Concerto/Core/*.hpp)",
                    "Include/(Concerto/Core/Math/*.hpp)",
                    "Include/(Concerto/Core/Network/*.hpp)",
                    "Include/(Concerto/Core/Network/ENet/*.hpp)",
                    "Include/(Concerto/Core/Profiler/*.hpp)")

    add_headerfiles("Src/(Concerto/Core/Network/IpAddress/*.hpp)",
                    "Src/(Concerto/Core/Network/Socket/*.hpp)",
                    {install = false})

    add_headerfiles("Include/(Concerto/Core/*.inl)",
                    "Include/(Concerto/Core/Math/*.inl)",
                    "Include/(Concerto/Core/Network/*.inl)",
                    "Include/(Concerto/Core/Network/ENet/*.inl)",
                    "Include/(Concerto/Core/Profiler/*.inl)")
    add_cxxflags("cl::/wd4251")
    if is_plat("windows") then
        add_syslinks("ws2_32", "Kernel32")
    end

    if is_plat("linux") then
        add_syslinks("dl")
    end

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CCT_UNITY_BUILD_ID"})
    end

if has_config("tests") then
    includes("Tests/xmake.lua")
end