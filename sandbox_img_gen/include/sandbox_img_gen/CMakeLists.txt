add_library(sandbox_img_gen_headers INTERFACE)

target_sources(sandbox_img_gen_headers 
  INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    TYPE HEADERS
    FILES
      shapes.hpp
      dimension.hpp
      static_pmr_vector.hpp
)
