#engine
add_executable(engine src/main.c)
target_link_libraries(engine PRIVATE game)
set_target_properties(engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(engine PROPERTIES OUTPUT_NAME "cona")

add_custom_command(TARGET engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:engine>
)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  add_custom_target(fix_compile_commands ALL
    COMMAND wsl bash -c "cd \"$$(wslpath '${CMAKE_SOURCE_DIR}')\" && bash fix-compile-commands.sh"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMENT "Fixing compile_commands.json paths for WSL clangd"
  )
endif()
