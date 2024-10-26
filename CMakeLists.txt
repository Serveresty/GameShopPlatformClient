cmake_minimum_required(VERSION 3.31.0)

# Название проекта
project(GameShopPlatformClient)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Указываем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Найти необходимые пакеты Qt5
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)

# Пути к исходникам и заголовкам
set(SOURCES
    src/main.cpp
    src/authorization.cpp
    includes/authorization.h
)

# Создаем исполняемый файл
add_executable(GameShopPlatformClient ${SOURCES})

# Линкуем с библиотеками Qt
target_link_libraries(GameShopPlatformClient Qt6::Widgets Qt6::Core Qt6::Gui)