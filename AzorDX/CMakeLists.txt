cmake_minimum_required(VERSION 3.0)
project(Test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cc")
file(GLOB LIB_FILES "${PROJECT_SOURCE_DIR}/lib/*.a")
file(GLOB DLL_FILES "${PROJECT_SOURCE_DIR}/dll/*.dll")
file(GLOB TEXTURE_FILES "${PROJECT_SOURCE_DIR}/resources/textures/*.*")
file(GLOB SOUND_FILES "${PROJECT_SOURCE_DIR}/resources/sounds/*.*")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/resources")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/resources/sounds")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/resources/textures")
file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/resources/fonts")

#copy dlls
foreach(dll_file ${DLL_FILES})
    configure_file(${dll_file} ${PROJECT_SOURCE_DIR}/bin COPYONLY) 
endforeach(dll_file)

#copy textures
foreach(texture_file ${TEXTURE_FILES})
    configure_file(${texture_file} ${PROJECT_SOURCE_DIR}/bin/resources/textures COPYONLY) 
endforeach(texture_file)

#copy sounds
foreach(sound_file ${SOUND_FILES})
    configure_file(${sound_file} ${PROJECT_SOURCE_DIR}/bin/resources/sounds COPYONLY) 
endforeach(sound_file)

#copy .config
configure_file("${PROJECT_SOURCE_DIR}/.config" "${PROJECT_SOURCE_DIR}/bin" COPYONLY)

#add_executable(azordx ${SRC_FILES})
add_library(azordx STATIC ${SRC_FILES})
target_link_libraries(azordx "libd3d9.a" "libd3dx9.a" "libwinmm.a" "libdxerr9.a" "libdxguid.a" "libdinput8.a" ${LIB_FILES})