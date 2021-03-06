//
//  adc_sensor_component.h
//  esphomelib
//
//  Created by Otto Winter on 24.02.18.
//  Copyright © 2018 Otto Winter. All rights reserved.
//

#ifndef ESPHOMELIB_SENSOR_ADC_SENSOR_COMPONENT_H
#define ESPHOMELIB_SENSOR_ADC_SENSOR_COMPONENT_H

#include "esphomelib/component.h"
#include "esphomelib/sensor/sensor.h"
#include "esphomelib/esphal.h"
#include "esphomelib/defines.h"

#ifdef USE_ADC_SENSOR

namespace esphomelib {

namespace sensor {

/** This class allows using the integrated Analog to Digital converts of the ESP32 and ESP8266.
 *
 * Internally it uses the existing `analogRead` methods for doing this.
 *
 * The ESP8266 only has one pin where this can be used: A0
 *
 * The ESP32 has multiple pins that can be used with this component: GPIO32-GPIO39
 * Note you can't use the ADC2 here on the ESP32 because that's already used by WiFi internally.
 * Additionally on the ESP32 you can set an using `set_attenuation`.
 */
class ADCSensorComponent : public PollingSensorComponent {
 public:
  /// Construct the ADCSensor with the provided pin and update interval in ms.
  explicit ADCSensorComponent(const std::string &name, GPIOInputPin pin, uint32_t update_interval = 15000);

  /// Manually set the pin used for this ADC sensor.
  void set_pin(const GPIOInputPin &pin);

#ifdef ARDUINO_ARCH_ESP32
  /// Set the attenuation for this pin. Only available on the ESP32.
  void set_attenuation(adc_attenuation_t attenuation);
#endif

  // ========== INTERNAL METHODS ==========
  // (In most use cases you won't need these)
  /// Get the pin used for this ADC sensor.
  GPIOInputPin &get_pin();
#ifdef ARDUINO_ARCH_ESP32
  /// Get the attenuation used for this sensor.
  adc_attenuation_t get_attenuation() const;
#endif

  /// Update adc values.
  void update() override;
  /// Setup ADc
  void setup() override;
  /// Unit of measurement: "V".
  std::string unit_of_measurement() override;
  /// Icon: "mdi:flash".
  std::string icon() override;
  /// Accuracy decimals: 2.
  int8_t accuracy_decimals() override;
  /// `HARDWARE_LATE` setup priority.
  float get_setup_priority() const override;

 protected:
  GPIOInputPin pin_;

#ifdef ARDUINO_ARCH_ESP32
  adc_attenuation_t attenuation_{ADC_0db};
#endif
};

} // namespace sensor

} // namespace esphomelib

#endif //USE_ADC_SENSOR

#endif //ESPHOMELIB_SENSOR_ADC_SENSOR_COMPONENT_H
