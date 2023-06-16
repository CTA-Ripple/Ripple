#include "IRadarSensor.h"

#include "platform_log.h"
#include "platform_check.h"

#include <stddef.h>
#include <stdlib.h>

// Radar API callbacks.
void OnBurstReadyCb(void* user_data) {
  (void)user_data;
  DLOG("Burst data is ready");
}

void OnLogCb(RadarLogLevel level, const char* file, const char* function,
    int line, void* user_data, const char* message) {
  (void)user_data;

  if (level == RLOG_DBG) {
    DLOG("%s:%s:%i %s", file, function, line, message);
  } else if (level == RLOG_INF) {
    ILOG("%s:%s:%i %s", file, function, line, message);
  } else if (level == RLOG_ERR) {
    ELOG("%s:%s:%i %s", file, function, line, message);
  }
}

void OnRegisterSetCb(uint32_t address, uint32_t value, void* user_data) {
  (void)user_data;
  ILOG("Sensor register is set addr %08X val %08X", address, value);
}

// The value should match the TX and RX antenna mask.
#define NUM_CHANS 3

// Buffer to receive raw data.
#define MAX_BUF_BYTES (32 * 1024)
static uint8_t buffer[MAX_BUF_BYTES];

// Helper struct to hold config params.
typedef struct RadarMainParamVal_s {
  RadarMainParam param;
  uint32_t value;
} RadarMainParamVal;

typedef struct RadarTxParamVal_s {
  RadarTxParam param;
  uint32_t value;
} RadarTxParamVal;

