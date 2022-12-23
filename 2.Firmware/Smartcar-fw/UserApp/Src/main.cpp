#ifdef __cplusplus
extern "C" {
#endif
#include "zf_common_headfile.h"
#ifdef __cplusplus
}
#endif

#define LED1 (H2)
#define LED2 (B13)

int main()
{
    clock_init(SYSTEM_CLOCK_120M);
    gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);
    gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);

    while (1) {
        gpio_set_level(LED1, GPIO_LOW);
        system_delay_ms(1000);
        // gpio_set_level(LED1, GPIO_HIGH);
        gpio_set_level(LED1, GPIO_HIGH);
        system_delay_ms(1000);
        gpio_set_level(LED2, GPIO_LOW);
        system_delay_ms(1000);
        gpio_set_level(LED2, GPIO_HIGH);
        system_delay_ms(1000);
    }
}