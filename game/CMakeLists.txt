add_library(game STATIC src/game.c)
target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC engine_core)


