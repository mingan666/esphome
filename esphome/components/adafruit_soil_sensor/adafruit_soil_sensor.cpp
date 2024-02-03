#include "esphome/core/log.h"
#include "adafruit_soil_sensor.h"

namespace esphome {
namespace adafruit_soil_sensor {

static const char *const TAG = "adafruit_soil_sensor.sensor";

void SoilSensorComponent::setup() {
  if(!adafruit_seesaw_.begin(this->address_))
  {
    ESP_LOGE(TAG, "Failure to connect to sensor on address: 0x%02X", this->address_);
    this->connected_ = false;
  }
  else
  {
    ESP_LOGD(TAG, "Connected to sensor on address: 0x%02X", this->address_);
    this->connected_ = true;
  }
}

void SoilSensorComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Adafruit Soil Sensor:");
  ESP_LOGCONFIG("  ", "Address: 0x%02X", this->address_);
  LOG_SENSOR("  ", "Moisture sensor:", this->moisture_sensor_);
  LOG_SENSOR("  ", "Temperature sensor", this->temperature_sensor_);
}

float SoilSensorComponent::get_setup_priority() const { return setup_priority::DATA; }

void SoilSensorComponent::update() {
  if(this->connected_) {
    if (float temp = this->adafruit_seesaw_.getTemp())
    {
      this->temperature_sensor_->publish_state(temp);
    }
    if (uint16_t value = this->adafruit_seesaw_.touchRead(0))
    {
      float moist = value;
      this->moisture_sensor_->publish_state(moist);
    }
  }
  else
  {
    ESP_LOGE(TAG, "Failed to update, sensor not connected on address: 0x%02X", this->address_);
  }
}
}
}
