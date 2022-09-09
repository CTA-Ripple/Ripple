#include "IRadarSensor.h"

#include "platform_log.h"
#include "platform_check.h"

#include <stddef.h>
#include <stdlib.h>

// Radar API callbacks.
void OnBurstReadyCb(void* user_data) {
  DLOG("Burst data is ready");
}

void OnLogCb(RadarLogLevel level, const char* file, const char* function,
    int line, void* user_data, const char* message) {

  if (level == RLOG_DBG) {
    DLOG("%s:%s:%i %s", file, function, line, message);
  } else if (level == RLOG_INF) {
    ILOG("%s:%s:%i %s", file, function, line, message);
  } else if (level == RLOG_ERR) {
    ELOG("%s:%s:%i %s", file, function, line, message);
  }
}

void OnRegisterSetCb(uint32_t address, uint32_t value, void* user_data) {
  DLOG("Sensor register is set addr %08X val %08X", address, value);
}

// The value should match the TX and RX antenna mask.
#define NUM_CHANS 3

// Buffer to receive raw data.
#define MAX_BUF_BYTES (32 * 1024)
static uint8_t buffer[MAX_BUF_BYTES];

int main(int argc, char* argv[]) {
  ILOG("Raw data streaming example");

  // A few main parameters
  const uint32_t kSamplesPerChirp = 64;
  const uint32_t kChirpsPerBurst = 32;
  const uint32_t kTxMask = 0x01;
  const uint32_t kRxMask = 0x07;

  // Configure radar.
  uint32_t main_params[][2] =
  {
    { RADAR_PARAM_AFTERBURST_POWER_MODE, 0},
    { RADAR_PARAM_INTERCHIRP_POWER_MODE, 0},
    { RADAR_PARAM_BURST_PERIOD_US,       40000},
    { RADAR_PARAM_CHIRP_PERIOD_US,       500},
    { RADAR_PARAM_CHIRPS_PER_BURST,      kChirpsPerBurst},
    { RADAR_PARAM_SAMPLES_PER_CHIRP,     kSamplesPerChirp},
    { RADAR_PARAM_LOWER_FREQ_MHZ,        58500},
    { RADAR_PARAM_UPPER_FREQ_MHZ,        63000},
    { RADAR_PARAM_TX_ANTENNA_MASK,       kTxMask},
    { RADAR_PARAM_RX_ANTENNA_MASK,       kRxMask},
    { RADAR_PARAM_ADC_SAMPLING_HZ,       2000000}
  };
  int num_main_params = sizeof(main_params)/sizeof(main_params[0]);

  uint32_t rx_params[][2] =
  {
    { RX_PARAM_VGA_DB,            5},
    { RX_PARAM_HP_GAIN_DB,        30},
    { RX_PARAM_HP_CUTOFF_KHZ,     45}
  };
  int num_rx_params = sizeof(rx_params)/sizeof(rx_params[0]);

  ILOG("Initializing radar...");
  RadarReturnCode rc = RC_UNDEFINED;
  rc = radarInit();
  QCHECK_EQ(rc, RC_OK, "%u", "Failed to init radar");

  RadarHandle* radar = radarCreate(0);
  QCHECK_NE(radar, NULL, "%p", "Unable to create radar handler");

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
    ILOG("Setting a main param %u value %u", main_params[i][0], main_params[i][1]);
    rc = radarSetMainParam(radar, slot_id, main_params[i][0], main_params[i][1]);
    QCHECK_EQ(rc, RC_OK, "%u",
        "Failed to set main param %u value %u",
        main_params[i][0], main_params[i][1]);
  }

  ILOG("Configure TX params for slot %u", slot_id);
  {
    // Set the TX params for all the antannas at once.
    uint32_t param_id = TX_PARAM_POWER_DB;
    uint32_t param_val = 35;
    ILOG("Setting TX param %u value %u for TX mask 0x%X",
        param_id, param_val, kTxMask);
    rc = radarSetTxParam(radar, slot_id, kTxMask, param_id, param_val);
    QCHECK_EQ(rc, RC_OK, "%u",
        "Failed to set TX param %u value %u for TX mask 0x%X",
        param_id, param_val, kTxMask);
  }

  ILOG("Configure RX params for slot %u", slot_id);
  for (int i = 0; i < num_rx_params; ++i) {
    // Set the TX params for all the antannas at once.
    ILOG("Setting RX param %u value %u for RX mask 0x%X",
        rx_params[i][0], rx_params[i][1], kRxMask);
    rc = radarSetRxParam(radar, slot_id, kRxMask,
        rx_params[i][0], rx_params[i][1]);
    QCHECK_EQ(rc, RC_OK, "%d",
        "Failed to set RX param %u value %u for RX mask 0x%X",
        rx_params[i][0], rx_params[i][1], kRxMask);
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
