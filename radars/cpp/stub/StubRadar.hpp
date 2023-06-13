// Copyright 2022 Google LLC.

/**
 *
 * @brief Stub implementation for Ripple Radar API C++.
 *        All the returns are default or RC_UNSUPPORTED
 *        except Create/Destroy radar.
 *
 */
#ifndef RIPPLE_RADARS_CPP_STUBRADAR_HPP_
#define RIPPLE_RADARS_CPP_STUBRADAR_HPP_

#include <IRadarSensor.hpp>

namespace radar_api {
class StubRadar: public IRadarSensor {
 public:
  StubRadar(int32_t id) {
    (void) id;
    (void) stub_field;
  }

  ~StubRadar() {
  }

  // RadarSensor interface.

  // Feedback.
  RadarReturnCode AddObserver(IRadarSensorObserver* observer) {
    (void) observer;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode RemoveObserver(IRadarSensorObserver* observer) {
    (void) observer;
    return RC_UNSUPPORTED;
  }

  // State management.
  RadarReturnCode GetRadarState(RadarState& state) {
    (void) state;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode TurnOn(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode TurnOff(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GoSleep(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode WakeUp(void) {
    return RC_UNSUPPORTED;
  }


  // Configuration.
  RadarReturnCode GetNumConfigSlots(uint8_t& num_slots) {
    (void) num_slots;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetMaxActiveConfigSlots(uint8_t& num_slots) {
    (void) num_slots;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode ActivateConfig(uint8_t slot_id) {
    (void) slot_id;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode DeactivateConfig(uint8_t slot_id) {
    (void) slot_id;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetActiveConfigs(std::vector<uint8_t>& slot_ids) {
    (void) slot_ids;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetMainParam(uint8_t slot_id, RadarMainParam id,
                               uint32_t& value) {
    (void) slot_id;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetMainParam(uint8_t slot_id, RadarMainParam id,
                               uint32_t value) {
    (void) slot_id;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetMainParamRange(RadarMainParam id, uint32_t& min_value,
                                    uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetTxParam(uint8_t slot_id, uint32_t antenna_mask,
                             RadarTxParam id, uint32_t& value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetTxParam(uint8_t slot_id, uint32_t antenna_mask,
                             RadarTxParam id, uint32_t value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetTxParamRange(RadarTxParam id,
                                  uint32_t& min_value,
                                  uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetRxParam(uint8_t slot_id, uint32_t antenna_mask,
                             RadarRxParam id, uint32_t& value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetRxParam(uint8_t slot_id, uint32_t antenna_mask,
                             RadarRxParam id, uint32_t value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetRxParamRange(RadarRxParam id,
                                  uint32_t& min_value,
                                  uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorParam(uint8_t slot_id, RadarVendorParam id,
                                 uint32_t& value) {
    (void) slot_id;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetVendorParam(uint8_t slot_id, RadarVendorParam id,
                                 uint32_t value) {
    (void) slot_id;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorParamRange(RadarVendorParam id,
      uint32_t& min_value, uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorTxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorTxParam id, uint32_t& value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetVendorTxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorTxParam id, uint32_t value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorTxParamRange(RadarVendorTxParam id,
      uint32_t& min_value, uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorRxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorRxParam id, uint32_t& value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetVendorRxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorRxParam id, uint32_t value) {
    (void) slot_id;
    (void) antenna_mask;
    (void) id;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetVendorRxParamRange(RadarVendorRxParam id,
      uint32_t& min_value, uint32_t& max_value) {
    (void) id;
    (void) min_value;
    (void) max_value;
    return RC_UNSUPPORTED;
  }

  // Running.
  RadarReturnCode StartDataStreaming(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode StopDataStreaming(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode IsBurstReady(bool& is_ready) {
    (void) is_ready;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode ReadBurst(RadarBurstFormat& format,
                            std::vector<uint8_t>& raw_radar_data,
                            timespec timeout) {
    (void) format;
    (void) raw_radar_data;
    (void) timeout;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode CheckCountryCode(const std::string& country_code) {
    (void) country_code;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetSensorInfo(SensorInfo& info) {
    (void) info;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode LogSensorDetails(void) {
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetTxPosition(uint32_t tx_mask,
      int32_t& x, int32_t& y, int32_t& z) {
    (void) tx_mask;
    (void) x;
    (void) y;
    (void) z;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetRxPosition(uint32_t rx_mask,
      int32_t& x, int32_t& y, int32_t& z) {
    (void) rx_mask;
    (void) x;
    (void) y;
    (void) z;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetLogLevel(RadarLogLevel level) {
    (void) level;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetAllRegisters(
      std::vector<std::pair<uint32_t, uint32_t>>& registers) {
    (void) registers;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode GetRegister(uint32_t address, uint32_t& value) {
    (void) address;
    (void) value;
    return RC_UNSUPPORTED;
  }

  RadarReturnCode SetRegister(uint32_t address, uint32_t value) {
    (void) address;
    (void) value;
    return RC_UNSUPPORTED;
  }

 private:
  int stub_field;
};

}  // namespace radar_api

#endif  // RIPPLE_RADARS_CPP_STUBRADAR_HPP_

