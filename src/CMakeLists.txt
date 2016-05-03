
add_library(cl_loader SHARED cl_loader.c)
add_library(cl_loader_static STATIC cl_loader.c)

if(UNIX)
target_link_libraries(cl_loader dl)
target_link_libraries(cl_loader_static dl)
endif(UNIX)

#message(STATUS "LIBRARY_OUTPUT_PATH = ${LIBRARY_OUTPUT_PATH}")
#message(STATUS "EXECUTABLE_OUTPUT_PATH = ${EXECUTABLE_OUTPUT_PATH}")
install(TARGETS cl_loader cl_loader_static  
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX} 
        ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX})
