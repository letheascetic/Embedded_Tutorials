# lpc1768 reg

### 引脚功能相关寄存器

    /**
     * Initialize the system
     *
     * @param  none
     * @return none
     *
     * @brief  Setup the microcontroller system.
     *         Initialize the System and update the SystemFrequency variable.
     */
    void SystemInit (void)
    {
    #if (CLOCK_SETUP)                       /* Clock Setup                        */
      LPC_SC->SCS       = SCS_Val;
      if (SCS_Val & (1 << 5)) {             /* If Main Oscillator is enabled      */
        while ((LPC_SC->SCS & (1<<6)) == 0);/* Wait for Oscillator to be ready    */
      }

      LPC_SC->CCLKCFG   = CCLKCFG_Val;      /* Setup Clock Divider                */

      LPC_SC->PCLKSEL0  = PCLKSEL0_Val;     /* Peripheral Clock Selection         */
      LPC_SC->PCLKSEL1  = PCLKSEL1_Val;

      LPC_SC->CLKSRCSEL = CLKSRCSEL_Val;    /* Select Clock Source for PLL0       */

    #if (PLL0_SETUP)
      LPC_SC->PLL0CFG   = PLL0CFG_Val;
      LPC_SC->PLL0CON   = 0x01;             /* PLL0 Enable                        */
      LPC_SC->PLL0FEED  = 0xAA;
      LPC_SC->PLL0FEED  = 0x55;
      while (!(LPC_SC->PLL0STAT & (1<<26)));/* Wait for PLOCK0                    */

      LPC_SC->PLL0CON   = 0x03;             /* PLL0 Enable & Connect              */
      LPC_SC->PLL0FEED  = 0xAA;
      LPC_SC->PLL0FEED  = 0x55;
    #endif

    #if (PLL1_SETUP)
      LPC_SC->PLL1CFG   = PLL1CFG_Val;
      LPC_SC->PLL1CON   = 0x01;             /* PLL1 Enable                        */
      LPC_SC->PLL1FEED  = 0xAA;
      LPC_SC->PLL1FEED  = 0x55;
      while (!(LPC_SC->PLL1STAT & (1<<10)));/* Wait for PLOCK1                    */

      LPC_SC->PLL1CON   = 0x03;             /* PLL1 Enable & Connect              */
      LPC_SC->PLL1FEED  = 0xAA;
      LPC_SC->PLL1FEED  = 0x55;
    #else
      LPC_SC->USBCLKCFG = USBCLKCFG_Val;    /* Setup USB Clock Divider            */
    #endif

      LPC_SC->PCONP     = PCONP_Val;        /* Power Control for Peripherals      */

      LPC_SC->CLKOUTCFG = CLKOUTCFG_Val;    /* Clock Output Configuration         */
    #endif

      /* Determine clock frequency according to clock register values             */
      if (((LPC_SC->PLL0STAT >> 24)&3)==3) {/* If PLL0 enabled and connected      */
        switch (LPC_SC->CLKSRCSEL & 0x03) {
          case 0:                           /* Internal RC oscillator => PLL0     */
          case 3:                           /* Reserved, default to Internal RC   */
            SystemFrequency = (IRC_OSC *
                              ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                              (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                              ((LPC_SC->CCLKCFG & 0xFF)+ 1));
            break;
          case 1:                           /* Main oscillator => PLL0            */
            SystemFrequency = (OSC_CLK *
                              ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                              (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                              ((LPC_SC->CCLKCFG & 0xFF)+ 1));
            break;
          case 2:                           /* RTC oscillator => PLL0             */
            SystemFrequency = (RTC_CLK *
                              ((2 * ((LPC_SC->PLL0STAT & 0x7FFF) + 1)))  /
                              (((LPC_SC->PLL0STAT >> 16) & 0xFF) + 1)    /
                              ((LPC_SC->CCLKCFG & 0xFF)+ 1));
            break;
        }
      } else {
        switch (LPC_SC->CLKSRCSEL & 0x03) {
          case 0:                           /* Internal RC oscillator => PLL0     */
          case 3:                           /* Reserved, default to Internal RC   */
            SystemFrequency = IRC_OSC / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
            break;
          case 1:                           /* Main oscillator => PLL0            */
            SystemFrequency = OSC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
            break;
          case 2:                           /* RTC oscillator => PLL0             */
            SystemFrequency = RTC_CLK / ((LPC_SC->CCLKCFG & 0xFF)+ 1);
            break;
        }
      }

    #if (FLASH_SETUP == 1)                  /* Flash Accelerator Setup            */
      LPC_SC->FLASHCFG  = (LPC_SC->FLASHCFG & ~0x0000F000) | FLASHCFG_Val;
    #endif
    }
