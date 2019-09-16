# add_custom_target(doc 

if(TARGET Doxygen::doxygen)
    get_property(DOXYGEN_EXECUTABLE TARGET Doxygen::doxygen PROPERTY IMPORTED_LOCATION)
    
    add_custom_command(OUTPUT html/refman/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/lib/Doxyfile
        DEPENDS ${PROJECT_BINARY_DIR}/lib/Doxyfile
    )
    
    add_custom_command(OUTPUT html/refman/ssx/index.html
        COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/ssx/Doxyfile
        DEPENDS ${PROJECT_BINARY_DIR}/ssx/Doxyfile
    )
    
    add_custom_target(doc 
        DEPENDS 
          html/refman/index.html
          html/refman/ssx/index.html
    )
endif()
