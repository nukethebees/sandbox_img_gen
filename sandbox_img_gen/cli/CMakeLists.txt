add_executable (sandbox_img_gen_cli)

target_sources(sandbox_img_gen_cli 
  PRIVATE
    main.cpp
)

target_include_directories(sandbox_img_gen_cli
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(sandbox_img_gen_cli
  PRIVATE
    cpp_standard
    msvc_settings
    sandbox_img_gen
    ImageMagick::Magick++
)
