cmake_minimum_required (VERSION 4.1)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("sandbox_img_gen")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(ImageMagick 
  COMPONENTS
    Magick++
    MagickCore
)
find_package(tbb CONFIG REQUIRED)

add_subdirectory(cmake)

add_subdirectory ("sandbox_img_gen")

