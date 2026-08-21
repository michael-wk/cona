#engine core
add_library(engine_core STATIC src/application.c)
target_include_directories(engine_core PUBLIC include)
target_link_libraries(engine_core PUBLIC SDL3::SDL3)
