/*
 * Copyright (c) 2024 HarvestX Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef XV3CART_PACKET_DEFINITION_PACKET_UTILS_HPP_
#define XV3CART_PACKET_DEFINITION_PACKET_UTILS_HPP_

#define AK70
#include <cmath>


class PacketUtils
{
public:
#ifdef AK60
  static constexpr double P_MIN = -12.5, P_MAX = 12.5, V_MIN = -45.0, V_MAX = 45.0, T_MIN = -15.0,
  T_MAX = 15.0, Kp_MIN = 0.0, Kp_MAX = 500.0, Kd_MIN = 0.0, Kd_MAX = 5.0;
#endif
#ifdef AK70
  static constexpr double P_MIN = -12.5, P_MAX = 12.5, V_MIN = -50.0, V_MAX = 50.0, T_MIN = -25.0,
  T_MAX = 25.0, Kp_MIN = 0.0, Kp_MAX = 500.0, Kd_MIN = 0.0, Kd_MAX = 5.0;
#endif

  static constexpr double RPM2RPS = 2.0 * M_PI / 60.0;
  static constexpr double RPS2RPM = 60.0 / 2.0 / M_PI;

public:
  PacketUtils() = delete;
};

#endif // XV3CART_PACKET_DEFINITION_PACKET_UTILS_HPP_
