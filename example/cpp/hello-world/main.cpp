// Copyright 2022 Google LLC.

/**
 * @brief An example that demonstrates a usage of a Ripple Radar API C++.
 */
#include <stdlib.h>

#include <platform_check.h>
#include <platform_log.h>

#include <IRadarApi.hpp>

using MainParams = std::vector<std::pair<RadarMainParam, uint32_t>>;
using TxParams =
    std::vector<std::vector<std::pair<RadarTxParam, uint32_t>>>;
using RxParams =
    std::vector<std::vector<std::pair<RadarRxParam, uint32_t>>>;

class RadarObserver: public radar_api::IRadarSensorObserver {
 public:
  void OnBurstReady(void) {
    DLOG("Burst is ready.");
  }

  void OnLogMessage(RadarLogLevel level, const char* file,
      const char* function, int line, const std::string& message) {
    if (level == RLOG_DBG) {
      DLOG("%s:%s:%i %s\n", file, function, line, message.c_str());
    } else if (level == RLOG_INF) {
      ILOG("%s:%s:%i %s\n", file, function, line, message.c_str());
    } else if (level == RLOG_ERR) {
      ELOG("%s:%s:%i %s\n", file, function, line, message.c_str());
    }
  }
  void OnRegisterSet(uint32_t address, uint32_t value) {
    ILOG("Register at %u is set to %u", address, value);
  }
};

int main(int argc, char* argv[]) {
  (void) argc;
  (void) argv;
  ILOG("Raw data streaming example");

  // A few main parameters
  const uint32_t kSamplesPerChirp = 64;
  const uint32_t kChirpsPerBurst = 32;

  // Configure radar for FMCW radar.
  MainParams main_params = {
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_AFTERBURST_POWER_MODE}, 1},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_BURST_PERIOD_US},       40000},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_TX_ANTENNA_MASK},       0x1},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_RX_ANTENNA_MASK},       0x7},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_INTERCHIRP_POWER_MODE},  2},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_CHIRP_PERIOD_US},        500},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_CHIRPS_PER_BURST},       kChirpsPerBurst},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_SAMPLES_PER_CHIRP},      kSamplesPerChirp},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_LOWER_FREQ_MHZ},         58500},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_UPPER_FREQ_MHZ},         63000},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_ADC_SAMPLING_HZ},        2000000}
  };

  TxParams tx_params = {
    // Channel 0.
    {
      { {RADAR_PARAM_GROUP_FMCW, FMCW_TX_PARAM_POWER_IDX},           255},
    },
  };

  RxParams rx_params = {
    // Channel 0.
    {
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_VGA_IDX},             5},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_GAIN_IDX},         30},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_CUTOFF_KHZ},       45}
    },
    // Channel 1.
    {
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_VGA_IDX},             5},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_GAIN_IDX},         30},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_CUTOFF_KHZ},       45}
    },
    // Channel 2.
    {
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_VGA_IDX},             5},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_GAIN_IDX},         30},
      { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_CUTOFF_KHZ},       45}
    }
  };

  ILOG("Initializing radar...");
  RadarReturnCode rc = RC_UNDEFINED;
  radar_api::IRadarSensor* radar = radar_api::CreateRadarSensor(/*radar_id*/ 0);
  QCHECK(radar != nullptr, "Invalid radar handle from driver");

  DLOG("Adding the observer");
  RadarObserver observer;
  rc = radar->AddObserver(&observer);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to add an observer");

  rc = radar->SetLogLevel(RLOG_INF);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to set radar log level");

  uint8_t num_slots = 0;
  DLOG("Getting the number of config slots");
  rc = radar->GetNumConfigSlots(num_slots);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to get number for config slots");
  QCHECK_GE(num_slots, 1, "%u", "Available config slots %u < 1", num_slots);

  // Main params.
  uint8_t slot_id = 0;
  ILOG("Configure main params at slot %u", slot_id);
  for (auto& param : main_params) {
    ILOG("Setting a main param %u.%u value %u",
        param.first.group, param.first.id, param.second);
    rc = radar->SetMainParam(slot_id, param.first, param.second);
    QCHECK_EQ(rc, RC_OK, "%d", "Failed to set main param %u.%u value %u",
        param.first.group, param.first.id, param.second);
  }

  // TX params.
  ILOG("Configure TX params at slot %u", slot_id);
  uint32_t tx_antenna_mask = main_params[RADAR_PARAM_TX_ANTENNA_MASK-1].second;
  uint32_t tx_count = tx_params.size();
  for (uint32_t tx_id = 0; tx_id < tx_count; ++tx_id) {
    if (tx_antenna_mask & 1) {
      for (auto& param : tx_params[tx_id]) {
        ILOG("Setting a TX %u.%u param %u value %u", tx_id,
             param.first.group, param.first.id, param.second);
        rc = radar->SetTxParam(slot_id, (1 << tx_id), param.first,
                               param.second);
        QCHECK_EQ(rc, RC_OK, "%d",
            "Failed to set TX %u.%u param %u value %u",
            tx_id, param.first.group, param.first.id, param.second);
      }
    }
    tx_antenna_mask = tx_antenna_mask >> 1;
  }

  // RX params.
  ILOG("Configure RX params at slot %u", slot_id);
  uint32_t rx_antenna_mask = main_params[RADAR_PARAM_RX_ANTENNA_MASK-1].second;
  uint32_t rx_count = rx_params.size();
  for (uint32_t rx_id = 0; rx_id < rx_count; ++rx_id) {
    if (rx_antenna_mask & 1) {
      for (auto& param : rx_params[rx_id]) {
        ILOG("Setting a RX %u.%u param %u value %u", rx_id,
             param.first.group, param.first.id, param.second);
        rc = radar->SetRxParam(slot_id, (1 << rx_id), param.first,
                               param.second);
        QCHECK_EQ(rc, RC_OK, "%d",
            "Failed to set RX %u.%u param %u value %u", rx_id,
            param.first.group, param.first.id, param.second);
      }
    }
    rx_antenna_mask = rx_antenna_mask >> 1;
  }

  ILOG("Radar initialized");

  ILOG("Turning the radar on...");
  rc = radar->TurnOn();
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to turn on the radar");

  ILOG("Activating config slot %u...", slot_id);
  rc = radar->ActivateConfig(slot_id);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to activate the config slot %u", slot_id);

  ILOG("Start data streaming...");
  rc = radar->StartDataStreaming();
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to start data streaming");

  // Main loop to get raw data out.
  RadarBurstFormat format;
  // The buffer for raw data will be allocated from heap when resized.
  std::vector<uint8_t> raw_radar_data;

  int frames_to_read = 250;
  ILOG("Reading %i burst...", frames_to_read);
  for (int i = 0; i < frames_to_read; ++i) {
    rc = radar->ReadBurst(format, raw_radar_data, {1, 0});
    ILOG("Burst %i. raw radar data size: %zu\n", i+1, raw_radar_data.size());
  }
  ILOG("Reading %i bursts completed", frames_to_read);

  ILOG("Stopping data streaming...");
  rc = radar->StopDataStreaming();
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to stop radar data streaming");

  ILOG("Turning the radar off...");
  rc = radar->TurnOff();
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to turn the radar off");

  rc = radar_api::DestroyRadarSensor(radar);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to destroy radar instance");
}
