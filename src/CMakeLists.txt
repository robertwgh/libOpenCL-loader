
add_library(cl_loader SHARED cl_loader.c)
add_library(cl_loader_static STATIC cl_loader.c)

if(UNIX)
target_link_libraries(cl_loader dl)
target_link_libraries(cl_loader_static dl)
endif(UNIX)

install(TARGETS cl_loader LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX})
install(TARGETS cl_loader LIBRARY DESTINATION ${EXECUTABLE_OUTPUT_PATH}${LIB_SUFFIX})
install(TARGETS cl_loader_static ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX})
