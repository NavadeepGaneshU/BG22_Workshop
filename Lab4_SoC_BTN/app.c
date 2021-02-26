/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "em_common.h"
#include "sl_app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include"sl_simple_led_instances.h"
#include"sl_simple_button_instances.h"

// The advertising set handle allocated from Bluetooth stack.
static uint8_t advertising_set_handle = 0xff;

// These variables need to be added and are used for the connection handle
// and the notification parameters to send Button data to the mobile app
uint8_t g_lab4Connection;
uint8_t notification_data[1] = {0};
uint16_t notification_len = 0;
uint8_t notifyEnabled = false;

extern sl_simple_button_context_t simple_btn0_context;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
}
/*
 * Override function for button press that needs to be added.  This function is
 * called in interrupt context and uses the Bluetooth stack external signaling.
 */
void sl_button_on_change(const sl_button_t *handle)
{
  sl_simple_button_context_t *ctxt = ((sl_simple_button_context_t *)handle[0].context);
  if (ctxt->state) {
      ctxt->history += 1;
      sl_bt_external_signal(1);
  }
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to get Bluetooth address\n",
                    (int)sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to write attribute\n",
                    (int)sc);

      // Create an advertising set.
      sc = sl_bt_advertiser_create_set(&advertising_set_handle);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to create advertising set\n",
                    (int)sc);

      // Set advertising interval to 100ms.
      sc = sl_bt_advertiser_set_timing(
        advertising_set_handle,
        160, // min. adv. interval (milliseconds * 1.6)
        160, // max. adv. interval (milliseconds * 1.6)
        0,   // adv. duration
        0);  // max. num. adv. events
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to set advertising timing\n",
                    (int)sc);
      // Start general advertising and enable connections.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        advertiser_general_discoverable,
        advertiser_connectable_scannable);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to start advertising\n",
                    (int)sc);
      break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      // When sending notifications we need the connection handle.  Capture
      // it here
      g_lab4Connection = evt->data.evt_connection_opened.connection;
      break;

    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      // Restart advertising after client has disconnected.
      sc = sl_bt_advertiser_start(
        advertising_set_handle,
        advertiser_general_discoverable,
        advertiser_connectable_scannable);
      sl_app_assert(sc == SL_STATUS_OK,
                    "[E: 0x%04x] Failed to start advertising\n",
                    (int)sc);
      break;

      ///////////////////////////////////////////////////////////////////////////
      // Add additional event handlers here as your application requires!      //
      ///////////////////////////////////////////////////////////////////////////

    case sl_bt_evt_gatt_server_user_write_request_id:
              if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_LED) {
              // Write user supplied value to LEDs.
                  if (evt->data.evt_gatt_server_attribute_value.value.data[0]) {

                    //This is the use of the Simple LED component
                    sl_led_turn_on(&sl_led_led0);
                }
                else {
                    //This is the use of the Simple LED component
                    sl_led_turn_off(&sl_led_led0);
                }
              sl_bt_gatt_server_send_user_write_response(
                  evt->data.evt_gatt_server_user_write_request.connection,
                  gattdb_LED, SL_STATUS_OK);
            }
            break;

        case sl_bt_evt_system_external_signal_id:
         /* Process external signals */
         if (notifyEnabled) {
             if (evt->data.evt_system_external_signal.extsignals == 1)  // 1 = BTN0
             {
                 notification_data[0] = (uint8_t)simple_btn0_context.history;
                // simple_btn0_context.history = 0;   //commenting to accumilate button press count

                 // send number of button presses
                 sc = sl_bt_gatt_server_send_characteristic_notification(
                         g_lab4Connection, gattdb_BTN, sizeof(notification_data),
                         notification_data, &notification_len);
             }
         }
         break;

    case  sl_bt_evt_gatt_server_characteristic_status_id:
        if ((evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_BTN)
            && (evt->data.evt_gatt_server_characteristic_status.status_flags == 0x01)) {
     if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == 0x00) {
           notifyEnabled = false;
     }
     else {
        notifyEnabled = true;
     }
  }
  break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}
