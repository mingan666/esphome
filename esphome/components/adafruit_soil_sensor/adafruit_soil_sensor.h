#ifndef __ADAFRUIT_SOIL_SENSOR_H__
#define __ADAFRUIT_SOIL_SENSOR_H__

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include <Adafruit_seesaw.h>

namespace esphome {
namespace adafruit_soil_sensor {

class SoilSensorComponent : public PollingComponent {
 public:
  void set_moisture_sensor(sensor::Sensor *moisture_sensor) { this->moisture_sensor_ = moisture_sensor; }
  void set_temperature_sensor(sensor::Sensor *temperature_sensor) { this->temperature_sensor_ = temperature_sensor; }
  void set_address(uint8_t address) { this->address_ = address; }

  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  void update() override;

 protected:
  Adafruit_seesaw adafruit_seesaw_;
  sensor::Sensor *moisture_sensor_;
  sensor::Sensor *temperature_sensor_;
  uint8_t address_;
  bool connected_;
};

}
}

#endif
