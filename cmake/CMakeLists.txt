include("${CMAKE_CURRENT_LIST_DIR}/utilities.cmake")

function(define_msvc_settings)
  add_library(msvc_settings INTERFACE)

  set(compile_options
      /Wall
      -wd4710
      -wd4711
      /permissive-
      /WX
      /EHsc  # Enable standard C++ exceptions model
  )
  target_compile_options(msvc_settings INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:${compile_options}>      
  )
endfunction()
consume_setup_fn(define_msvc_settings)

add_library(cpp_standard INTERFACE)
target_compile_features(cpp_standard INTERFACE cxx_std_23)
