#ifndef QT5_CART_FIRMWARE_MAINWINDOW_MAINWINDOW_HPP_
#define QT5_CART_FIRMWARE_MAINWINDOW_MAINWINDOW_HPP_

#include <QMainWindow>
#include "widget/widget.hpp"

namespace qt5_cart_firmware{
    class CartFirmwareWindow : public QMainWindow{
        public:
            explicit CartFirmwareWindow(QWidget * = nullptr);
    };
}

#endif