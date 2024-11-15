
/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_TESTER_INTERFACE_HPP
#define XV3CART_TESTER_INTERFACE_HPP
#ifndef XV3CART_TESTER_INTERFACE_XV3CART_TESTER_INTERFACE_HPP_
#define XV3CART_TESTER_INTERFACE_XV3CART_TESTER_INTERFACE_HPP_

#include <map>
#include <string>
#include <cstdint>
#include <string>
#include <memory>
#include <h6x_serial_interface/h6x_serial_interface.hpp>
#include <rclcpp/rclcpp.hpp>
#include "xv3cart_tester_interface/rx_packet.hpp"
#include "xv3cart_tester_interface/tx_packet.hpp"

namespace xv3cart_tester_interface
{
class Xv3CartTesterInterface
{
public:
  RCLCPP_SHARED_PTR_DEFINITIONS(Xv3CartTesterInterface)

public:
  using PortHandler = h6x_serial_interface::PortHandler;
  const int baudrate_;

  PortHandler::UniquePtr port_handler_;

  RxBatteryPacket::UniquePtr rx_battery_packet_;
  RxWhlPacket::UniquePtr rx_whl_packet_;
  RxMgsFPacket::UniquePtr rx_mgs_l_packet_;
  RxMgsBPacket::UniquePtr rx_mgs_r_packet_;
  RxToFPacket::UniquePtr rx_tof_packet_;
  RxInfoPacket::UniquePtr rx_info_packet_;

  TxWhlPacket::UniquePtr tx_whl_packet_;
  TxToFPacket::UniquePtr tx_tof_packet_;
  TxInfoPacket::UniquePtr tx_info_packet_;
  TxTrigger1Packet::UniquePtr tx_trigger1_packet_;

public:
  Xv3CartTesterInterface() = delete;
  explicit Xv3CartTesterInterface(const std::string &, const int);
  ~Xv3CartTesterInterface();

  bool configure();
  bool activate();
  bool deactivate();

  void __attribute__((optimize("O0"))) read(void) noexcept;
  void updateToF(const uint8_t, const uint8_t, const uint8_t, const uint8_t) noexcept;
  void updateBrake(const bool) noexcept;
  void updateCharge(const bool) noexcept;
  void shutdown(void) noexcept;
  void shutdown_force(void) noexcept;
  void clear_error(void) noexcept;
  void update_speed(const double, const double) noexcept;
  void update_info(void) noexcept;

private:
  static const rclcpp::Logger getLogger(void) noexcept;
};
} // namespace xv3cart_tester_interface


class CartStatus {
    public:
        int8_t batteryLevel = 75;
        int8_t current = 120;
        int8_t voltage = 12;
        int8_t powerSupplyStatus = 3;
        uint8_t tof_front_mode = 0;
        uint8_t tof_back_mode = 0;
        uint8_t tof_left_mode = 0;
        uint8_t tof_right_mode = 0;
        uint8_t left_enc = 0;
        uint8_t right_enc = 0;
        uint8_t left_rpm = 0;
        uint8_t right_rpm = 0;
        uint8_t left_trk = 0;
        uint8_t right_trk = 0;
        int8_t agv_info = 0;
        int8_t bty_info = 0;
        int8_t charge_info = 0;
        int8_t mgs_info = 0;
        int8_t tof_info = 0;

        std::map<uint8_t, std::string> power_supply_status_map = {
            {0, "UNKNOWN"}, {1, "CHARGING"}, {2, "DISCHARGING"},
            {3, "NOT_CHARGING"}, {4, "FULL"}
        };
};

#endif // XV3CART_TESTER_INTERFACE_HPP
#endif
