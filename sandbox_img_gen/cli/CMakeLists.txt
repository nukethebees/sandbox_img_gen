add_executable (sandbox_img_gen_cli)

target_sources(sandbox_img_gen_cli 
  PRIVATE
    main.cpp
)

target_compile_definitions(sandbox_img_gen_cli
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_DECLARE_NONSTDC_NAMES=1>
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1>
)

target_include_directories(sandbox_img_gen_cli
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(sandbox_img_gen_cli
  PRIVATE
    c_standard
    cpp_standard
    msvc_settings
    TBB::tbb
    sandbox_img_gen
)
