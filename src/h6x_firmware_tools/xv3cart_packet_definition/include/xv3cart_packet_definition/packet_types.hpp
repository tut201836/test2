/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_PACKET_DEFINITION_PACKET_TYPES_HPP_
#define XV3CART_PACKET_DEFINITION_PACKET_TYPES_HPP_

#include <stdint.h>
#include <array>

struct BatteryDataCD2OD
{
  int16_t percent;
  int16_t mA;
  int16_t cV;
  uint8_t power_supply_status;
};

struct WheelDataCD2OD
{
  double enc_l;
  double enc_r;
  double rpm_l;
  double rpm_r;
  double trk_l;
  double trk_r;
};

struct ToFDataCD2OD
{
  uint8_t tof_state_f;
  uint8_t tof_state_b;
  uint8_t tof_state_l;
  uint8_t tof_state_r;
};

struct InfoDataCD2OD
{
  uint8_t agv_info;
  uint8_t bty_info;
  uint8_t charge_info;
  uint8_t mgs_info;
  uint8_t tof_info;
  bool io_info_oden;
  bool io_info_brk_unlocked;
  bool io_info_em;
};

struct MgsDataCD2OD
{
  std::array<uint8_t, 16> data;
};

struct ToFDataOD2CD
{
  uint8_t front_mode;
  uint8_t rear_mode;
  uint8_t left_mode;
  uint8_t right_mode;
};

struct TriggerDataOD2CD
{
  uint8_t brk_status;
  uint8_t charge_trigger;
  uint8_t power_off;
  uint8_t power_off_f;
  uint8_t clear_error;
};

struct WhlDataOD2CD
{
  double speed_l;
  double speed_r;
};

struct InfoDataOD2CD
{
};

#endif // XV3CART_PACKET_DEFINITION_PACKET_TYPES_HPP
