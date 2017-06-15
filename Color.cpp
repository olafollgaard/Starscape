#include <Color.h>

void color_t::SetColor(hbr_t hbr)
{
	if (hbr.bri == 0) {
		value = 0;
	}
	else if (hbr.hue < 0x55) {
		channel[0] = hbr.bri * (0x55 - hbr.hue) * 1.0 / 0x55;
		channel[1] = hbr.bri * (hbr.hue - 0x00) * 1.0 / 0x55;
		channel[2] = 0;
	}
	else if (hbr.hue < 0xAA) {
		channel[1] = hbr.bri * (0xAA - hbr.hue) * 1.0 / 0x55;
		channel[2] = hbr.bri * (hbr.hue - 0x55) * 1.0 / 0x55;
		channel[0] = 0;
	}
	else {
		channel[2] = hbr.bri * (0xFF - hbr.hue) * 1.0 / 0x55;
		channel[0] = hbr.bri * (hbr.hue - 0xAA) * 1.0 / 0x55;
		channel[1] = 0;
	}
}
