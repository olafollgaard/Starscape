PROJECT_NAME = Starscape
TARGET_SYSTEM = pro_trinket_5v
INCLUDE_LIBS = Adafruit_NeoPixel DS3232RTC Wire Time LiquidCrystal
LIBRARY_OBJS_LiquidCrystal = I2CIO LCD LiquidCrystal_I2C

include ../makeArduino/makeArduino.mk
