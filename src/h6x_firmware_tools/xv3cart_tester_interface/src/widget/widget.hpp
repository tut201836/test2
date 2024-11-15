/*
 * Copyright (c) 2024 NITK.K ROS-Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef QT5_CART_FIRMWARE_WIDGET_WIDGET_HPP_
#define QT5_CART_FIRMWARE_WIDGET_WIDGET_HPP_

// 作成した.uiファイル名によって変わる
// xxx.ui -> ui_xxx.h
#include "ui_qt5_cart_firmware.h"

namespace qt5_cart_firmware
{

// Widgetのクラス
class CartFirmwareWidget : public QWidget
{
  public:
    // 初期化
    explicit CartFirmwareWidget(QWidget *);
    void updateLabels();
    void updateImages();
    QImage getImage(const std::array<uint8_t, 16> &in, bool &is_line_detected);
    static void convertRGB(const std::array<uint8_t, 16> &in, std::array<uint8_t, 16 * 3> &out, bool &is_line_detected);


  private:
    // ボタンがクリックされたときの処理
    void onPushButtonClicked();

  private:
    Ui::CartFirmwareWidget ui;

  
};

} // namespace qt5_cart_firmware

#endif 