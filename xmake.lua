add_requires('gtest', 'nlohmann_json 3.11.2')
add_rules("mode.debug")

target("ConcertoCore")
    set_kind("shared")
    set_symbols("debug")
    set_warnings("everything")
    set_languages("cxx20")
    add_packages('nlohmann_json', { public = true })
    add_includedirs('Include', 'Include/Concerto','Include/Concerto/Core', 'Include/Concerto/Core/Math')
    add_files('Src/*.cpp', 'Src/Concerto/Core/*.cpp', 'Src/Math/*.cpp')
    add_defines("CONCERTO_BUILD")
    add_headerfiles('Include/(Concerto/*.hpp)','Include/(Concerto/Core/*.hpp)', 'Include/(Concerto/Core/Math/*.hpp)')
    add_headerfiles('Include/(Concerto/*.inl)','Include/(Concerto/Core/*.inl)', 'Include/(Concerto/Core/Math/*.inl)')

target("ConcertoCoreTests")
    set_kind("binary")
    set_symbols("debug")
    set_warnings("everything")
    set_languages("cxx20")
    add_files('Tests/*.cpp')
    add_packages('gtest')
    add_packages('nlohmann_json')
    add_includedirs('Include', 'Include/Concerto','Include/Concerto/Core', 'Include/Concerto/Core/Math')
    add_files('Tests/*.cpp', 'Src/Concerto/Core/*.cpp', 'Src/Concerto/Core/Math/*.cpp')
    add_defines("CONCERTO_BUILD")
    after_build(function(target)
            print("Copying resources...")
            local binaryPath = "$(buildir)/$(plat)/$(arch)/$(mode)"
            os.cp("./goodConfig.json", binaryPath .. "/goodConfig.json")
            print("Copying resources... Done !")
    end)
