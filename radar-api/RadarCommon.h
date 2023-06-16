/**
 * @file
 *
 * @brief Common data types and enums for RadarSensor interface.
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

#ifndef RADAR_API_RADAR_COMMON_H_
#define RADAR_API_RADAR_COMMON_H_

#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------
//----- Constants ----------------------
//--------------------------------------

//! A list of possible status/return codes that API can report back.
typedef uint16_t RadarReturnCode;

//! A default undefined value that should be used at initialization.
#define RC_UNDEFINED                        0
//! Operation completed successfully.
#define RC_OK                               1
//! Operation failed and no more information can be provided.
#define RC_ERROR                            2
//! Input parameters are invalid or out of supported range.
#define RC_BAD_INPUT                        3
//! Operation timed out.
#define RC_TIMEOUT                          4
//! Operation cannot be performed at the current state.
#define RC_BAD_STATE                        5
//! Operation failed due to limited resources (memory, timers, mutexes, etc).
#define RC_RES_LIMIT                        6
//! Operation is not supported.
#define RC_UNSUPPORTED                      7
//! An internal system error that should never happen.
#define RC_OOPS                             8

//! A list of radar types.
typedef uint8_t RadarType;

//! A default undefined value that should be used at initialization.
#define RTYPE_UNDEFINED                     0
//! Radar type as Frequency Modulated Continuous Wave.
#define RTYPE_FMCW                          1
//! Radar type as Impulse.
#define RTYPE_PULSED                        2
//! Radar type as Ultra Wide Band.
#define RTYPE_UWB                           3

//! A list of radar sample data types.
typedef uint32_t RadarSampleDType;

//! A default undefined value that should be used at initialization.
#define RSAMPLE_DTYPE_UNDEFINED             0
//! Radar sample data type as integer.
#define RSAMPLE_DTYPE_INT                   1
//! Radar sample data type as unsigned integer.
#define RSAMPLE_DTYPE_UINT                  2
//! Radar sample data type as complex integer.
#define RSAMPLE_DTYPE_CINT                  3
//! Radar sample data type as complex unsigned integer.
#define RSAMPLE_DTYPE_CUINT                 4
//! Radar sample data type as float.
#define RSAMPLE_DTYPE_FLOAT                 5
//! Radar sample data type as complex float.
#define RSAMPLE_DTYPE_CFLOAT                6

//! A list of possible power mode states for radar sensors.
typedef uint16_t RadarState;

//! A default undefined value that should be used at initialization.
#define RSTATE_UNDEFINED                    0
//! Active state when radar is emitting/collecting data started.
#define RSTATE_ACTIVE                       1
//! Idle state when the radar is neither ACTIVE nor SLEEP nor OFF.
#define RSTATE_IDLE                         2
//! Sleep state when configuration persists but power consumption reduced.
#define RSTATE_SLEEP                        3
//! When radar is currently turned off and configuration is reset.
#define RSTATE_OFF                          4

//! A list of log levels.
typedef uint32_t RadarLogLevel;

//! A default undefined value that should be used at initialization.
#define RLOG_UNDEFINED                      0
//! None of log messages are requested.
#define RLOG_OFF                            1
//! Provide only log messages about occurred errors.
#define RLOG_ERR                            2
//! Provide log messages same as for RLOG_ERR and warnings.
#define RLOG_WRN                            3
//! Provide log messages same as for RLOG_WRN and informative changes.
#define RLOG_INF                            4
//! Provide log messages same as for RLOG_INF and debugging info details.
#define RLOG_DBG                            5


//--------------------------------------
//----- Main Params --------------------
//--------------------------------------

//! A list of radar sensor parameters group IDs.
typedef uint16_t RadarParamGroup;

//! A default undefined value that should be used at initialization.
#define RADAR_PARAM_GROUP_UNDEFINED         0
//! A group ID for main params that are common across radars.
#define RADAR_PARAM_GROUP_COMMON            1
//! A group ID dedicated for FMCW kind of radars.
#define RADAR_PARAM_GROUP_FMCW              2
//! A group ID dedicated for Pulsed kind of radars.
#define RADAR_PARAM_GROUP_PULSED            3
//! A group ID dedicated for UWB kind of radars.
#define RADAR_PARAM_GROUP_UWB               4

//! A list of radar sensor parameters that define main characteristics.
//! A configuration slot can hold only 1 value for each MainParam.
typedef uint16_t RadarMainParamId;

//! A general container for a main parameter that defines its group and ID.
typedef struct RadarMainParam_s {
  //! Group ID that radar main param belongs to.
  RadarParamGroup group;
  //! Param ID that belongs to the specified group.
  RadarMainParamId id;
} RadarMainParam;

// Common radar main params.

//! A default undefined value that should be used at initialization.
#define RADAR_PARAM_UNDEFINED               0
//! Power mode for after the burst period.
#define RADAR_PARAM_AFTERBURST_POWER_MODE   1
//! Duration between the start times of two consecutive bursts.
#define RADAR_PARAM_BURST_PERIOD_US         2
//! Bit mask for enabled TX antennas.
#define RADAR_PARAM_TX_ANTENNA_MASK         3
//! Bit mask for enabled RX antennas.
#define RADAR_PARAM_RX_ANTENNA_MASK         4

// FMCW specific main params.

//! A default undefined value that should be used at initialization.
#define FMCW_PARAM_UNDEFINED                0
//! Power mode for the period between chirps.
#define FMCW_PARAM_INTERCHIRP_POWER_MODE    1
//! Duration between the start times of two consecutive chirps.
#define FMCW_PARAM_CHIRP_PERIOD_US          2
//! Amount of chirps within the burst.
#define FMCW_PARAM_CHIRPS_PER_BURST         3
//! The number of ADC sample values captured for each chirp.
#define FMCW_PARAM_SAMPLES_PER_CHIRP        4
//! The lower frequency at what TX antenna starts emitting the signal.
#define FMCW_PARAM_LOWER_FREQ_MHZ           5
//! The upper frequency at what TX antenna stops emitting the signal.
#define FMCW_PARAM_UPPER_FREQ_MHZ           6
//! ADC sampling frequency.
#define FMCW_PARAM_ADC_SAMPLING_HZ          7

// PULSED specific main params.

//! A default undefined value that should be used at initialization.
#define PULSED_PARAM_UNDEFINED              0
//! Power mode for the period between sweeps.
#define PULSED_PARAM_INTERSWEEP_POWER_MODE  1
//! The duration between the start times of two consecutive Radar sweeps.
#define PULSED_PARAM_SWEEP_PERIOD_US        2
//! The number of Radar sweeps within the Radar burst.
#define PULSED_PARAM_SWEEPS_PER_BURST       3
//! The number of samples captured for each Radar sweep.
#define PULSED_PARAM_SAMPLES_PER_SWEEP      4
//! Length of offset in number of samples to limit retrieved channel data.
#define PULSED_PARAM_START_OFFSET           5
//! Pulse Repetition Frequency. Use get param range API to get min/max value.
#define PULSED_PARAM_PRF_IDX                6

// UWB specific main params.

//! A default undefined value that should be used at initialization.
#define UWB_PARAM_UNDEFINED                 0
//! UWB channel number to be used.
#define UWB_PARAM_INTERSWEEP_POWER_MODE     1
//! The duration between the start times of two consecutive Radar sweeps.
#define UWB_PARAM_SWEEP_PERIOD_US           2
//! The number of Radar sweeps within the Radar burst.
#define UWB_PARAM_SWEEPS_PER_BURST          3
//! The number of samples captured for each Radar sweep.
#define UWB_PARAM_SAMPLES_PER_SWEEP         4
//! Length of offset in number of samples to limit retrieved channel data.
#define UWB_PARAM_START_OFFSET              5
//! UWB channel number to be used.
#define UWB_PARAM_PRF_IDX                   6
//! UWB channel number to be used.
#define UWB_RADAR_CHANNEL_NUMBER            7
//! Ranging frame configuration used to transmit/receive ranging messages.
#define UWB_RADAR_PARAM_STS_PACKET_CONFIG   8
//! Length of preamble in symbols repetitions.
#define UWB_RADAR_PARAM_PREAMBLE_LENGTH     9
//! Preamble code index to be used as per IEEE 802.15.4a and 802.15.4z.
#define UWB_RADAR_PARAM_PREAMBLE_IDX        10
//! The priority value for the radar session.
#define UWB_RADAR_PARAM_SESSION_PRIORITY    11
//! Size of single sample in bits including real and imaginary parts.
#define UWB_RADAR_BITS_PER_SAMPLE           12
//! Maximum number of bursts to be executed before radar automatically changes
//! state to not active.
#define UWB_RADAR_NUMBER_OF_BURSTS          13


//--------------------------------------
//----- TX Params ----------------------
//--------------------------------------

//! A TX antennas specific list of parameters.
typedef uint16_t RadarTxParamId;

typedef struct RadarTxParam_s {
  RadarParamGroup group;
  RadarTxParamId id;
} RadarTxParam;

// Common radar TX params.

//! A default undefined value that should be used at initialization.
#define RADAR_TX_PARAM_UNDEFINED            0

// FMCW specific TX params.

//! A default undefined value that should be used at initialization.
#define FMCW_TX_PARAM_UNDEFINED             0
//! A TX antenna emitting power index on scale defined by min/max range.
#define FMCW_TX_PARAM_POWER_IDX             1

// PULSED specific TX params.

//! A default undefined value that should be used at initialization.
#define PULSED_TX_PARAM_UNDEFINED           0
//! A TX antenna emitting power index on scale defined by min/max range.
#define PULSED_TX_PARAM_POWER_IDX           1

// UWB specific TX params.

//! A default undefined value that should be used at initialization.
#define UWB_TX_PARAM_UNDEFINED              0
//! A TX antenna emitting power index on scale defined by min/max range.
#define UWB_TX_PARAM_POWER_IDX              1


//--------------------------------------
//----- TX Params ----------------------
//--------------------------------------

//! A RX antennas specific list of parameters.
typedef uint32_t RadarRxParamId;

typedef struct RadarRxParam_s {
  RadarParamGroup group;
  RadarRxParamId id;
} RadarRxParam;

// Common radar RX params.

//! A default undefined value that should be used at initialization.
#define RADAR_RX_PARAM_UNDEFINED            0

// FMCW specific RX params.

//! A default undefined value that should be used at initialization.
#define FMCW_RX_PARAM_UNDEFINED             0
//! Variable Gain Amplifiers (VGA) index on scale defined by min/max range.
#define FMCW_RX_PARAM_VGA_IDX               1
//! High Phase (HP) filter gain index on scale defined by min/max range.
#define FMCW_RX_PARAM_HP_GAIN_IDX           2
//! High Phase (HP) cut off frequency in kHz.
#define FMCW_RX_PARAM_HP_CUTOFF_KHZ         3

// PULSED specific RX params.

//! A default undefined value that should be used at initialization.
#define PULSED_RX_PARAM_UNDEFINED           0
//! Variable Gain Amplifiers (VGA) on scale defined by min/max range.
#define PULSED_RX_PARAM_VGA_IDX             1

// UWB specific RX params.

//! A default undefined value that should be used at initialization.
#define UWB_RX_PARAM_UNDEFINED              0


//--------------------------------------
//----- Vendor Params ------------------
//--------------------------------------

//! Forward declaration for a list of vendor specific parameters.
typedef uint32_t RadarVendorParam;
//! Forward declaration for a list of vendor specific TX parameters.
typedef uint32_t RadarVendorTxParam;
//! Forward declaration for a list of vendor specific RX parameters.
typedef uint32_t RadarVendorRxParam;


//--------------------------------------
//----- Data types ---------------------
//--------------------------------------

//! Describes a data format of burst data.
typedef struct RadarBurstFormat_s {
  uint32_t sequence_number;
  RadarType radar_type;
  uint8_t config_id;
  RadarSampleDType sample_data_type;
  uint8_t bits_per_sample;

  uint8_t num_channels;
  uint8_t is_channels_interleaved;
  uint8_t is_big_endian;
  uint8_t reserved_1;

  // Custom radar specific fields.
  union {
    struct {
      uint16_t samples_per_chirp;
      uint16_t chirps_per_burst;
    } fmcw;
    struct {
      uint16_t samples_per_sweep;
      uint16_t sweeps_per_burst;
    } pusled;
    struct {
      uint32_t session_handle;
      uint16_t samples_per_sweep;
      uint16_t sweeps_per_burst;
    } uwb;
  } custom;

} RadarBurstFormat;

//! A semantic version holder.
typedef struct Version_s {
  uint8_t major;
  uint8_t minor;
  uint8_t patch;
  uint8_t build;
} Version;

//! The general information about the radar sensor hardware and software.
typedef struct SensorInfo_s {
  //! Name of the radar sensor.
  const char* name;
  //! Vendor name.
  const char* vendor;
  //! ID that identifies this sensor.
  uint32_t device_id;
  //! Radar type.
  RadarType radar_type;
  //! The radar driver version.
  Version driver_version;
} SensorInfo;

//! The very basic way to get the Radar API version supported by the driver.
Version radarGetRadarApiVersion(void);

#ifdef __cplusplus
}
#endif

#endif // RADAR_API_RADAR_COMMON_H_
