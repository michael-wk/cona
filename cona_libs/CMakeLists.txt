#cona_libs
add_library(cona_libs STATIC 
    src/carrays.c
);
target_include_directories(cona_libs PUBLIC include);
target_link_libraries(cona_libs PUBLIC engine_core);
