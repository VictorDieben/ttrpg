
#
cmake_minimum_required (VERSION 3.13)

message("TtrpgApp source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
 
add_executable (TtrpgApp 
    "ttrpg_app.cpp" 
)

if (MSVC)
  add_compile_options(/bigobj)
else ()
  add_compile_options(-Wa,-mbig-obj)
endif () 


target_include_directories(TtrpgApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(TtrpgApp
    PRIVATE 
        TtrpgLib 
)  