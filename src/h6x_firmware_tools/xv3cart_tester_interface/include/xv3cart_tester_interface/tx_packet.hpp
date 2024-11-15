/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_TESTER_INTERFACE_TX_PACKET_HPP
#define XV3CART_TESTER_INTERFACE_TX_PACKET_HPP

#include <h6x_packet_handler/tx_ascii_packet.hpp>
#include <xv3cart_packet_definition/packet_utils.hpp>
#include <xv3cart_packet_definition/packet_types.hpp>
#include <rclcpp/rclcpp.hpp>

// TMP UpdatePower
#define __POWER_STATE_START_CHARGE__ 1
#define __POWER_STATE_STOP_CHARGE__ 2
#define __POWER_STATE_SHUTDOWN__ 4

namespace xv3cart_tester_interface
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
  TxPacket() = delete;
  explicit TxPacket(const char id)
  : h6x_packet_handler::TxPacket<2, 32, 2>::TxPacket({'#', id}, "\r") {}
};

class TxToFPacket : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxToFPacket)
  static const char ID = 'E';

public:
  TxToFPacket()
  : TxToFPacket::TxPacket(TxToFPacket::ID) {}

  void setPacket(const struct ToFDataOD2CD & tof_data)
  {
    this->set1ByteData<uint8_t>(0, tof_data.front_mode);
    this->set1ByteData<uint8_t>(1, tof_data.rear_mode);
    this->set1ByteData<uint8_t>(2, tof_data.left_mode);
    this->set1ByteData<uint8_t>(3, tof_data.right_mode);
    this->makeOK();
  }

};

class TxTrigger1Packet : public TxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(TxTrigger1Packet)
  static const char ID = 'F';

public:
  TxTrigger1Packet()
  : TxTrigger1Packet::TxPacket(TxTrigger1Packet::ID) {}

  void setPacket(const struct TriggerDataOD2CD & trigger_data)
  {
    this->set1ByteData<uint8_t>(0, trigger_data.brk_status);
    this->set1ByteData<uint8_t>(1, trigger_data.charge_trigger);
    this->set1ByteData<uint8_t>(2, trigger_data.power_off);
    this->set1ByteData<uint8_t>(3, trigger_data.power_off_f);
    this->set1ByteData<uint8_t>(4, trigger_data.clear_error);

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

  void setPacket(const struct WhlDataOD2CD & whl_data)
  {
    this->set2ByteData<int16_t>(
      0,
      d2u(whl_data.speed_l, PacketUtils::V_MIN, PacketUtils::V_MAX, 12));
    this->set2ByteData<int16_t>(
      2,
      d2u(whl_data.speed_r, PacketUtils::V_MIN, PacketUtils::V_MAX, 12));
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

  void setPacket()
  {
    this->makeOK();
  }
};

} // namespace xv3cart_tester_interface

#endif // XV3CART_TESTER_INTERFACE_TX_PACKET_HPP
