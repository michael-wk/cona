#engine core
add_library(engine_core STATIC 
    core/application.c
    core/datamodel.c
    core/cona_math.c
    core/renderer.c
    core/error.c

    data/scene.c
    data/node.c

    dstructs/hashtab.c
)
target_include_directories(engine_core PUBLIC core_include)
target_include_directories(engine_core PUBLIC data_include)
target_include_directories(engine_core PUBLIC dstructs_include)
target_link_libraries(engine_core PUBLIC SDL3::SDL3)
