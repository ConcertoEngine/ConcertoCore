target("c-api-example")
    set_languages("c99")
    set_kind("binary")
    add_files("CApiExample/main.c")
    add_deps("concerto-core")