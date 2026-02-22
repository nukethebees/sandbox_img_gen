cmake_minimum_required (VERSION 3.28)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("sandbox_img_gen")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include("cmake/utilities.cmake")

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

find_package(ImageMagick
  COMPONENTS
    Magick++
    MagickCore
)

print_var(ImageMagick_FOUND)
print_var(ImageMagick_VERSION)
print_var(ImageMagick_LIBRARIES)
print_var(ImageMagick_INCLUDE_DIRS)
print_var(ImageMagick_COMPILE_OPTIONS)
print_var(ImageMagick_LIBRARIES)

add_subdirectory ("sandbox_img_gen")
