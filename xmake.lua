add_requires('gtest', 'enet')
add_rules("mode.debug", "mode.release")

option("unitybuild", { description = "Build using unity build", default = false })

if is_plat("windows") then
    set_runtimes(is_mode("debug") and "MDd" or "MD")
end

target("ConcertoCore")
    set_kind("shared")
    if (is_mode('debug')) then
        set_symbols("debug")
    end
    set_warnings("allextra")
    set_languages("cxx20")
    add_packages('enet', {public = false})
    add_files('Src/**.cpp')
    add_defines("CONCERTO_CORE_BUILD")
    add_cxxflags("cl::/Zc:preprocessor", { public = true })

    add_includedirs('Include',
                    'Include/Concerto',
                    'Include/Concerto/Core',
                    'Include/Concerto/Core/Math',
                    'Include/Concerto/Core/Network',
                    'Include/Concerto/Core/Network/ENet',
                    'Src/Concerto/Core/Network/IpAddress',
                    'Src/Concerto/Core/Network/Socket', {public = true})

    add_headerfiles('Include/(Concerto/*.hpp)',
                    'Include/(Concerto/Core/*.hpp)',
                    'Include/(Concerto/Core/Math/*.hpp)',
                    'Include/(Concerto/Core/Network/*.hpp)',
                    'Include/(Concerto/Core/Network/ENet/*.hpp)')

    add_headerfiles('Include/(Concerto/*.inl)',
                    'Include/(Concerto/Core/*.inl)',
                    'Include/(Concerto/Core/Math/*.inl)',
                    'Include/(Concerto/Core/Network/*.inl)',
                    'Include/(Concerto/Core/Network/ENet/*.inl)')
    add_cxxflags("cl::/wd4251")
    if is_plat("windows") then
        add_syslinks("ws2_32", "Kernel32")
    end

    if is_plat("linux") then
        add_syslinks("dl")
    end

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
    end

includes("Tests/xmake.lua")