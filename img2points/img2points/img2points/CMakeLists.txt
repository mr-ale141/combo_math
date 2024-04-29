# CMakeList.txt : CMake project for img2points, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (img2points "img2points.cpp" "img2points.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET img2points PROPERTY CXX_STANDARD 20)
endif()

set(OpenCV_DIR "C:/Tools/opencv/build" CACHE PATH "C:/Tools/opencv/build/install")
find_package(OpenCV REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
