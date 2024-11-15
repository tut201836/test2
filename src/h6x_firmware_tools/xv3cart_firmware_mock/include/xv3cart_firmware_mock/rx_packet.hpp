/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_FIRMWARE_MOCK_RX_PACKET_HPP_
#define XV3CART_FIRMWARE_MOCK_RX_PACKET_HPP_

#include <algorithm>

#include <h6x_packet_handler/rx_ascii_packet.hpp>
#include <xv3cart_packet_definition/packet_utils.hpp>
#include <xv3cart_packet_definition/packet_types.hpp>
#include <rclcpp/rclcpp.hpp>


namespace xv3cart_firmware_mock
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
  : h6x_packet_handler::RxPacket<2, 32, 2>::RxPacket({'#', id}) {}
};

class RxToFPacket : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxToFPacket)
  static const char ID = 'E';

public:
  RxToFPacket()
  : RxToFPacket::RxPacket(RxToFPacket::ID) {}

  inline void loadPacket(struct ToFDataOD2CD & tof_data)
  {
    tof_data.front_mode = this->get1byteData<uint8_t>(0);
    tof_data.rear_mode = this->get1byteData<uint8_t>(1);
    tof_data.left_mode = this->get1byteData<uint8_t>(2);
    tof_data.right_mode = this->get1byteData<uint8_t>(3);
  }

  struct ToFDataOD2CD getPacket()
  {
    struct ToFDataOD2CD tof_data;
    loadPacket(tof_data);
    return tof_data;
  }

};

class RxTrigger1Packet : public RxPacket
{
public:
  RCLCPP_UNIQUE_PTR_DEFINITIONS(RxTrigger1Packet)
  static const char ID = 'F';

public:
  RxTrigger1Packet()
  : RxTrigger1Packet::RxPacket(RxTrigger1Packet::ID) {}

  inline void loadPacket(struct TriggerDataOD2CD & trigger_data)
  {
    trigger_data.brk_status = this->get1byteData<uint8_t>(0);
    trigger_data.charge_trigger = this->get1byteData<uint8_t>(1);
    trigger_data.power_off = this->get1byteData<uint8_t>(2);
    trigger_data.power_off_f = this->get1byteData<uint8_t>(3);
    trigger_data.clear_error = this->get1byteData<uint8_t>(4);
  }

  struct TriggerDataOD2CD getPacket()
  {
    struct TriggerDataOD2CD trigger_data;
    loadPacket(trigger_data);
    return trigger_data;
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

  inline void loadPacket(struct WhlDataOD2CD & whl_data)
  {
    whl_data.speed_l = u2d(
      this->get2byteData<int16_t>(
        0), PacketUtils::V_MIN, PacketUtils::V_MAX, 12);
    whl_data.speed_r = u2d(
      this->get2byteData<int16_t>(
        2), PacketUtils::V_MIN, PacketUtils::V_MAX, 12);
  }

  struct WhlDataOD2CD getPacket()
  {
    struct WhlDataOD2CD whl_data;
    loadPacket(whl_data);
    return whl_data;
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
};

} // namespace xv3cart_firmware_mock

#endif // XV3CART_FIRMWARE_MOCK_TX_PACKET_HPP_
