
add_library(opencl_loader SHARED opencl_loader.cpp)
add_library(opencl_loader_static STATIC opencl_loader.cpp)

if(UNIX)
target_link_libraries(opencl_loader dl)
target_link_libraries(opencl_loader_static dl)
endif(UNIX)

#message(STATUS "LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
#message(STATUS "EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
install(TARGETS opencl_loader opencl_loader_static  
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX} 
        ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX})
