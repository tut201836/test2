/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "xv3cart_firmware_mock/xv3cart_firmware_mock.hpp"

namespace xv3cart_firmware_mock
{

Xv3CartFirmwareMock::Xv3CartFirmwareMock(
  const std::string & dev, const int baudrate)
: baudrate_(baudrate)
{
  this->port_handler_ = std::make_unique<PortHandler>(dev);

  this->tx_battery_packet_ = std::make_unique<TxBatteryPacket>();
  this->tx_whl_packet_ = std::make_unique<TxWhlPacket>();
  this->tx_mgs_l_packet_ = std::make_unique<TxMgsFPacket>();
  this->tx_mgs_r_packet_ = std::make_unique<TxMgsBPacket>();
  this->tx_tof_packet_ = std::make_unique<TxToFPacket>();
  this->tx_info_packet_ = std::make_unique<TxInfoPacket>();

  this->rx_whl_packet_ = std::make_unique<RxWhlPacket>();
  this->rx_tof_packet_ = std::make_unique<RxToFPacket>();
  this->rx_info_packet_ = std::make_unique<RxInfoPacket>();
  this->rx_trigger1_packet_ = std::make_unique<RxTrigger1Packet>();
}

Xv3CartFirmwareMock::~Xv3CartFirmwareMock()
{
  this->port_handler_.reset();

  this->tx_battery_packet_.reset();
  this->tx_whl_packet_.reset();
  this->tx_mgs_l_packet_.reset();
  this->tx_mgs_r_packet_.reset();
  this->tx_tof_packet_.reset();
  this->tx_info_packet_.reset();

  this->rx_whl_packet_.reset();
  this->rx_tof_packet_.reset();
  this->rx_trigger1_packet_.reset();
}

bool Xv3CartFirmwareMock::configure()
{
  if (!this->port_handler_->configure(this->baudrate_, 20)) {
    return false;
  }

  return true;
}

bool Xv3CartFirmwareMock::activate()
{
  if (!this->port_handler_->open()) {
    return false;
  }

  return true;
}

bool Xv3CartFirmwareMock::deactivate()
{
  if (!this->port_handler_->close()) {
    return false;
  }

  return true;
}

void __attribute__((optimize("O0"))) Xv3CartFirmwareMock::read(void) noexcept
{
  static uint8_t i = 0;
  static std::string send_buf;
  static std::string packet;

  static std::array<uint8_t, 16> line_fb_data;
  static struct BatteryDataCD2OD battery_data;
  static struct WheelDataCD2OD whl_tx_data;
  static struct WhlDataOD2CD whl_rx_data;
  static struct ToFDataCD2OD tof_tx_data;
  static struct ToFDataOD2CD tof_rx_data;
  static struct InfoDataCD2OD info_tx_data;

  for (;; ) {
    auto buf = std::stringstream();
    // clear write buffer
    const ssize_t ret = this->port_handler_->readUntil(buf, '\r');
    if (ret <= 0) {
      break;
    }

    if (buf.str().size() == 0) {
      continue;
    }

    packet = buf.str();
    if (packet.size() == 0) {
      continue;
    }
    // ADD 1 for '\r'
    if (packet.size() != RxPacket::ASCII_BUF_SIZE + 1) {
      continue;
    }
    packet.pop_back();


    switch (packet[RxPacket::ID_IDX]) {
      case RxWhlPacket::ID:
        this->rx_whl_packet_->set(packet);
        this->rx_whl_packet_->loadPacket(whl_rx_data);
        whl_tx_data.enc_l += whl_rx_data.speed_l / 1000.0;
        whl_tx_data.enc_r += whl_rx_data.speed_r / 1000.0;
        whl_tx_data.rpm_l = whl_rx_data.speed_l;
        whl_tx_data.rpm_r = whl_rx_data.speed_r;
        whl_tx_data.trk_l = whl_rx_data.speed_l / 1000.0;
        whl_tx_data.trk_r = whl_rx_data.speed_r / 1000.0;

        this->tx_whl_packet_->setPacket(whl_tx_data);
        this->tx_whl_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));


        // get data
        if (++i == 16) {
          i = 0;
        }
        for (size_t i = 0; i < 16; ++i) {
          line_fb_data[i] = 127;
        }
        line_fb_data[i] = 0;
        this->tx_mgs_l_packet_->setPacket({line_fb_data});
        this->tx_mgs_l_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        line_fb_data[i] = 255;
        this->tx_mgs_r_packet_->setPacket({line_fb_data});
        this->tx_mgs_r_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        battery_data.percent = i;
        battery_data.mA = i * 100;
        battery_data.cV = i;
        battery_data.power_supply_status = 3;
        this->tx_battery_packet_->setPacket(battery_data);
        this->tx_battery_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        break;
      case RxTrigger1Packet::ID:
        this->rx_trigger1_packet_->set(packet);
        if (this->rx_trigger1_packet_->getPacket().charge_trigger == 2) {
          info_tx_data.charge_info = 1;
        } else {
          info_tx_data.charge_info = 0;
        }

        if (this->rx_trigger1_packet_->getPacket().power_off == 1) {
          info_tx_data.agv_info = 1;
        } else {
          info_tx_data.agv_info = 0;
        }

        if (this->rx_trigger1_packet_->getPacket().power_off_f == 1) {
          exit(0);
        }

        this->tx_info_packet_->setPacket(info_tx_data);
        this->tx_info_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        break;
      case RxToFPacket::ID:
        this->rx_tof_packet_->set(packet);
        this->rx_tof_packet_->loadPacket(tof_rx_data);

        tof_tx_data.tof_state_f = (tof_rx_data.front_mode == 2) ? 3 : i;
        tof_tx_data.tof_state_b = (tof_rx_data.rear_mode == 2) ? 3 : i;
        tof_tx_data.tof_state_l = (tof_rx_data.left_mode == 2) ? 3 : i;
        tof_tx_data.tof_state_r = (tof_rx_data.right_mode == 2) ? 3 : i;

        this->tx_tof_packet_->setPacket(tof_tx_data);
        this->tx_tof_packet_->get(send_buf);
        this->port_handler_->write(send_buf.data(), send_buf.size());
        break;
      case RxInfoPacket::ID:
        this->rx_info_packet_->set(packet);
        break;
      default:
        break;
    }
  }
}

} // namespace Xv3CartDriver_interface
