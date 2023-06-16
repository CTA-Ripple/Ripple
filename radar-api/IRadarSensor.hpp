/**
 * @file
 *
 * @details
 *
 * ```
 * Copyright 2022 CTA Radar API Technical Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ```
 */

#ifndef I_RADAR_SENSOR_HPP_
#define I_RADAR_SENSOR_HPP_

#include "RadarCommon.h"

#include <cstdint>
#include <string>
#include <time.h>
#include <vector>

//--------------------------------------
//----- Enums --------------------------
//--------------------------------------

namespace radar_api {

//--------------------------------------
//----- Data types ---------------------
//--------------------------------------

/**
 * @brief A Radar data observer that allows application to be notified
 *        about it's events.
 */
class IRadarSensorObserver {
 public:
  virtual ~IRadarSensorObserver(){}

  /**
   * @brief An interface function declaration that will be invoked
   *        when a new burst is ready for read. Can be set using
   *        radarSetBurstReadyCb function.
   *
   */
  virtual void OnBurstReady(void) = 0;

  /**
   * @brief An interface function declaration that will be invoked
   *        when a new log message is available from the radar driver.
   *        The callback can be registered with radarSetLogCb function.
   *        Run time log level can be set using radarSetLogLevel function.
   *
   * @param level a level of the current log message.
   * @param file a source file name where the log message is generated.
   *        The value is set by a compiler and embedded into the code.
   * @param function a function name where the log message is generated.
   *        The value is set by a compiler and embedded into the code.
   * @param line a line number within a file where the log message is generated.
   * @param message a completely formed log message.
   *
   */
  virtual void OnLogMessage(RadarLogLevel level, const char* file,
                            const char* function,
                            int line, const std::string& message) = 0;

  /**
   * @brief An interface function declaration that will be invoked
   *        when the radar driver sets a new value for the sensor chip register.
   *
   * @param address a register's address.
   * @param value a new value to be set in the register.
   *
   */
  virtual void OnRegisterSet(uint32_t address, uint32_t value) = 0;
};

//--------------------------------------
//----- API ----------------------------
//--------------------------------------

class IRadarSensor {
 public:
  virtual ~IRadarSensor(){}

  // Feedback

  /**
   * @brief Add a new observer object.
   *
   * @detils Add a new observer object that will get notified about
   *         the Radar sensor activity.
   *
   * @note Log messages will not be generated during execution of
   *       ctor/dtor and AddObserver/RemoveObserver API.
   *
   * @param observer pointer to the implmenetation of the interface to add.
   */
  virtual RadarReturnCode AddObserver(IRadarSensorObserver* observer) = 0;

  /**
   * @brief Remove the observer.
   *
   * @details Remove the previously registered observer from subscribers list.
   *
   * @note Log messages will not be generated during execution of
   *       ctor/dtor and AddObserver/RemoveObserver API.
   *
   * @param observer pointer to the implmenetation of the interface to remove.
   */
  virtual RadarReturnCode RemoveObserver(IRadarSensorObserver* observer) = 0;


  // Power management.

  /**
   * @brief Get the current power state.
   *
   * @param state a pointer to the state that will be set.
   */
  virtual RadarReturnCode GetRadarState(RadarState& state) = 0;

  /**
   * @brief Turn on the radar.
   */
  virtual RadarReturnCode TurnOn(void) = 0;

  /**
   * @brief Turn off the radar.
   */
  virtual RadarReturnCode TurnOff(void) = 0;

  /**
   * @brief Put the radar to sleep and preserve configuration.
   */
  virtual RadarReturnCode GoSleep(void) = 0;

  /**
   * @brief Wake up the radar.
   */
  virtual RadarReturnCode WakeUp(void) = 0;

  // Configuration.

  /**
   * Get the total available configuration slots.
   *
   * @param num_slots where the number of config slots to write.
   */
  virtual RadarReturnCode GetNumConfigSlots(uint8_t& num_slots) = 0;

