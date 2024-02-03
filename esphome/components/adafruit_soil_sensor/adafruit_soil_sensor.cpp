#include "esphome/core/log.h"
#include "adafruit_soil_sensor.h"

namespace esphome {
namespace adafruit_soil_sensor {

static const char *const TAG = "adafruit_soil_sensor.sensor";

void SoilSensorComponent::setup() {
  if(!adafruit_seesaw.begin(this->address_))
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
  LOG_SENSOR("  ", "X Axis", this->moisture_sensor_);
}

float SoilSensorComponent::get_setup_priority() const { return setup_priority::DATA; }

void SoilSensorComponent::update() {
  if(this->connected_) {
//    ESP_LOGD(TAG, "update sensor on address: 0x%02X", this->address_);

//    if (float temp = adafruit_seesaw.getTemp())
//    {
//      TemperatureSensor->publish_state(temp);
//      //ESP_LOGD("custom", "The value of temp sensor is: %f", temp);
//    }
    if (uint16_t capread = adafruit_seesaw.touchRead(0))
    {
      float moist = capread;
      moisture_sensor_->publish_state(moist);
      ESP_LOGD(TAG, "The value of the moisture sensor is: %f", moist);
    }
  }
  else
  {
    ESP_LOGE(TAG, "Failed to update, sensor not connected on address: 0x%02X", this->address_);
  }
}
}
}
