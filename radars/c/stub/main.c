// Copyright 2022 Google LLC.

#include <IRadarSensor.h>

//--------------------------------------
//----- Consts --- ---------------------
//--------------------------------------

//--------------------------------------
//----- Data types ---------------------
//--------------------------------------

typedef struct RadarHandleImpl_s {
  uint32_t stub_field;
} RadarHandleImpl;

//--------------------------------------
//----- API ----------------------------
//--------------------------------------

// Lifecycle.

RadarReturnCode radarInit(void) {
  return RC_UNSUPPORTED;
}

RadarReturnCode radarDeinit(void) {
  return RC_UNSUPPORTED;
}

RadarHandle* radarCreate(int32_t id) {
  (void) id;
  return NULL;
}

RadarReturnCode radarDestroy(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetState(RadarHandle* handle, RadarState* state) {
  (void) handle;
  (void) state;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarTurnOn(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarTurnOff(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGoSleep(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarWakeUp(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

// Configuration.

RadarReturnCode radarGetNumConfigSlots(RadarHandle* handle,
                                       uint8_t* num_slots) {
  (void) handle;
  (void) num_slots;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetMaxActiveConfigSlots(RadarHandle* handle,
    uint8_t* num_slots) {
  (void) handle;
  (void) num_slots;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarActivateConfig(RadarHandle* handle, uint8_t slot_id) {
  (void) handle;
  (void) slot_id;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarDeactivateConfig(RadarHandle* handle, uint8_t slot_id) {
  (void) handle;
  (void) slot_id;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarIsActiveConfig(RadarHandle* handle, uint8_t slot_id,
                                    bool* is_active) {
  (void) handle;
  (void) slot_id;
  (void) is_active;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetMainParam(RadarHandle* handle, uint8_t slot_id,
                                  RadarMainParam param, uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetMainParam(RadarHandle* handle, uint8_t slot_id,
                                  RadarMainParam param, uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetMainParamRange(RadarHandle* handle,
                                       RadarMainParam param,
                                       uint32_t* min_value,
                                       uint32_t* max_value) {
  (void) handle;
  (void) param;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetTxParam(RadarHandle* handle, uint8_t slot_id,
                                uint32_t antenna_mask, RadarTxParam param,
                                uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetTxParam(RadarHandle* handle, uint8_t slot_id,
                                uint32_t antenna_mask, RadarTxParam param,
                                uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetTxParamRange(RadarHandle* handle, RadarTxParam param,
                                     uint32_t* min_value,
                                     uint32_t* max_value) {
  (void) handle;
  (void) param;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetRxParam(RadarHandle* handle, uint8_t slot_id,
                                uint32_t antenna_mask, RadarRxParam param,
                                uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetRxParam(RadarHandle* handle, uint8_t slot_id,
                                uint32_t antenna_mask, RadarRxParam param,
                                uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}


RadarReturnCode radarGetRxParamRange(RadarHandle* handle, RadarRxParam param,
                                     uint32_t* min_value,
                                     uint32_t* max_value) {
  (void) handle;
  (void) param;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorParam(RadarHandle* handle, uint8_t slot_id,
                                    RadarVendorParam param, uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetVendorParam(RadarHandle* handle, uint8_t slot_id,
                                    RadarVendorParam param, uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) param;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorParamRange(RadarHandle* handle,
    RadarVendorParam id, uint32_t* min_value, uint32_t* max_value) {
  (void) handle;
  (void) id;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorTxParam(RadarHandle* handle, uint8_t slot_id,
    uint32_t antenna_mask, RadarVendorTxParam id, uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) id;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetVendorTxParam(RadarHandle* handle, uint8_t slot_id,
    uint32_t antenna_mask, RadarVendorTxParam id, uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) id;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorTxParamRange(RadarHandle* handle,
    RadarVendorTxParam id, uint32_t* min_value, uint32_t* max_value) {
  (void) handle;
  (void) id;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorRxParam(RadarHandle* handle, uint8_t slot_id,
    uint32_t antenna_mask, RadarVendorRxParam id, uint32_t* value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) id;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetVendorRxParam(RadarHandle* handle, uint8_t slot_id,
    uint32_t antenna_mask, RadarVendorRxParam id, uint32_t value) {
  (void) handle;
  (void) slot_id;
  (void) antenna_mask;
  (void) id;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetVendorRxParamRange(RadarHandle* handle,
    RadarVendorRxParam id, uint32_t* min_value, uint32_t* max_value) {
  (void) handle;
  (void) id;
  (void) min_value;
  (void) max_value;
  return RC_UNSUPPORTED;
}

// Running.

RadarReturnCode radarStartDataStreaming(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarStopDataStreaming(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarIsBurstReady(RadarHandle* handle, bool* is_ready) {
  (void) handle;
  (void) is_ready;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarReadBurst(RadarHandle* handle, RadarBurstFormat* format,
                               uint8_t* buffer, uint32_t* read_bytes,
                               struct timespec timeout) {
  (void) handle;
  (void) format;
  (void) buffer;
  (void) read_bytes;
  (void) timeout;
  return RC_UNSUPPORTED;
}

// Feedback.

RadarReturnCode radarSetBurstReadyCb(RadarHandle* handle, RadarBurstReadyCB cb,
                                     void* user_data) {
  (void) handle;
  (void) cb;
  (void) user_data;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetLogCb(RadarHandle* handle, RadarLogCB cb,
                              void* user_data) {
  (void) handle;
  (void) cb;
  (void) user_data;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetRegisterSetCb(RadarHandle* handle,
                                      RadarRegisterSetCB cb, void* user_data) {
  (void) handle;
  (void) cb;
  (void) user_data;
  return RC_UNSUPPORTED;
}

// Miscellaneous.

RadarReturnCode radarCheckCountryCode(RadarHandle* handle,
                                      const char* country_code) {
  (void) handle;
  (void) country_code;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetSensorInfo(RadarHandle* handle, SensorInfo* info) {
  (void) handle;
  (void) info;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarLogSensorDetails(RadarHandle* handle) {
  (void) handle;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetTxPosition(RadarHandle* handle,
    uint32_t tx_mask, int32_t* x, int32_t* y, int32_t* z) {
  (void) handle;
  (void) tx_mask;
  (void) x;
  (void) y;
  (void) z;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetRxPosition(RadarHandle* handle,
    uint32_t rx_mask, int32_t* x, int32_t* y, int32_t* z) {
  (void) handle;
  (void) rx_mask;
  (void) x;
  (void) y;
  (void) z;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetLogLevel(RadarHandle* handle, RadarLogLevel level) {
  (void) handle;
  (void) level;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetAllRegisters(RadarHandle* handle, uint32_t* addresses,
                                     uint32_t* values, uint32_t* count) {
  (void) handle;
  (void) addresses;
  (void) values;
  (void) count;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarGetRegister(RadarHandle* handle, uint32_t address,
                                 uint32_t* value) {
  (void) handle;
  (void) address;
  (void) value;
  return RC_UNSUPPORTED;
}

RadarReturnCode radarSetRegister(RadarHandle* handle, uint32_t address,
                                 uint32_t value) {
  (void) handle;
  (void) address;
  (void) value;
  return RC_UNSUPPORTED;
}
