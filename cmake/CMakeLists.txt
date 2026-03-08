include("${CMAKE_CURRENT_LIST_DIR}/utilities.cmake")

function(define_msvc_settings)
  add_library(msvc_settings INTERFACE)

  set(compile_options_base
      /EHsc  # Enable standard C++ exceptions model
      /fpcvt:IA
      /permissive-
      /Wall
      -wd4514
      -wd4710
      -wd4711
      -wd5045
      -wd4189 # Unused variables
      /WX
  )

  set(compile_options_debug ${compile_options_base})

  set(compile_options_release ${compile_options_base})
  list(APPEND compile_options_release
    /Zi
    /dynamicdeopt
  )

  target_compile_options(msvc_settings INTERFACE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:${compile_options_debug}>      
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:${compile_options_release}>      
  )
endfunction()
consume_setup_fn(define_msvc_settings)

add_library(cpp_standard INTERFACE)
target_compile_features(cpp_standard INTERFACE cxx_std_23)

add_library(c_standard INTERFACE)
target_compile_features(c_standard INTERFACE c_std_17)
