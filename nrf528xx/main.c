#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

void main() {
  gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

  while (1) {
    gpio_pin_toggle_dt(&led);
    k_msleep(500);
  }
}
