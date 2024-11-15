/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_FIRMWARE_MOCK_XV3CART_FIRMWARE_MOCK_HPP_
#define XV3CART_FIRMWARE_MOCK_XV3CART_FIRMWARE_MOCK_HPP_

#include <string>
#include <memory>

#include <h6x_serial_interface/h6x_serial_interface.hpp>
#include <rclcpp/rclcpp.hpp>

#include "xv3cart_firmware_mock/rx_packet.hpp"
#include "xv3cart_firmware_mock/tx_packet.hpp"

namespace xv3cart_firmware_mock
{
class Xv3CartFirmwareMock
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(Xv3CartFirmwareMock)

public:
  using PortHandler = h6x_serial_interface::PortHandler;
  const int baudrate_;

  PortHandler::UniquePtr port_handler_;

  TxBatteryPacket::UniquePtr tx_battery_packet_;
  TxWhlPacket::UniquePtr tx_whl_packet_;
  TxMgsFPacket::UniquePtr tx_mgs_l_packet_;
  TxMgsBPacket::UniquePtr tx_mgs_r_packet_;
  TxToFPacket::UniquePtr tx_tof_packet_;
  TxInfoPacket::UniquePtr tx_info_packet_;

  RxWhlPacket::UniquePtr rx_whl_packet_;
  RxToFPacket::UniquePtr rx_tof_packet_;
  RxInfoPacket::UniquePtr rx_info_packet_;
  RxTrigger1Packet::UniquePtr rx_trigger1_packet_;

public:
  Xv3CartFirmwareMock() = delete;
  explicit Xv3CartFirmwareMock(const std::string &, const int);
  ~Xv3CartFirmwareMock();

  bool configure();
  bool activate();
  bool deactivate();

  void __attribute__((optimize("O0"))) read(void) noexcept;

private:
  static const rclcpp::Logger getLogger(void) noexcept;
};
} // namespace xv3cart_firmware_mock

#endif // XV3CART_FIRMWARE_MOCK_XV3CART_FIRMWARE_MOCK_HPP_