  /**
   * @brief Get the maximum number of activated configuration slots.
   *
   * @param num_slots where the maximum number of
   *        active config slots to write.
   */
  virtual RadarReturnCode GetMaxActiveConfigSlots(uint8_t& num_slots) = 0;

  /**
   * @brief Activate a specified configuration slot. Does not start the radar.
   *
   * @param slot_id a configuration slot ID to activate.
   *
   * @note This function will perform the final configuration check for
   *       compatibility before activating.
   */
  virtual RadarReturnCode ActivateConfig(uint8_t slot_id) = 0;

  /**
   * @brief Deactivate a specified configuration slot.
   *
   * @param slot_id a configuration slot ID to deactivate.
   */
  virtual RadarReturnCode DeactivateConfig(uint8_t slot_id) = 0;

  /**
   * @brief Check if the configuration slot is active.
   *
   * @param slot_ids a vector to be filled with IDs of
   *        active config slots.
   */
  virtual RadarReturnCode GetActiveConfigs(std::vector<uint8_t>& slot_ids) = 0;

  /**
   * @brief Get a main radar parameter.
   *
   * @param slot_id a configuration slot ID where to read the parameter value.
   * @param id a parameter ID to be read.
   * @param value where a parameter value will be written into.
   */
  virtual RadarReturnCode GetMainParam(uint8_t slot_id, RadarMainParam param,
      uint32_t& value) = 0;

  /**
   * @brief Set a main radar parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param id a parameter ID to be set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetMainParam(uint8_t slot_id, RadarMainParam param,
      uint32_t value) = 0;

  /**
   * @brief Get a main radar parameter range of acceptable values.
   *
   * @param id a parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be set.
   * @param max_value where a maximum parameter value will be set.
   */
  virtual RadarReturnCode GetMainParamRange(RadarMainParam param,
      uint32_t& min_value, uint32_t& max_value) = 0;

  /**
   * @brief Get a TX specific parameter.
   *
   * @param slot_id a configuration slot ID where to read the parameter value.
   * @param antenna_mask antenna bit mask from which to get the parameter value.
   *                     Only one bit should be set.
   * @param id a parameter ID to read.
   * @param value to where a parameter value will be written into.
   */
  virtual RadarReturnCode GetTxParam(uint8_t slot_id, uint32_t antenna_mask,
      RadarTxParam param, uint32_t& value) = 0;

  /**
   * @brief Set a TX specific parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param antenna_mask antenna bit mask for which to get the parameter value.
   * @param id a parameter ID to set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetTxParam(uint8_t slot_id, uint32_t antenna_mask,
      RadarTxParam param, uint32_t value) = 0;

  /**
   * @brief Get a TX antenna parameter range of acceptable values.
   *
   * @param id a parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be set.
   * @param max_value where a maximum parameter value will be set.
   */
  virtual RadarReturnCode GetTxParamRange(RadarTxParam id,
      uint32_t& min_value, uint32_t& max_value) = 0;

  /**
   * @brief Get a RX specific parameter.
   *
   * @param slot_id a configuration slot ID where to read the parameter value.
   * @param antenna_mask antenna bit mask from which to get the parameter value.
   *                     Only one bit should be set.
   * @param id a parameter ID to read.
   * @param value to where a parameter value will be written into.
   */
  virtual RadarReturnCode GetRxParam(uint8_t slot_id, uint32_t antenna_mask,
      RadarRxParam param, uint32_t& value) = 0;

  /**
   * @brief Set a RX specific parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param antenna_mask antenna bit mask for which to get the parameter value.
   * @param id a parameter ID to set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetRxParam(uint8_t slot_id, uint32_t antenna_mask,
      RadarRxParam param, uint32_t value) = 0;

  /**
   * @brief Get a RX antenna parameter range of acceptable values.
   *
   * @param id a parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be set.
   * @param max_value where a maximum parameter value will be set.
   */
  virtual RadarReturnCode GetRxParamRange(RadarRxParam param,
      uint32_t& min_value, uint32_t& max_value) = 0;

