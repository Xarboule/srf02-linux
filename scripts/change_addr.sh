#!/bin/bash

I2CBUS = $0
OLDADDR = $1
NEWADDR = $2

i2cset I2CBUS OLDADDR 0xA0
i2cset I2CBUS OLDADDR 0xAA
i2cset I2CBUS OLDADDR 0xA5
i2cset I2CBUS OLDADDR NEWADDR
