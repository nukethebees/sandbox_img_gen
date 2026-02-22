add_executable (sandbox_img_gen)

target_sources(sandbox_img_gen 
  PRIVATE
    "sandbox_img_gen.cpp"
)

target_include_directories(sandbox_img_gen
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(sandbox_img_gen 
  PROPERTIES
    CXX_STANDARD 23
)

target_link_libraries(sandbox_img_gen
  PRIVATE
    msvc_settings
)