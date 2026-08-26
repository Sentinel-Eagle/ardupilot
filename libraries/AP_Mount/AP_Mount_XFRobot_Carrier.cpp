#include "AP_Mount_XFRobot_Carrier.h"

#if HAL_MOUNT_XFROBOT_ENABLED

#include <AP_AHRS/AP_AHRS.h>
#include <AP_Common/Location.h>
#include <AP_GPS/AP_GPS.h>

AP_Mount_XFRobot_Carrier::State AP_Mount_XFRobot_Carrier::get_state(uint32_t now_ms)
{
#if AP_MOUNT_XFROBOT_BENCH_SIM_ENABLED
    return get_bench_state(now_ms);
#else
    return get_live_state();
#endif
}

float AP_Mount_XFRobot_Carrier::get_yaw_rad(uint32_t now_ms)
{
#if AP_MOUNT_XFROBOT_BENCH_SIM_ENABLED
    return get_bench_yaw_rad(now_ms);
#else
    return AP::ahrs().get_yaw_rad();
#endif
}

AP_Mount_XFRobot_Carrier::State AP_Mount_XFRobot_Carrier::get_live_state()
{
    const Vector3f &accel_ef = AP::ahrs().get_accel_ef();
    State state {
        .accel_neu_mss = {
            accel_ef.x,
            accel_ef.y,
            -(accel_ef.z + GRAVITY_MSS),
        },
        .roll_deg = AP::ahrs().get_roll_deg(),
        .pitch_deg = AP::ahrs().get_pitch_deg(),
        .yaw_rad = AP::ahrs().get_yaw_rad(),
        .gps_week_ms = AP::gps().time_week_ms(),
        .gps_week = AP::gps().time_week(),
        .gps_num_sats = AP::gps().num_sats(),
        .ins_valid = AP::ahrs().have_inertial_nav(),
    };

    Vector3f velocity_ned_ms;
    if (state.ins_valid && AP::ahrs().get_velocity_NED(velocity_ned_ms)) {
        state.velocity_neu_ms = {
            velocity_ned_ms.x,
            velocity_ned_ms.y,
            -velocity_ned_ms.z,
        };
    }

    Location location;
    if (AP::ahrs().get_location(location)) {
        state.longitude = location.lng;
        state.latitude = location.lat;

        int32_t altitude_amsl_cm;
        if (location.get_alt_cm(Location::AltFrame::ABSOLUTE, altitude_amsl_cm)) {
            state.altitude_amsl_mm = altitude_amsl_cm * 10;
        }

        int32_t relative_altitude_cm;
        if (location.get_alt_cm(Location::AltFrame::ABOVE_HOME, relative_altitude_cm)) {
            state.relative_altitude_mm = relative_altitude_cm * 10;
        }
    }

    return state;
}

#if AP_MOUNT_XFROBOT_BENCH_SIM_ENABLED

static constexpr float BENCH_CIRCLE_RADIUS_M = 50.0f;
static constexpr float BENCH_CIRCLE_SPEED_MS = 10.0f;
static constexpr int32_t BENCH_RELATIVE_ALTITUDE_MM = 100000;
static constexpr int32_t BENCH_ANCHOR_LATITUDE = 531127440;
static constexpr int32_t BENCH_ANCHOR_LONGITUDE = 185587070;
static constexpr int32_t BENCH_ANCHOR_ALTITUDE_AMSL_CM = 8190;
static constexpr uint8_t BENCH_GPS_NUM_SATS = 12;
static constexpr uint16_t BENCH_GPS_WEEK = 2433;
static constexpr uint32_t BENCH_GPS_WEEK_START_MS = 2U * 24U * 60U * 60U * 1000U;

AP_Mount_XFRobot_Carrier::State AP_Mount_XFRobot_Carrier::get_bench_state(uint32_t now_ms)
{
    const float phase_rad = wrap_2PI(now_ms * 0.001f * BENCH_CIRCLE_SPEED_MS / BENCH_CIRCLE_RADIUS_M);
    const float phase_sin = sinf(phase_rad);
    const float phase_cos = cosf(phase_rad);
    const float centripetal_accel_mss = sq(BENCH_CIRCLE_SPEED_MS) / BENCH_CIRCLE_RADIUS_M;

    Location location(BENCH_ANCHOR_LATITUDE,
                      BENCH_ANCHOR_LONGITUDE,
                      BENCH_ANCHOR_ALTITUDE_AMSL_CM + BENCH_RELATIVE_ALTITUDE_MM / 10,
                      Location::AltFrame::ABSOLUTE);
    location.offset(BENCH_CIRCLE_RADIUS_M * phase_cos,
                    BENCH_CIRCLE_RADIUS_M * phase_sin);

    return {
        .accel_neu_mss = {
            -centripetal_accel_mss * phase_cos,
            -centripetal_accel_mss * phase_sin,
            0.0f,
        },
        .velocity_neu_ms = {
            -BENCH_CIRCLE_SPEED_MS * phase_sin,
            BENCH_CIRCLE_SPEED_MS * phase_cos,
            0.0f,
        },
        .roll_deg = degrees(atanf(centripetal_accel_mss / GRAVITY_MSS)),
        .pitch_deg = 0.0f,
        .yaw_rad = get_bench_yaw_rad(now_ms),
        .longitude = location.lng,
        .latitude = location.lat,
        .altitude_amsl_mm = BENCH_ANCHOR_ALTITUDE_AMSL_CM * 10 + BENCH_RELATIVE_ALTITUDE_MM,
        .relative_altitude_mm = BENCH_RELATIVE_ALTITUDE_MM,
        .gps_week_ms = uint32_t((BENCH_GPS_WEEK_START_MS + now_ms % AP_MSEC_PER_WEEK) % AP_MSEC_PER_WEEK),
        .gps_week = BENCH_GPS_WEEK,
        .gps_num_sats = BENCH_GPS_NUM_SATS,
        .ins_valid = true,
    };
}

float AP_Mount_XFRobot_Carrier::get_bench_yaw_rad(uint32_t now_ms)
{
    const float angular_rate_rads = BENCH_CIRCLE_SPEED_MS / BENCH_CIRCLE_RADIUS_M;
    return wrap_PI(now_ms * 0.001f * angular_rate_rads + M_PI_2);
}

#endif  // AP_MOUNT_XFROBOT_BENCH_SIM_ENABLED

#endif  // HAL_MOUNT_XFROBOT_ENABLED
