
###C soruce file on flash

###Public include path for other module
CFLAGS += -Iexamples/demo_main

include examples/adc/adc.mk
include examples/flash/flash.mk
include examples/gpio/gpio.mk
include examples/i2c/i2c.mk
include examples/net/net.mk
include examples/onenet/onenet.mk
include examples/os/os.mk
include examples/ota/ota.mk
include examples/spi/spi.mk
include examples/timer/timer.mk
include examples/uart/uart.mk
#include examples/pwm/pwm.mk
#include examples/coap/coap.mk
include examples/ctwing/ctwing.mk
include examples/demo_main/demo_main.mk
include examples/sys/sys.mk
include examples/modem/modem.mk
include examples/asocket/asocket.mk
include examples/pwm/pwm.mk
include examples/http/http.mk
include examples/mqtt/mqtt.mk
include examples/pm/pm.mk
include examples/unicom/unicom.mk