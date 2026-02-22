add_library(sandbox_img_gen)

target_sources(sandbox_img_gen 
  PRIVATE
    src/shapes.cpp
)

target_include_directories(sandbox_img_gen
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(sandbox_img_gen
  PRIVATE
    cpp_standard
    msvc_settings
    ImageMagick::Magick++
)

add_subdirectory(cli)

install(TARGETS sandbox_img_gen sandbox_img_gen_cli
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
