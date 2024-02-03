import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_ADDRESS,
    CONF_MOISTURE,
    CONF_TEMPERATURE,
    UNIT_PERCENT,
    UNIT_CELSIUS,
    ICON_WATER_PERCENT,
    ICON_THERMOMETER,
    STATE_CLASS_MEASUREMENT,
)

adafruit_soil_sensor_ns = cg.esphome_ns.namespace("adafruit_soil_sensor")
SoilSensorComponent = adafruit_soil_sensor_ns.class_(
    "SoilSensorComponent", cg.PollingComponent
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SoilSensorComponent),
        cv.Required(CONF_ADDRESS): cv.uint8_t,
        cv.Optional(CONF_MOISTURE): sensor.sensor_schema(
            accuracy_decimals=0,
            unit_of_measurement=UNIT_PERCENT,
            icon=ICON_WATER_PERCENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
            accuracy_decimals=1,
            unit_of_measurement=UNIT_CELSIUS,
            icon=ICON_THERMOMETER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
).extend(cv.polling_component_schema("60s"))


def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)

    cg.add(var.set_address(config[CONF_ADDRESS]))

    if CONF_MOISTURE in config:
        moisture_sensor = yield sensor.new_sensor(config[CONF_MOISTURE])
        cg.add(var.set_moisture_sensor(moisture_sensor))

    if CONF_TEMPERATURE in config:
        temp_sensor = yield sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature_sensor(temp_sensor))
