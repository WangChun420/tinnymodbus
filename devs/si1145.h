/*********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright (c) 2018
 *
 * Balint Cristian <cristian dot balint at gmail dot com>
 *
 * TinnyModbus
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *   * Neither the name of the copyright holders nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************/

/*

  si1145.h (SI1145 visible, infra, ultraviolet sensor)

*/

#ifndef _SI1145_H
#define _SI1145_H



#include <avr/io.h>
#include <avr/interrupt.h>

/* COMMANDS */
#define SI1145_PARAM_QUERY 0x80
#define SI1145_PARAM_SET   0xA0
#define SI1145_NOP         0x00
#define SI1145_RESET       0x01
#define SI1145_BUSADDR     0x02
#define SI1145_PS_FORCE    0x05
#define SI1145_ALS_FORCE   0x06
#define SI1145_PSALS_FORCE 0x07
#define SI1145_PS_PAUSE    0x09
#define SI1145_ALS_PAUSE   0x0A
#define SI1145_PSALS_PAUSE 0x0B
#define SI1145_PS_AUTO     0x0D
#define SI1145_ALS_AUTO    0x0E
#define SI1145_PSALS_AUTO  0x0F
#define SI1145_GET_CAL     0x12

/* Parameters */
#define SI1145_PARAM_I2CADDR         0x00
#define SI1145_PARAM_CHLIST          0x01
#define SI1145_PARAM_CHLIST_ENUV     0x80
#define SI1145_PARAM_CHLIST_ENAUX    0x40
#define SI1145_PARAM_CHLIST_ENALSIR  0x20
#define SI1145_PARAM_CHLIST_ENALSVIS 0x10
#define SI1145_PARAM_CHLIST_ENPS1    0x01
#define SI1145_PARAM_CHLIST_ENPS2    0x02
#define SI1145_PARAM_CHLIST_ENPS3    0x04

#define SI1145_PARAM_PSLED12SEL         0x02
#define SI1145_PARAM_PSLED12SEL_PS2NONE 0x00
#define SI1145_PARAM_PSLED12SEL_PS2LED1 0x10
#define SI1145_PARAM_PSLED12SEL_PS2LED2 0x20
#define SI1145_PARAM_PSLED12SEL_PS2LED3 0x40
#define SI1145_PARAM_PSLED12SEL_PS1NONE 0x00
#define SI1145_PARAM_PSLED12SEL_PS1LED1 0x01
#define SI1145_PARAM_PSLED12SEL_PS1LED2 0x02
#define SI1145_PARAM_PSLED12SEL_PS1LED3 0x04

#define SI1145_PARAM_PSLED3SEL 0x03
#define SI1145_PARAM_PSENCODE  0x05
#define SI1145_PARAM_ALSENCODE 0x06

#define SI1145_PARAM_PS1ADCMUX        0x07
#define SI1145_PARAM_PS2ADCMUX        0x08
#define SI1145_PARAM_PS3ADCMUX        0x09
#define SI1145_PARAM_PSADCOUNTER      0x0A
#define SI1145_PARAM_PSADCGAIN        0x0B
#define SI1145_PARAM_PSADCMISC        0x0C
#define SI1145_PARAM_PSADCMISC_RANGE  0x20
#define SI1145_PARAM_PSADCMISC_PSMODE 0x04

#define SI1145_PARAM_ALSIRADCMUX 0x0E
#define SI1145_PARAM_AUXADCMUX   0x0F

#define SI1145_PARAM_ALSVISADCOUNTER            0x10
#define SI1145_PARAM_ALSVISADCGAIN              0x11
#define SI1145_PARAM_ALSVISADCMISC              0x12
#define SI1145_PARAM_ALSVISADCMISC_VISRANGE     0x20
#define SI1145_PARAM_ALSVISADCMISC_VISRANGE_LOW 0x00

#define SI1145_PARAM_ALSIRADCOUNTER         0x1D
#define SI1145_PARAM_ALSIRADCGAIN           0x1E
#define SI1145_PARAM_ALSIRADCMISC           0x1F
#define SI1145_PARAM_ALSIRADCMISC_RANGE     0x20
#define SI1145_PARAM_ALSIRADCMISC_RANGE_LOW 0x00

#define SI1145_PARAM_ADCCOUNTER_511CLK 0x70

#define SI1145_PARAM_ADCMUX_SMALLIR  0x00
#define SI1145_PARAM_ADCMUX_LARGEIR  0x03
#define SI1145_PARAM_ADCMUX_VIS      0x02
#define SI1145_PARAM_ADCMUX_NODIODE  0x06
#define SI1145_PARAM_ADCMUX_GND      0x25
#define SI1145_PARAM_ADCMUX_TEMP     0x65

#define SI1145_RESP_ALS_VIS_ADC_OVERFLOW 0x8C
#define SI1145_RESP_ALS_IR_ADC_OVERFLOW  0x8D

/* REGISTERS */
#define SI1145_REG_PARTID  0x00
#define SI1145_REG_REVID  0x01
#define SI1145_REG_SEQID  0x02

#define SI1145_REG_INTCFG  0x03
#define SI1145_REG_INTCFG_INTOE 0x01
#define SI1145_REG_INTCFG_INTMODE 0x02

#define SI1145_REG_IRQEN  0x04
#define SI1145_REG_IRQEN_ALSEVERYSAMPLE 0x01
#define SI1145_REG_IRQEN_PS1EVERYSAMPLE 0x04
#define SI1145_REG_IRQEN_PS2EVERYSAMPLE 0x08
#define SI1145_REG_IRQEN_PS3EVERYSAMPLE 0x10


#define SI1145_REG_IRQMODE1 0x05
#define SI1145_REG_IRQMODE2 0x06

#define SI1145_REG_HWKEY  0x07
#define SI1145_REG_MEASRATE0 0x08
#define SI1145_REG_MEASRATE1  0x09
#define SI1145_REG_PSRATE  0x0A
#define SI1145_REG_PSLED21  0x0F
#define SI1145_REG_PSLED3  0x10
#define SI1145_REG_UCOEFF0  0x13
#define SI1145_REG_UCOEFF1  0x14
#define SI1145_REG_UCOEFF2  0x15
#define SI1145_REG_UCOEFF3  0x16
#define SI1145_REG_PARAMWR  0x17
#define SI1145_REG_COMMAND  0x18
#define SI1145_REG_RESPONSE  0x20
#define SI1145_REG_IRQSTAT  0x21
#define SI1145_REG_IRQSTAT_ALS  0x01

#define SI1145_REG_ALSVISDATA0 0x22
#define SI1145_REG_ALSVISDATA1 0x23
#define SI1145_REG_ALSIRDATA0 0x24
#define SI1145_REG_ALSIRDATA1 0x25
#define SI1145_REG_PS1DATA0 0x26
#define SI1145_REG_PS1DATA1 0x27
#define SI1145_REG_PS2DATA0 0x28
#define SI1145_REG_PS2DATA1 0x29
#define SI1145_REG_PS3DATA0 0x2A
#define SI1145_REG_PS3DATA1 0x2B
#define SI1145_REG_UVINDEX0 0x2C
#define SI1145_REG_UVINDEX1 0x2D
#define SI1145_REG_PARAMRD 0x2E
#define SI1145_REG_CHIPSTAT 0x30

#define SI1145_ADDR 0x60

#define SI1145_READ_UV 0x2C
#define SI1145_READ_VI 0x22
#define SI1145_READ_IR 0x24


void si1145_init(void);
float si1145_read_value(const uint8_t TYPE);


#endif