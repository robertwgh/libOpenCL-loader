
SET(MAJOR_VERSION 1)
SET(MINOR_VERSION 0)
SET(MICRO_VERSION 0)


if( BUILD_SHARED_LIBRARY )
  add_library( cl_loader SHARED cl_loader.c )
else()
  add_library( cl_loader cl_loader.c )
endif()

set_target_properties(cl_loader
        PROPERTIES
        OUTPUT_NAME cl_loader
        CLEAN_DIRECT_OUTPUT 1
        VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${MICRO_VERSION}"
        SOVERSION "${MAJOR_VERSION}"
    )

if(UNIX)
target_link_libraries( cl_loader dl )
endif(UNIX)

install(TARGETS cl_loader 
    LIBRARY DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX}
    ARCHIVE DESTINATION ${LIBRARY_OUTPUT_PATH}${LIB_SUFFIX})
