/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_FIRMWARE_MOCK_TX_PACKET_HPP_
#define XV3CART_FIRMWARE_MOCK_TX_PACKET_HPP_

#include <h6x_packet_handler/tx_ascii_packet.hpp>
#include <xv3cart_packet_definition/packet_utils.hpp>
#include <xv3cart_packet_definition/packet_types.hpp>
#include <rclcpp/rclcpp.hpp>

// TMP UpdatePower
#define __POWER_STATE_START_CHARGE__ 1
#define __POWER_STATE_STOP_CHARGE__ 2
#define __POWER_STATE_SHUTDOWN__ 4

namespace xv3cart_firmware_mock
{
static uint16_t d2u(const double x, const double x_min, const double x_max, const size_t bits)
{
  if (x < x_min) {
    return x_min;
  } else if (x > x_max) {
    return x_max;
  }
  return static_cast<uint16_t>(
    (x - x_min) * static_cast<double>((2 << (bits - 1)) - 1) / (x_max - x_min));
}

class TxPacket : public h6x_packet_handler::TxPacket<2, 32, 2>
{
public:
  static const std::size_t ID_IDX = 1;

public:
  TxPacket() = delete;
  explicit TxPacket(const char id)
  : h6x_packet_handler::TxPacket<2, 32, 2>::TxPacket({'$', id}) {}
};

class TxBatteryPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxBatteryPacket)
  static const char ID = 'A';

public:
  TxBatteryPacket()
  : TxBatteryPacket::TxPacket(TxBatteryPacket::ID) {}

  void setPacket(const struct BatteryDataCD2OD & battery_data)
  {
    this->set2ByteData<uint16_t>(0, battery_data.percent);
    this->set2ByteData<uint16_t>(2, battery_data.mA);
    this->set2ByteData<uint16_t>(4, battery_data.cV);
    this->set1ByteData<uint8_t>(12, battery_data.power_supply_status);
    this->makeOK();
  }
};

class TxWhlPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxWhlPacket)
  static const char ID = 'B';

public:
  TxWhlPacket()
  : TxWhlPacket::TxPacket(TxWhlPacket::ID) {}

  void setPacket(const struct WheelDataCD2OD & wheel_data)
  {
    this->set2ByteData<uint16_t>(
      0, d2u(
        wheel_data.enc_l, PacketUtils::P_MIN, PacketUtils::P_MAX,
        16));
    this->set2ByteData<uint16_t>(
      2, d2u(
        wheel_data.enc_r, PacketUtils::P_MIN, PacketUtils::P_MAX,
        16));
    this->set2ByteData<uint16_t>(
      4, d2u(
        wheel_data.rpm_l, PacketUtils::V_MIN, PacketUtils::V_MAX,
        12));
    this->set2ByteData<uint16_t>(
      6, d2u(
        wheel_data.rpm_r, PacketUtils::V_MIN, PacketUtils::V_MAX,
        12));
    this->set2ByteData<uint16_t>(
      8, d2u(
        wheel_data.trk_l, PacketUtils::T_MIN, PacketUtils::T_MAX,
        12));
    this->set2ByteData<uint16_t>(
      10,
      d2u(wheel_data.trk_r, PacketUtils::T_MIN, PacketUtils::T_MAX, 12));
    this->makeOK();
  }
};

class TxMgsFPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxMgsFPacket)
  static const char ID = 'C';

public:
  TxMgsFPacket()
  : TxMgsFPacket::TxPacket(TxMgsFPacket::ID) {}

  void setPacket(const struct MgsDataCD2OD & mgs_data)
  {
    for (size_t i = 0; i < 16; ++i) {
      this->set1ByteData<uint8_t>((int)i, mgs_data.data[i]);
    }
    this->makeOK();
  }
};

class TxMgsBPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxMgsBPacket)
  static const char ID = 'D';

public:
  TxMgsBPacket()
  : TxMgsBPacket::TxPacket(TxMgsBPacket::ID) {}

  void setPacket(const struct MgsDataCD2OD & mgs_data)
  {
    for (size_t i = 0; i < 16; ++i) {
      this->set1ByteData<uint8_t>((int)i, mgs_data.data[i]);
    }
    this->makeOK();
  }
};

class TxInfoPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxInfoPacket)
  static const char ID = 'G';

public:
  TxInfoPacket()
  : TxInfoPacket::TxPacket(TxInfoPacket::ID) {}
  void setPacket(const struct InfoDataCD2OD & info_data)
  {
    this->set1ByteData<uint8_t>(0, info_data.agv_info);
    this->set1ByteData<uint8_t>(1, info_data.bty_info);
    this->set1ByteData<uint8_t>(2, info_data.charge_info);
    this->set1ByteData<uint8_t>(3, info_data.mgs_info);
    this->set1ByteData<uint8_t>(4, info_data.tof_info);
    this->set1ByteData<uint8_t>(
      5,
      info_data.io_info_oden |
      (info_data.io_info_brk_unlocked << 1) | (info_data.io_info_em << 2));
    this->makeOK();
  }

};


class TxToFPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxToFPacket)
  static const char ID = 'E';

public:
  TxToFPacket()
  : TxToFPacket::TxPacket(TxToFPacket::ID) {}

  void setPacket(const struct ToFDataCD2OD & tof_data)
  {
    this->set1ByteData<uint8_t>(0, tof_data.tof_state_f);
    this->set1ByteData<uint8_t>(1, tof_data.tof_state_b);
    this->set1ByteData<uint8_t>(2, tof_data.tof_state_l);
    this->set1ByteData<uint8_t>(3, tof_data.tof_state_r);
    this->makeOK();
  }
};


} // namespace xv3cart_firmware_mock

#endif // XV3CART_FIRMWARE_MOCK_RX_PACKET_HPP_
