add_library(sandbox_img_gen)

add_subdirectory("include/sandbox_img_gen")

target_sources(sandbox_img_gen 
  PRIVATE
    src/shapes.cpp
)

target_link_libraries(sandbox_img_gen
  PUBLIC
    ImageMagick::Magick++
    sandbox_img_gen_headers
  PRIVATE
    cpp_standard
    msvc_settings
)

add_subdirectory(cli)

install(
  TARGETS
    sandbox_img_gen
    sandbox_img_gen_cli
    sandbox_img_gen_headers
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static
  FILE_SET HEADERS DESTINATION include
)
