file(GLOB days RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*.c)


foreach(day ${days})
    get_filename_component(num ${day} NAME_WE)
    add_executable(day_${num} ${day})
    target_link_libraries(day_${num} intcode)
    
endforeach()
