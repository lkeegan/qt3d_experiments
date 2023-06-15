cmake_minimum_required(VERSION 3.16..3.26)

project(qt3d-experiments VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# need qt6 with qt3d modules
find_package(Qt6 REQUIRED COMPONENTS 3DCore 3DExtras 3DInput 3DRender Core Gui Widgets)

# need sme core to read voxels
find_package(
    sme
    REQUIRED
    CONFIG)

set(CMAKE_AUTOMOC ON)

add_executable(qt3d qt3d.cpp)

target_include_directories(qt3d PRIVATE .)

target_link_libraries(qt3d PRIVATE
    sme::core
	Qt::3DCore
    Qt::3DExtras
    Qt::3DInput
    Qt::3DRender
    Qt::Core
    Qt::Gui
    Qt::Widgets)