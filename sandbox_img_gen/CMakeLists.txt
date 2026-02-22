add_library(sandbox_img_gen)

target_sources(sandbox_img_gen 
  PRIVATE
    src/shapes.cpp
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    TYPE HEADERS
    FILES
      include/sandbox_img_gen/shapes.hpp
)

target_include_directories(sandbox_img_gen
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(sandbox_img_gen
  PUBLIC
    ImageMagick::Magick++
  PRIVATE
    cpp_standard
    msvc_settings
)

add_subdirectory(cli)

install(TARGETS sandbox_img_gen sandbox_img_gen_cli
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        FILE_SET HEADERS DESTINATION include
)
