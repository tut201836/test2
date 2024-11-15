#include "widget/widget.hpp"
#include "xv3cart_tester_interface/xv3cart_tester_interface.hpp" 
#include "xv3cart_tester_interface/rx_packet.hpp"
#include "xv3cart_tester_interface/tx_packet.hpp"
#include <xv3cart_packet_definition/packet_utils.hpp>
#include <QImage>
#include <QLabel>
#include <cmath>
#include <map>
#include <string>

namespace qt5_cart_firmware {

    CartFirmwareWidget::CartFirmwareWidget(QWidget *parent) : QWidget(parent) {
        ui.setupUi(this);
        updateLabels();
        updateImages();
    }

    void CartFirmwareWidget::updateLabels() {
        CartStatus cartStatus;

        std::string port = "/dev/pts/12";

        // ラベル情報を格納するmap
        std::map<QLabel*, QString> label_info = {
            {ui.ToF_Front_label, "ToF Front: %1"},
            {ui.ToF_Back_label, "ToF Back: %1"},
            {ui.ToF_Left_label, "ToF Left: %1"},
            {ui.ToF_Right_label, "ToF Right: %1"},
            {ui.Left_Enc_label, "Left Enc: %1"},
            {ui.Right_Enc_label, "Right Enc: %1"},
            {ui.Left_RPM_label, "Left RPM: %1"},
            {ui.Right_RPM_label, "Right RPM: %1"},
            {ui.Left_Trk_label, "Left Trk: %1"},
            {ui.Right_Trk_label, "Right Trk: %1"},
            {ui.AGV_label, "AGV: %1"},
            {ui.Bty_label, "Bty: %1"},
            {ui.Charge_label, "Charge: %1"},
            {ui.MGS_label, "MGS: %1"},
            {ui.ToF_label, "ToF: %1"}
        };

        // 各ラベルに対応するデータ
        std::map<QLabel*, int> label_data = {
            {ui.ToF_Front_label, cartStatus.tof_front_mode},
            {ui.ToF_Back_label, cartStatus.tof_back_mode},
            {ui.ToF_Left_label, cartStatus.tof_left_mode},
            {ui.ToF_Right_label, cartStatus.tof_right_mode},
            {ui.Left_Enc_label, cartStatus.left_enc},
            {ui.Right_Enc_label, cartStatus.right_enc},
            {ui.Left_RPM_label, cartStatus.left_rpm},
            {ui.Right_RPM_label, cartStatus.right_rpm},
            {ui.Left_Trk_label, cartStatus.left_trk},
            {ui.Right_Trk_label, cartStatus.right_trk},
            {ui.AGV_label, cartStatus.agv_info},
            {ui.Bty_label, cartStatus.bty_info},
            {ui.Charge_label, cartStatus.charge_info},
            {ui.MGS_label, cartStatus.mgs_info},
            {ui.ToF_label, cartStatus.tof_info}
        };

        // init interface
        auto interface = std::make_shared<xv3cart_tester_interface::Xv3CartTesterInterface>(port, 115200);
        interface->rx_battery_packet_ = std::make_unique<xv3cart_tester_interface::RxBatteryPacket>();
        interface->rx_whl_packet_ = std::make_unique<xv3cart_tester_interface::RxWhlPacket>();
        interface->rx_tof_packet_ = std::make_unique<xv3cart_tester_interface::RxToFPacket>();
        interface->rx_mgs_l_packet_ = std::make_unique<xv3cart_tester_interface::RxMgsFPacket>();
        interface->rx_mgs_r_packet_ = std::make_unique<xv3cart_tester_interface::RxMgsBPacket>();

        interface->configure();
        interface->activate();

        // mapを利用してラベルを一括更新
        for (auto& [label, text] : label_info) {
            int value = label_data[label];  // 対応するデータを取得
            label->setText(text.arg(value)); // ラベルにテキストを設定
        }

        // Bty Statusの更新は別途行う
        auto bty_data = interface->rx_battery_packet_->getPacket();
        std::string statusString = cartStatus.power_supply_status_map[cartStatus.powerSupplyStatus];
        QString Bty_Status_label_Text = QString("Bty: %1%, %2 mA, %3 cV, %4")
                                            .arg(bty_data.percent)
                                            .arg(bty_data.mA)
                                            .arg(bty_data.cV)
                                            .arg(1);
                                            // 余計なエラーが出るため一旦除外 .arg(power_supply_status_map[bty_data.power_supply_status].c_str());
        ui.Bty_Status_label->setText(Bty_Status_label_Text);
    }

    void CartFirmwareWidget::updateImages() {
        CartStatus cartStatus;  // CartStatus インスタンスを取得
        bool is_front_line_detected = false;
        bool is_back_line_detected = false;

        std::array<uint8_t, 16> arr_l = {/* データを埋める */};
        std::array<uint8_t, 16> arr_r = {/* データを埋める */};

        ui.img_1_label->setPixmap(QPixmap::fromImage(getImage(arr_l, is_front_line_detected)));
        ui.img_2_label->setPixmap(QPixmap::fromImage(getImage(arr_r, is_back_line_detected)));
    }

    void CartFirmwareWidget::convertRGB(const std::array<uint8_t, 16> &in, std::array<uint8_t, 16 * 3> &out, bool &is_line_detected) {
        uint8_t count_s = 0;
        for (size_t i = 0; i < in.size(); ++i) {
            const auto ret = -255.0 + (255.0 - (-255.0)) * (static_cast<float>(in.at(i)) / 255.0);
            uint8_t val_S = 0, val_N = 0;
            if (ret > 0.0) {
                val_N = static_cast<uint8_t>(round(abs(ret)));
            } else if (ret < 0.0) {
                val_S = static_cast<uint8_t>(round(abs(ret)));
            }

            out.at(i * 3) = val_N;
            out.at(i * 3 + 1) = 0;
            out.at(i * 3 + 2) = val_S;
            if (val_S > 100) {
                count_s++;
            }
        }
        is_line_detected = (count_s > 1);
    }

    QImage CartFirmwareWidget::getImage(const std::array<uint8_t, 16> &in, bool &is_line_detected) {
        std::array<uint8_t, 16 * 3> out;
        convertRGB(in, out, is_line_detected);
        QImage ret(320, 20, QImage::Format_RGB888);
        for (size_t i = 0; i < 16; ++i) {
            for (size_t j = 0; j < 20; ++j) {
                for (size_t k = 0; k < 20; ++k) {
                    ret.setPixel(i * 20 + k, j, qRgb(out.at(i * 3), out.at(i * 3 + 1), out.at(i * 3 + 2)));
                }
            }
        }
        return ret;
    }

} // namespace qt5_cart_firmware
