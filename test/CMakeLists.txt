LIEN_SET_EXECUTABLE_OUTPUT_DIR(${PROJECT_BINARY_DIR}/output/bin/lien_tests)

# Prevent flood of GCC 7.1 ABI warnings
if(LIEN_COMPILER_GCC)
    add_definitions(-Wno-psabi)
endif()

add_subdirectory(base)

if(LIEN_BUILD_PARALLEL)
    add_subdirectory(parallel)
endif()

if(LIEN_BUILD_STRUTILS)
    add_subdirectory(strutils)
endif()

if(LIEN_BUILD_IMAGE)
    add_subdirectory(image)
endif()