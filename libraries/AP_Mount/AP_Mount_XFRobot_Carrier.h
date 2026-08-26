#pragma once

#include "AP_Mount_config.h"

#if HAL_MOUNT_XFROBOT_ENABLED

#include <AP_Math/AP_Math.h>

class AP_Mount_XFRobot_Carrier {
public:
    struct State {
        Vector3f accel_neu_mss;
        Vector3f velocity_neu_ms;
        float roll_deg;
        float pitch_deg;
        float yaw_rad;
        int32_t longitude;
        int32_t latitude;
        int32_t altitude_amsl_mm;
        int32_t relative_altitude_mm;
        uint32_t gps_week_ms;
        uint16_t gps_week;
        uint8_t gps_num_sats;
        bool ins_valid;
    };

    static State get_state(uint32_t now_ms);
    static float get_yaw_rad(uint32_t now_ms);

private:
    static State get_live_state();

#if AP_MOUNT_XFROBOT_BENCH_SIM_ENABLED
    static State get_bench_state(uint32_t now_ms);
    static float get_bench_yaw_rad(uint32_t now_ms);
#endif
};

#endif  // HAL_MOUNT_XFROBOT_ENABLED
