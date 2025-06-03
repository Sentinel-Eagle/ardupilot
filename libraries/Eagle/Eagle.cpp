#include <AP_Math/AP_Math.h>
#include "Eagle.h"

const AP_Param::GroupInfo Eagle::var_info[] = {
    // @Param: EAGLE_F0
    // @DisplayName: EAGLE_F0
    // @Description: EAGLE_F0
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F0", 0, Eagle, _f0, 0),

    // @Param: EAGLE_F1
    // @DisplayName: EAGLE_F1
    // @Description: EAGLE_F1
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F1", 1, Eagle, _f1, 0),

    // @Param: EAGLE_F2
    // @DisplayName: EAGLE_F2
    // @Description: EAGLE_F2
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F2", 2, Eagle, _f2, 0),

    // @Param: EAGLE_F3
    // @DisplayName: EAGLE_F3
    // @Description: EAGLE_F3
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F3", 3, Eagle, _f3, 0),

    // @Param: EAGLE_F4
    // @DisplayName: EAGLE_F4
    // @Description: EAGLE_F4
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F4", 4, Eagle, _f4, 0),

    // @Param: EAGLE_F5
    // @DisplayName: EAGLE_F5
    // @Description: EAGLE_F5
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F5", 5, Eagle, _f5, 0),

    // @Param: EAGLE_F6
    // @DisplayName: EAGLE_F6
    // @Description: EAGLE_F6
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F6", 6, Eagle, _f6, 0),

    // @Param: EAGLE_F7
    // @DisplayName: EAGLE_F7
    // @Description: EAGLE_F7
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F7", 7, Eagle, _f7, 0),

    // @Param: EAGLE_F8
    // @DisplayName: EAGLE_F8
    // @Description: EAGLE_F8
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F8", 8, Eagle, _f8, 0),

    // @Param: EAGLE_F9
    // @DisplayName: EAGLE_F9
    // @Description: EAGLE_F9
    // @Range: -100 100
    // @Increment: 0.01
    // @User: Standard
    AP_GROUPINFO("_F9", 9, Eagle, _f9, 0),

    // @Param: EAGLE_I0
    // @DisplayName: EAGLE_I0
    // @Description: EAGLE_I0
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I0", 10, Eagle, _i0, 0),

    // @Param: EAGLE_I1
    // @DisplayName: EAGLE_I1
    // @Description: EAGLE_I1
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I1", 11, Eagle, _i1, 0),

    // @Param: EAGLE_I2
    // @DisplayName: EAGLE_I2
    // @Description: EAGLE_I2
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I2", 12, Eagle, _i2, 0),

    // @Param: EAGLE_I3
    // @DisplayName: EAGLE_I3
    // @Description: EAGLE_I3
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I3", 13, Eagle, _i3, 0),

    // @Param: EAGLE_I4
    // @DisplayName: EAGLE_I4
    // @Description: EAGLE_I4
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I4", 14, Eagle, _i4, 0),

    // @Param: EAGLE_I5
    // @DisplayName: EAGLE_I5
    // @Description: EAGLE_I5
    // @Range: -10000 10000
    // @User: Standard
    AP_GROUPINFO("_I5", 15, Eagle, _i5, 0),


    AP_GROUPEND
};
