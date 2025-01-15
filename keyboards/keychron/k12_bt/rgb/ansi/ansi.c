#include "quantum.h"
#include "keymap.h"
#include "print.h"

#ifdef BLUETOOTH_ENABLE
#    include "iton_bt.h"
#    include "outputselect.h"

// static uint32_t last_update_time = 0;

static bool     ev_connecting    = false;
static bool     ev_pairing       = false;
static uint32_t ev_disconnected  = 0;
static uint32_t ev_connected     = 0;
static uint32_t ev_battery_level = 0;

static uint32_t battery_level = 0; // Battery level reported by Iton BT
static uint32_t bt_profile    = 0; // Bluetooth profile number

static bool dip_switch_bt_en = false; // Bluetooth ON by BT/OFF/Cable dip switch

void iton_bt_connection_successful() {
    print("iton_bt_connection_successful()");
    set_output(OUTPUT_BLUETOOTH);
    ev_connected  = 2500;
    ev_pairing    = false;
    ev_connecting = false;
}

void iton_bt_entered_pairing() {
    print("iton_bt_entered_pairing()");
    ev_pairing    = true;
    ev_connected  = 0;
    ev_connecting = false;
}

void iton_bt_enters_connection_state() {
    print("iton_bt_enters_connection_state()");
    ev_connecting = true;
    ev_connected  = 0;
    ev_pairing    = false;
}

void iton_bt_disconnected() {
    print("iton_bt_disconnected()");
    set_output(OUTPUT_USB);
    ev_disconnected = 2500;
    ev_connected    = 0;
    ev_pairing      = false;
    ev_connecting   = false;
}

void iton_bt_battery_level(uint8_t level) {
    print("iton_bt_battery_level()");
    battery_level    = level;
    ev_battery_level = 2500;
}

#endif

/**
 * @brief Set the Bluetooth profile
 *
 * @param profile Bluetooth profile number
 */
static void set_bt_profile(uint8_t profile) {
    // print("set_bt_profile()");
    iton_bt_switch_profile(profile);
    bt_profile = profile;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#ifdef BLUETOOTH_ENABLE
    // Ignore BT commands if BT is disabled
    if (dip_switch_bt_en && record->event.pressed) {
        switch (keycode) {
            case KC_BTPROF0:
                set_bt_profile(0);
                return false;
            case KC_BTPROF1:
                set_bt_profile(1);
                return false;
            case KC_BTPROF2:
                set_bt_profile(2);
                return false;
            case KC_BTPAIR:
                if (dip_switch_bt_en) {
                    iton_bt_enter_pairing();
                }
                return false;
            case KC_BTRST:
                if (dip_switch_bt_en) {
                    iton_bt_reset_pairing();
                }
                return false;
            case KC_BTBATT:
                if (dip_switch_bt_en && record->event.pressed) {
                    ev_battery_level = 10000;
                    iton_bt_query_battery_level();
                }
                return false;
        }
    }
#endif

    // switch (keycode) {
    //     case KC_MISSION_CONTROL:
    //         if (record->event.pressed) {
    //             host_consumer_send(0x29F);
    //         } else {
    //             host_consumer_send(0);
    //         }
    //         return false;
    //     case KC_LAUNCHPAD:
    //         if (record->event.pressed) {
    //             host_consumer_send(0x2A0);
    //         } else {
    //             host_consumer_send(0);
    //         }
    //         return false;
    //     default:
    //         break;
    // }
    return process_record_user(keycode, record);
}

bool dip_switch_update_user(uint8_t index, bool active) {
    dprintf("DIP #%d: %d\n", index, active);
    switch (index) {
        case DIP_WIN_MAC:
            if (active) {
                layer_move(MAC_BASE);
            } else {
                layer_move(WIN_BASE);
            }
            return false;
#ifdef BLUETOOTH_ENABLE
        case DIP_BT_EN:
            dip_switch_bt_en = active;
            if (active) {
                set_output(OUTPUT_USB);
            } else {
                iton_bt_init();
                set_output(OUTPUT_NONE);
            }
            return false;
#endif
    }

    return true;
}
