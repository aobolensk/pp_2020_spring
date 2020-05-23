get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)

if ( USE_SEQ )
    set(ProjectId "${ProjectId}_seq")
    project( ${ProjectId} )
    message( STATUS "-- " ${ProjectId} )

    file(GLOB_RECURSE header_files "*.h")
    file(GLOB_RECURSE source_files "*.cpp")
    set(PACK_LIB "${ProjectId}_lib")
    add_library(${PACK_LIB} STATIC ${header_files} ${source_files})

    add_executable(${ProjectId} ${source_files})

    target_link_libraries(${ProjectId} ${PACK_LIB})
    target_link_libraries(${ProjectId} gtest gtest_main)

    enable_testing()
    add_test(NAME ${ProjectId} COMMAND ${ProjectId})

    if (USE_OPENCV)
      add_definitions(-DOPENCV=1)
      find_package( OpenCV REQUIRED )
      include_directories("${CMAKE_CURRENT_SOURCE_DIR}" ${OpenCV_INCLUDE_DIRS})
      target_link_libraries(${ProjectId} ${OpenCV_LIBS})
    endif( USE_OPENCV)

else( USE_SEQ )
    message( STATUS "-- ${ProjectId} - NOT BUILD!"  )
endif( USE_SEQ )

