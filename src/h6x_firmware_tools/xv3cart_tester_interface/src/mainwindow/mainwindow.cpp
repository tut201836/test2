#include "mainwindow.hpp"

namespace qt5_cart_firmware{
    CartFirmwareWindow::CartFirmwareWindow(QWidget * parent) : QMainWindow(parent) {
        setWindowTitle("xv3cart_tester_interface");
        resize(800, 600);
        setCentralWidget(new CartFirmwareWidget(this)); // ここで ExampleWidget が正しいかも確認
    }
}