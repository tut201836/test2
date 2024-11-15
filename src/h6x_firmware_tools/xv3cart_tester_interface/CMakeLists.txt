cmake_minimum_required(VERSION 3.5)
project(qt5_cart_firmware)

set(CMAKE_AUTOUIC ON)

find_package(ament_cmake_auto REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(h6x_packet_handler REQUIRED)

ament_auto_find_build_dependencies()

set(QT5_LIBS Qt5::Core Qt5::Gui Qt5::Widgets)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../xv3cart_packet_definition/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../h6x_serial_interface/h6x_packet_handler/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../h6x_serial_interface/h6x_serial_interface/include/
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt5_wrap_ui(UIS_HDRS src/widget/qt5_cart_firmware.ui)

# qt5_cart_firmware_widget ターゲットの定義とリンク
add_library(qt5_cart_firmware_widget
    src/widget/qt5_cart_firmware.ui 
    src/widget/widget.cpp)
target_link_libraries(qt5_cart_firmware_widget
    ${QT5_LIBS}
    xv3cart_tester_interface::xv3cart_tester_interface
    h6x_packet_handler::h6x_packet_handler
)

# qt5_cart_firmware_mainwindow ターゲットの定義とリンク
add_library(qt5_cart_firmware_mainwindow
    src/mainwindow/mainwindow.cpp)
target_link_libraries(qt5_cart_firmware_mainwindow
    ${QT5_LIBS}
    qt5_cart_firmware_widget
    xv3cart_tester_interface::xv3cart_tester_interface
    h6x_packet_handler::h6x_packet_handler
)

# qt5_cart_firmware_exec ターゲットの定義とリンク
add_executable(qt5_cart_firmware_exec src/main.cpp)
target_link_libraries(qt5_cart_firmware_exec
    ${QT5_LIBS}
    rclcpp::rclcpp
    qt5_cart_firmware_mainwindow
    qt5_cart_firmware_widget
    xv3cart_tester_interface::xv3cart_tester_interface
    h6x_packet_handler::h6x_packet_handler
)

install(TARGETS qt5_cart_firmware_exec DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

# rclcpp 依存関係の設定
ament_target_dependencies(qt5_cart_firmware_widget rclcpp)
ament_target_dependencies(qt5_cart_firmware_mainwindow rclcpp)

ament_auto_package()
