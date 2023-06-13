// Copyright 2022 Google LLC.

#include <IRadarSensor.hpp>
#include <StubRadar.hpp>

namespace radar_api {

IRadarSensor* CreateRadarSensor(int32_t id) {
  return new StubRadar(id);
}

RadarReturnCode DestroyRadarSensor(IRadarSensor* radar) {
  delete radar;
  return RC_OK;
}

}  // namespace radar_api

