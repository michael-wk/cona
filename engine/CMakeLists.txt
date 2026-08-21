#engine
add_executable(engine src/main.c)
target_link_libraries(engine PRIVATE game)
set_target_properties(engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(engine PROPERTIES OUTPUT_NAME "cona")
