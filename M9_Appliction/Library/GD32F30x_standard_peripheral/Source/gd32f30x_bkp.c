/*!
    \file  gd32f30x_bkp.c
    \brief BKP driver
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#include "gd32f30x_bkp.h"

/*!
    \brief      reset BKP registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_deinit(void)
{
    /* reset BKP */
    rcu_bkp_reset_enable();
    rcu_bkp_reset_disable();
}

/*!
    \brief      write BKP data register
    \param[in]  register_number: refer to bkp_data_register_enum, only one parameter can be selected
      \arg        BKP_DATA_x(0..41): bkp data register number x
    \param[in]  data: the data to be write in BKP data register
    \param[out] none
    \retval     none
*/
void bkp_write_data(bkp_data_register_enum register_number, uint16_t data)
{
    if((register_number >= BKP_DATA_10) && (register_number <= BKP_DATA_41)){
        BKP_DATA10_41(register_number-1U) = data;
    }else if((register_number >= BKP_DATA_0) && (register_number <= BKP_DATA_9)){
        BKP_DATA0_9(register_number-1U) = data;
    }else{
        /* illegal parameters */
    }
}

/*!
    \brief      read BKP data register
    \param[in]  register_number: refer to bkp_data_register_enum, only one parameter can be selected
      \arg        BKP_DATA_x(0..41): bkp data register number x
    \param[out] none
    \retval     data of BKP data register
*/
uint16_t bkp_read_data(bkp_data_register_enum register_number)
{
    uint16_t data = 0U;
    
    /* get the data from the BKP data register */
    if((register_number >= BKP_DATA_10) && (register_number <= BKP_DATA_41)){
        data = BKP_DATA10_41(register_number-1U);
    }else if((register_number >= BKP_DATA_0) && (register_number <= BKP_DATA_9)){
        data = BKP_DATA0_9(register_number-1U);
    }else{
        /* illegal parameters */
    }
    return data;
}

/*!
    \brief      enable RTC clock calibration output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_output_enable(void)
{
    BKP_OCTL |= (uint16_t)BKP_OCTL_COEN;
}

/*!
    \brief      disable RTC clock calibration output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_output_disable(void)
{
    BKP_OCTL &= (uint16_t)~BKP_OCTL_COEN;
}

/*!
    \brief      enable RTC alarm or second signal output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_signal_output_enable(void)
{
    BKP_OCTL |= (uint16_t)BKP_OCTL_ASOEN;
}

/*!
    \brief      disable RTC alarm or second signal output
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_signal_output_disable(void)
{
    BKP_OCTL &= (uint16_t)~BKP_OCTL_ASOEN;
}

/*!
    \brief      select RTC output
    \param[in]  outputsel: RTC output selection
      \arg        RTC_OUTPUT_ALARM_PULSE: RTC alarm pulse is selected as the RTC output
      \arg        RTC_OUTPUT_SECOND_PULSE: RTC second pulse is selected as the RTC output
    \param[out] none
    \retval     none
*/
void bkp_rtc_output_select(uint16_t outputsel)
{
    uint16_t ctl = 0U;
    
    ctl = BKP_OCTL;
    ctl &= (uint16_t)~BKP_OCTL_ROSEL;
    ctl |= outputsel;
    BKP_OCTL = ctl;
}

/*!
    \brief      select RTC clock output
    \param[in]  clocksel: RTC clock output selection
      \arg        RTC_CLOCK_DIV_64: RTC clock div 64
      \arg        RTC_CLOCK_DIV_1: RTC clock
    \param[out] none
    \retval     none
*/
void bkp_rtc_clock_output_select(uint16_t clocksel)
{
    uint16_t ctl = 0U;
    
    ctl = BKP_OCTL;
    ctl &= (uint16_t)~BKP_OCTL_CCOSEL;
    ctl |= clocksel;
    BKP_OCTL = ctl;
}

/*!
    \brief      RTC clock calibration direction
    \param[in]  direction: RTC clock calibration direction
      \arg        RTC_CLOCK_SLOWED_DOWN: RTC clock slow down
      \arg        RTC_CLOCK_SPEED_UP: RTC clock speed up
    \param[out] none
    \retval     none
*/
void bkp_rtc_clock_calibration_direction(uint16_t direction)
{
    uint16_t ctl = 0U;
    
    ctl = BKP_OCTL;
    ctl &= (uint16_t)~BKP_OCTL_CALDIR;
    ctl |= direction;
    BKP_OCTL = ctl;
}

/*!
    \brief      set RTC clock calibration value 
    \param[in]  value: RTC clock calibration value
      \arg        0x00 - 0x7F
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_value_set(uint8_t value)
{
    BKP_OCTL = (uint16_t)OCTL_RCCV(value);
}

/*!
    \brief      enable tamper detection
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_detection_enable(void)
{
    BKP_TPCTL |= (uint16_t)BKP_TPCTL_TPEN;
}

/*!
    \brief      disable tamper detection
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_detection_disable(void)
{
    BKP_TPCTL &= (uint16_t)~BKP_TPCTL_TPEN;
}

/*!
    \brief      set tamper pin active level
    \param[in]  level: tamper active level
      \arg        TAMPER_PIN_ACTIVE_HIGH: the tamper pin is active high
      \arg        TAMPER_PIN_ACTIVE_LOW: the tamper pin is active low
    \param[out] none
    \retval     none
*/
void bkp_tamper_active_level_set(uint16_t level)
{
    uint16_t ctl = 0U;
    
    ctl = BKP_TPCTL;
    ctl &= (uint16_t)~BKP_TPCTL_TPAL;
    ctl |= level;
    BKP_TPCTL = ctl;
}

/*!
    \brief      enable tamper interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_interrupt_enable(void)
{
    BKP_TPCS |= (uint16_t)BKP_TPCTL_TPIE;
}

/*!
    \brief      disable tamper interrupt
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_interrupt_disable(void)
{
    BKP_TPCS &= (uint16_t)~BKP_TPCTL_TPIE;
}

/*!
    \brief      get bkp flag state
    \param[in]  flag
      \arg        BKP_FLAG_TEF: tamper event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus bkp_flag_get(uint16_t flag)
{
    if(RESET != (BKP_TPCS & BKP_TPCTL_TEF)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear bkp flag state
    \param[in]  flag
      \arg        BKP_FLAG_TEF: tamper event flag
    \param[out] none
    \retval     none
*/
void bkp_flag_clear(uint16_t flag)
{
    BKP_TPCS |= flag;
}

/*!
    \brief      get bkp interrupt flag state
    \param[in]  flag
      \arg        BKP_FLAG_TIF: tamper event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus bkp_interrupt_flag_get(uint16_t flag)
{
    if(RESET != (BKP_TPCS & BKP_TPCTL_TIF)){
        return SET;
    }else{
        return RESET;
    }
}

/*!
    \brief      clear bkp interrupt flag state
    \param[in]  flag
      \arg        BKP_FLAG_TIF: tamper event flag
    \param[out] none
    \retval     none
*/
void bkp_interrupt_flag_clear(uint16_t flag)
{
    BKP_TPCS |= flag;
}