typedef struct RadarRxParamVal_s {
  RadarRxParam param;
  uint32_t value;
} RadarRxParamVal;

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  ILOG("Raw data streaming example");

  // A few main parameters
  const uint32_t kSamplesPerChirp = 64;
  const uint32_t kChirpsPerBurst = 32;
  const uint32_t kTxMask = 0x01;
  const uint32_t kRxMask = 0x07;

  // Configure radar.
  RadarMainParamVal main_params[] =
  {
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_AFTERBURST_POWER_MODE}, 0},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_BURST_PERIOD_US},       40000},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_TX_ANTENNA_MASK},       kTxMask},
    { {RADAR_PARAM_GROUP_COMMON, RADAR_PARAM_RX_ANTENNA_MASK},       kRxMask},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_INTERCHIRP_POWER_MODE},  0},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_CHIRP_PERIOD_US},        500},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_CHIRPS_PER_BURST},       kChirpsPerBurst},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_SAMPLES_PER_CHIRP},      kSamplesPerChirp},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_LOWER_FREQ_MHZ},         58500},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_UPPER_FREQ_MHZ},         63000},
    { {RADAR_PARAM_GROUP_FMCW,   FMCW_PARAM_ADC_SAMPLING_HZ},        2000000}
  };
  int num_main_params = sizeof(main_params)/sizeof(main_params[0]);

  // Same params for all TX antennas.
  RadarTxParamVal tx_params[] =
  {
    { {RADAR_PARAM_GROUP_FMCW, FMCW_TX_PARAM_POWER_IDX},             35}
  };
  int num_tx_params = sizeof(tx_params)/sizeof(tx_params[0]);

  // Same params for all RX antennas.
  RadarRxParamVal rx_params[] =
  {
    { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_VGA_IDX},               5},
    { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_GAIN_IDX},           30},
    { {RADAR_PARAM_GROUP_FMCW, FMCW_RX_PARAM_HP_CUTOFF_KHZ},         45}
  };
  int num_rx_params = sizeof(rx_params)/sizeof(rx_params[0]);

  ILOG("Initializing radar...");
  RadarReturnCode rc = RC_UNDEFINED;
  rc = radarInit();
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to init radar");

  RadarHandle* radar = radarCreate(0);
  QCHECK(radar != NULL, "Unable to create radar handler");

  rc = radarSetLogLevel(radar, RLOG_INF);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to set log level");

  DLOG("Adding the observer callbacks");
  rc = radarSetBurstReadyCb(radar, OnBurstReadyCb, NULL);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to register OnBurstReady callback");
  rc = radarSetLogCb(radar, OnLogCb, NULL);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to register OnLog callback");
  rc = radarSetRegisterSetCb(radar, OnRegisterSetCb, NULL);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to register OnRegisterSet callback");

  uint8_t num_slots = 0;
  DLOG("Getting the number of config slots");
  rc = radarGetNumConfigSlots(radar, &num_slots);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to get number for config slots");
  QCHECK_GE(num_slots, 1, "%u",
      "Need at least 1 config slot but available %u", num_slots);

  uint8_t slot_id = 0;
  ILOG("Configure main params for slot %u", slot_id);
  for (int i = 0; i < num_main_params; ++i) {
    RadarMainParam param = main_params[i].param;
    uint32_t value = main_params[i].value;
    ILOG("Setting a main param %u.%u value %u", param.group, param.id, value);
    rc = radarSetMainParam(radar, slot_id, param, value);
    QCHECK_EQ(rc, RC_OK, "%u", "Failed to set main param %u.%u value %u",
        param.group, param.id, value);
  }

  ILOG("Configure TX params for slot %u", slot_id);
  for (int i = 0; i < num_tx_params; ++i) {
    RadarTxParam param = tx_params[i].param;
    uint32_t value = tx_params[i].value;
    // Set the TX params for all the antannas at once.
    ILOG("Setting TX param %u.%u value %u for TX mask 0x%X",
        param.group, param.id, value, kTxMask);
    rc = radarSetTxParam(radar, slot_id, kTxMask, param, value);
    QCHECK_EQ(rc, RC_OK, "%d",
        "Failed to set TX param %u.%u value %u for TX mask 0x%X",
        param.group, param.id, value, kTxMask);
  }

  ILOG("Configure RX params for slot %u", slot_id);
  for (int i = 0; i < num_rx_params; ++i) {
    RadarRxParam param = rx_params[i].param;
    uint32_t value = rx_params[i].value;
    // Set the RX params for all the antannas at once.
    ILOG("Setting RX param %u.%u value %u for RX mask 0x%X",
        param.group, param.id, value, kRxMask);
    rc = radarSetRxParam(radar, slot_id, kRxMask, param, value);
    QCHECK_EQ(rc, RC_OK, "%d",
        "Failed to set RX param %u.%u value %u for RX mask 0x%X",
        param.group, param.id, value, kRxMask);
  }

  ILOG("Radar initialized");

  ILOG("Turning the radar on...");
  rc = radarTurnOn(radar);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to turn on the radar");

  ILOG("Activating config slot %i...", slot_id);
  rc = radarActivateConfig(radar, slot_id);
  QCHECK_EQ(rc, RC_OK, "%d",
      "Failed to activate the config slot %i", slot_id);

  ILOG("Start data streaming...");
  rc = radarStartDataStreaming(radar);
  QCHECK_EQ(rc, RC_OK, "%d", "Failed to start data streaming");

  // Main loop to get raw data out.
  RadarBurstFormat format;
  uint32_t read_bytes = MAX_BUF_BYTES;

  int frames_to_read = 250;
  ILOG("Reading %i burst...", frames_to_read);
  struct timespec timeout = {1, 0}; // 1 second.
  for (int i = 0; i < frames_to_read; ++i) {
    rc = radarReadBurst(radar, &format, buffer, &read_bytes, timeout);
    ILOG("Burst %i. raw radar data size: %u", i+1, read_bytes);
  }
  ILOG("Reading %i bursts completed", frames_to_read);

  ILOG("Stopping data streaming...");
  rc = radarStopDataStreaming(radar);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to stop radar data streaming");

  ILOG("Turning the radar off...");
  rc = radarTurnOff(radar);
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to turn the radar off");

  ILOG("Destroying radar...");
  radarDestroy(radar);
}