  /**
   * @brief Get a vendor specific parameter.
   *
   * @param slot_id a configuration slot ID where to read a parameter value.
   * @param id a vendor specific parameter ID to read.
   * @param value to where a parameter value will be written into.
   */
  virtual RadarReturnCode GetVendorParam(uint8_t slot_id,
      RadarVendorParam param, uint32_t& value) = 0;

  /**
   * @brief Set a vendor specific parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param id a parameter ID to set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetVendorParam(uint8_t slot_id,
      RadarVendorParam param, uint32_t value) = 0;

  /**
   * @brief Get a vendor specific radar parameter range of acceptable values.
   *
   * @param id a vendor parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be set.
   * @param max_value where a maximum parameter value will be set.
   */
  virtual RadarReturnCode GetVendorParamRange(RadarVendorParam id,
      uint32_t& min_value, uint32_t& max_value) = 0;

  /**
   * @brief Get a vendor specific TX parameter.
   *
   * @param slot_id a configuration slot ID where to read the parameter value.
   * @param antenna_mask antenna bit mask from which to get the parameter value.
   *                     Only one bit should be set.
   * @param id a parameter ID to read.
   * @param value to where a parameter value will be written into.
   */
  virtual RadarReturnCode GetVendorTxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorTxParam id, uint32_t& value) = 0;

  /**
   * @brief Set a vendor specific TX parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param antenna_mask antenna bit mask for which to get the parameter value.
   * @param id a parameter ID to set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetVendorTxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorTxParam id, uint32_t value) = 0;

  /**
   * @brief Get a vendor specific TX parameter range of acceptable values.
   *
   * @param id a parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be returned.
   * @param max_value where a maximum parameter value will be returned.
   */
  virtual RadarReturnCode GetVendorTxParamRange(RadarVendorTxParam id,
      uint32_t& min_value, uint32_t& max_value) = 0;

