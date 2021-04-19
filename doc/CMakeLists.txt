add_subdirectory(userman)

if(TARGET Doxygen::doxygen)
    get_property(DOXYGEN_EXECUTABLE TARGET Doxygen::doxygen PROPERTY IMPORTED_LOCATION)
    
    file(GLOB LIBDEPENDS ${PROJECT_SOURCE_DIR}/lib/*.h)
    file(GLOB SSXDEPENDS ${PROJECT_SOURCE_DIR}/ssx/*.h)
    
    add_custom_command(OUTPUT html/refman/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/lib/Doxyfile > /dev/null
        DEPENDS ${PROJECT_BINARY_DIR}/lib/Doxyfile
        DEPENDS ${PROJECT_BINARY_DIR}/lib/mysql++.h
        DEPENDS ${LIBDEPENDS}
    )
    
    add_custom_command(OUTPUT html/refman/ssx/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/ssx/Doxyfile > /dev/null
        DEPENDS ${PROJECT_BINARY_DIR}/ssx/Doxyfile
        DEPENDS ${SSXDEPENDS}
    )
    
    add_custom_target(doc 
        DEPENDS 
          html/refman/index.html
          html/refman/ssx/index.html
    )
endif()
