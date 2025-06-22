#include "hal/clocks/clocks.h"
#include "hal/common/common.h"
#include "hal/io_bank/io_bank.h"
#include "hal/pad_bank/pad_bank.h"
#include "hal/sio/sio.h"

#define LED_PIN 25

int main(void) {
  clocks_init_default();

  // Configurar GPIO del LED
  pad_config_t led_pad_config = {.output_disable = false,
                                 .input_enable = true,
                                 .drive_strength = PAD_DRIVE_8MA,
                                 .pull_up_enable = false,
                                 .pull_down_enable = false,
                                 .schmitt_enable = true,
                                 .slew_fast = false};

  gpio_init_pin(LED_PIN, GPIO_FUNC_SIO, &led_pad_config);
  gpio_set_output_enabled(LED_PIN, true);

  // Configurar UART
  // uart_init();

  while (true) {
    gpio_toggle_output_level(LED_PIN);
    delay_cycles(1800000 * 8);
  }

  return 0;
}
