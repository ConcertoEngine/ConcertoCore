add_requires('gtest', 'nlohmann_json 3.11.2', 'enet')
add_rules("mode.debug")

option("unitybuild", { description = "Build using unity build", default = false })

target("ConcertoCore")
    set_kind("shared")
    set_symbols("debug")
    set_warnings("allextra")
    set_languages("cxx20")

    add_packages('nlohmann_json', {public = true})
    add_packages('enet', {public = false})
    add_files('Src/**.cpp')
    add_defines("CONCERTO_BUILD")

    add_includedirs('Include',
                    'Include/Concerto',
                    'Include/Concerto/Core',
                    'Include/Concerto/Core/Math',
                    'Include/Concerto/Core/Network',
                    'Include/Concerto/Core/Network/Enet',
                    'Src/Concerto/Core/Network/IpAddress',
                    'Src/Concerto/Core/Network/Socket', {public = true})

    add_headerfiles('Include/(Concerto/*.hpp)',
                    'Include/(Concerto/Core/*.hpp)',
                    'Include/(Concerto/Core/Math/*.hpp)',
                    'Include/(Concerto/Core/Network/*.hpp)',
                    'Include/(Concerto/Core/Network/Enet/*.hpp)')

    add_headerfiles('Include/(Concerto/*.inl)',
                    'Include/(Concerto/Core/*.inl)',
                    'Include/(Concerto/Core/Math/*.inl)',
                    'Include/(Concerto/Core/Network/*.inl)',
                    'Include/(Concerto/Core/Network/Enet/*.inl)')

    if is_plat("windows") then
        add_syslinks("ws2_32")
    end

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
    end

target("ConcertoCoreTests")
    set_kind("binary")
    set_symbols("debug")
    set_warnings("allextra")
    set_languages("cxx20")

    add_files('Tests/*.cpp')
    add_packages('gtest')
    add_deps('ConcertoCore')

    if has_config("unitybuild") then
        add_rules("c++.unity_build", {batchsize = 12, uniqueid = "CONCERTO_UNITY_BUILD_ID"})
    end

    after_build(function(target)
        print("Copying resources...")
        local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
        os.cp("./goodConfig.json", binaryPath .. "/goodConfig.json")
        print("Copying resources... Done !")
    end)
