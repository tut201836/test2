/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_TESTER_INTERFACE_RX_PACKET_HPP
#define XV3CART_TESTER_INTERFACE_RX_PACKET_HPP

#include <algorithm>

#include <h6x_packet_handler/rx_ascii_packet.hpp>
#include <xv3cart_packet_definition/packet_utils.hpp>
#include <xv3cart_packet_definition/packet_types.hpp>
#include <rclcpp/rclcpp.hpp>

namespace xv3cart_tester_interface
{

static double u2d(const uint16_t x, const double x_min, const double x_max, const size_t bits)
{
  return (static_cast<double>(x)) * (x_max - x_min) / static_cast<double>((2 << (bits - 1)) - 1) +
         x_min;
}

class RxPacket : public h6x_packet_handler::RxPacket<2, 32, 2>
{
public:
  static const std::size_t ID_IDX = 1;

public:
  RxPacket() = delete;
  explicit RxPacket(const char id)
  : h6x_packet_handler::RxPacket<2, 32, 2>::RxPacket({'$', id}) {}
};

class RxBatteryPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxBatteryPacket)
  static const char ID = 'A';

public:
  RxBatteryPacket()
  : RxBatteryPacket::RxPacket(RxBatteryPacket::ID) {}

  inline void loadPacket(struct BatteryDataCD2OD & battery_data)
  {
    battery_data.percent = this->get1byteData<uint8_t>(0) << 8 | this->get1byteData<uint8_t>(1);
    battery_data.mA = this->get1byteData<uint8_t>(2) << 8 | this->get1byteData<uint8_t>(3);
    battery_data.cV = this->get1byteData<uint8_t>(4) << 8 | this->get1byteData<uint8_t>(5);
    battery_data.power_supply_status = this->get1byteData<uint8_t>(12);
  }

  struct BatteryDataCD2OD getPacket()
  {
    struct BatteryDataCD2OD battery_data;
    loadPacket(battery_data);
    return battery_data;
  }
};

class RxWhlPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxWhlPacket)
  static const char ID = 'B';

public:
  RxWhlPacket()
  : RxWhlPacket::RxPacket(RxWhlPacket::ID) {}

  inline void loadPacket(struct WheelDataCD2OD & wheel_data)
  {
    wheel_data.enc_l = u2d(
      this->get2byteData<uint16_t>(
        0), PacketUtils::P_MIN, PacketUtils::P_MAX, 16);
    wheel_data.enc_r = u2d(
      this->get2byteData<uint16_t>(
        2), PacketUtils::P_MIN, PacketUtils::P_MAX, 16);
    wheel_data.rpm_l = u2d(
      this->get2byteData<uint16_t>(
        4), PacketUtils::V_MIN, PacketUtils::V_MAX, 12);
    wheel_data.rpm_r = u2d(
      this->get2byteData<uint16_t>(
        6), PacketUtils::V_MIN, PacketUtils::V_MAX, 12);
    wheel_data.trk_l = u2d(
      this->get2byteData<uint16_t>(
        8), PacketUtils::T_MIN, PacketUtils::T_MAX, 12);
    wheel_data.trk_r = u2d(
      this->get2byteData<uint16_t>(
        10), PacketUtils::T_MIN, PacketUtils::T_MAX, 12);
  }

  struct WheelDataCD2OD getPacket()
  {
    struct WheelDataCD2OD wheel_data;
    loadPacket(wheel_data);
    return wheel_data;
  }
};

class RxMgsFPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxMgsFPacket)
  static const char ID = 'C';

public:
  RxMgsFPacket()
  : RxMgsFPacket::RxPacket(RxMgsFPacket::ID) {}

  inline void loadPacket(struct MgsDataCD2OD & mgs_data)
  {
    for (size_t i = 0; i < 16; ++i) {
      mgs_data.data[i] = this->get1byteData<uint8_t>((int)i);
    }
  }

  struct MgsDataCD2OD getPacket()
  {
    struct MgsDataCD2OD mgs_data;
    loadPacket(mgs_data);
    return mgs_data;
  }
};

class RxMgsBPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxMgsBPacket)
  static const char ID = 'D';

public:
  RxMgsBPacket()
  : RxMgsBPacket::RxPacket(RxMgsBPacket::ID) {}

  inline void loadPacket(struct MgsDataCD2OD & mgs_data)
  {
    for (size_t i = 0; i < 16; ++i) {
      mgs_data.data[i] = this->get1byteData<uint8_t>((int)i);
    }
  }

  struct MgsDataCD2OD getPacket()
  {
    struct MgsDataCD2OD mgs_data;
    loadPacket(mgs_data);
    return mgs_data;
  }
};

class RxToFPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxToFPacket)
  static const char ID = 'E';

public:
  RxToFPacket()
  : RxToFPacket::RxPacket(RxToFPacket::ID) {}

  inline void loadPacket(struct ToFDataCD2OD & tof_data)
  {
    tof_data.tof_state_f = this->get1byteData<uint8_t>(0);
    tof_data.tof_state_b = this->get1byteData<uint8_t>(1);
    tof_data.tof_state_l = this->get1byteData<uint8_t>(2);
    tof_data.tof_state_r = this->get1byteData<uint8_t>(3);
  }

  struct ToFDataCD2OD getPacket()
  {
    struct ToFDataCD2OD tof_data;
    loadPacket(tof_data);
    return tof_data;
  }
};

class RxInfoPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxInfoPacket)
  static const char ID = 'G';

public:
  RxInfoPacket()
  : RxInfoPacket::RxPacket(RxInfoPacket::ID) {}
  inline void loadPacket(struct InfoDataCD2OD & info_data)
  {
    info_data.agv_info = this->get1byteData<uint8_t>(0);
    info_data.bty_info = this->get1byteData<uint8_t>(1);
    info_data.charge_info = this->get1byteData<uint8_t>(2);
    info_data.mgs_info = this->get1byteData<uint8_t>(3);
    info_data.tof_info = this->get1byteData<uint8_t>(4);
    info_data.io_info_oden = this->get1byteData<uint8_t>(5) & 0x01;
    info_data.io_info_brk_unlocked = this->get1byteData<uint8_t>(5) & 0x02;
    info_data.io_info_em = this->get1byteData<uint8_t>(5) & 0x04;
  }

  struct InfoDataCD2OD getPacket()
  {
    struct InfoDataCD2OD info_data;
    loadPacket(info_data);
    return info_data;
  }

};

} // namespace xv3cart_tester_interface

#endif // XV3CART_TESTER_INTERFACE_RX_PACKET_HPP
