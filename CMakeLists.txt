cmake_minimum_required(VERSION 3.28)
project(dofus_test)

set(CMAKE_CXX_STANDARD 23)

find_path(DETOURS_INCLUDE_DIRS "detours/detours.h")
find_library(DETOURS_LIBRARY detours REQUIRED)


add_library(dofus_test SHARED dll/src/main.cpp
        dll/src/HookEngine.cpp
        dll/src/ChatMessagePacket.cpp
        dll/src/PlayerInventoryPacket.cpp
        dll/src/MapMovementPacket.cpp
        dll/src/BasicPongPacket.cpp
        dll/src/BasicAckPacket.cpp
        dll/src/NoMovementPacket.cpp
        dll/src/MultiTabStoragePacket.cpp
        dll/src/MapFightCountPacket.cpp
        dll/src/GameContextRemoveElementPacket.cpp
        dll/src/UnknownPacket.cpp
        dll/src/BasicPingPacket.cpp
)
target_link_libraries(dofus_test PRIVATE ${DETOURS_LIBRARY})
target_include_directories(dofus_test PRIVATE "dll/include" ${DETOURS_INCLUDE_DIRS})

add_executable(injector injector/src/main.cpp)
target_link_libraries(injector PRIVATE ${DETOURS_LIBRARY})
target_include_directories(injector PRIVATE ${DETOURS_INCLUDE_DIRS})