  /**
   * @brief Get a vendor specific RX parameter.
   *
   * @param slot_id a configuration slot ID where to read the parameter value.
   * @param antenna_mask antenna bit mask from which to get the parameter value.
   *                     Only one bit should be set.
   * @param id a parameter ID to read.
   * @param value to where a parameter value will be written into.
   */
  virtual RadarReturnCode GetVendorRxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorRxParam id, uint32_t& value) = 0;

  /**
   * @brief Set a vendor specific RX parameter.
   *
   * @param slot_id a configuration slot ID where to set a new parameter value.
   * @param antenna_mask antenna bit mask for which to get the parameter value.
   * @param id a parameter ID to set.
   * @param value a new value for the parameter.
   */
  virtual RadarReturnCode SetVendorRxParam(uint8_t slot_id,
      uint32_t antenna_mask, RadarVendorRxParam id, uint32_t value) = 0;

  /**
   * @brief Get a vendor specific RX parameter range of acceptable values.
   *
   * @param id a parameter ID which range of values to read.
   * @param min_value where a minimum parameter value will be returned.
   * @param max_value where a maximum parameter value will be returned.
   */
  virtual RadarReturnCode GetVendorRxParamRange(RadarVendorRxParam id,
      uint32_t& min_value, uint32_t& max_value) = 0;

  // Running.

  /**
   * @brief Start running the radar with active configuration.
   */
  virtual RadarReturnCode StartDataStreaming(void) = 0;

  /**
   * @brief Stop running the radar.
   */
  virtual RadarReturnCode StopDataStreaming(void) = 0;

  /**
   * @brief Check if the radar has a new burst ready to read.
   *
   * @param is_ready where the result will be set.
   */
  virtual RadarReturnCode IsBurstReady(bool& is_ready) = 0;

  /**
   * @brief Initiate reading a new burst.
   *
   * @param format where a new burst format will be written into.
   * @param raw_radar_data where a burst data to be written.
   * @param timeout the maximum time to wait if the burst frame is not ready.
   */
  virtual RadarReturnCode ReadBurst(RadarBurstFormat& format,
      std::vector<uint8_t>& raw_radar_data, timespec timeout) = 0;

  // Miscellaneous.

  /**
   * @brief Checks the availability by a country code.
   *
   * @details Checks if local regulations allow the current sensor
   *        to operate.
   *
   * @param country_code a ISO 3166-1 alpha-2 country code.
   */
  virtual RadarReturnCode CheckCountryCode(const std::string& country_code) = 0;

  /**
   * @brief Get radar sensor info.
   *
   * @param info where the sensor info to be filled in.
   */
  virtual RadarReturnCode GetSensorInfo(SensorInfo& info) = 0;

  /**
   * @brief Logs sensor detailed information.
   *
   * @details Gets detailed sensor information and passes it
   *        to registered observers via OnLogMessage callback
   *        with a RLOG_INF log level.
   */
  virtual RadarReturnCode LogSensorDetails(void) = 0;

  /**
   * @brief Get TX antenna position offset in micrometers from a fixed origin.
   *
   * @param tx_mask bit mask of a single TX antenna which positiion to retrieve.
   * @param x where the x offset (um) to be written.
   * @param y where the y offset (um) to be written.
   * @param z where the z offset (um) to be written.
   */
  virtual RadarReturnCode GetTxPosition(uint32_t tx_mask,
      int32_t& x, int32_t& y, int32_t& z) = 0;

  /**
   * @brief Get RX antenna position offset in micrometers from a fixed origin.
   *
   * @param rx_mask bit mask of a single RX antenna which positiion to retrieve.
   * @param x where the x offset (um) to be written.
   * @param y where the y offset (um) to be written.
   * @param z where the z offset (um) to be written.
   */
  virtual RadarReturnCode GetRxPosition(uint32_t rx_mask,
      int32_t& x, int32_t& y, int32_t& z) = 0;

  /**
   * @brief Set a run time log level for radar API impl.
   *
   * @param level new log level.
   */
  virtual RadarReturnCode SetLogLevel(RadarLogLevel level) = 0;

  /**
   * @brief Get all register values from the radar sensor.
   *
   * @param registers where the pair of register's address and value
   *        to be written.
   */
  virtual RadarReturnCode GetAllRegisters(
      std::vector<std::pair<uint32_t, uint32_t>>& registers) = 0;

  /**
   * @brief Get a register value directly from the sensor.
   *
   * @param address an address to read.
   * @param value where the register's value will be written into.
   */
  virtual RadarReturnCode GetRegister(uint32_t address, uint32_t& value) = 0;

  /**
   * @brief Set a register value directly to the sensor.
   *
   * @param address an address of the register to set.
   * @param value a new value to set.
   */
  virtual RadarReturnCode SetRegister(uint32_t address, uint32_t value) = 0;
};

//--------------------------------------
//----- Static API ---------------------
//--------------------------------------

/**
 * @brief Initializes the radar module.
 *
 * @note This function should be called before any
 *        other radar related API.
 */
RadarReturnCode RadarSensorInit(void);

/**
 * @brief Deinitializes the radar module.
 *
 * @note This function should be called after any
 *        other radar related API.
 */
RadarReturnCode RadarSensorDeinit(void);

/**
 * @brief Create an intsance of the RadarSensor implementation.
 *
 * @param id a unique identifier of the radar chip.
 *        Can be used to differentiate if multiple radar available at the
 *        same time.
 *
 * @return Pointer to the RadarSensor implementation.
 */
IRadarSensor* CreateRadarSensor(int32_t id);

/**
 * @brief Destroy the instance of the RadarSensor implementation.
 *
 * @param radar pointer to the instance to be destroyed.
 */
RadarReturnCode DestroyRadarSensor(IRadarSensor* radar);

} // namespace radar_api

#endif // I_RADAR_SENSOR_HPP_
