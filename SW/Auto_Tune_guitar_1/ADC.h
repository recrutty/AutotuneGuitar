#ifndef ADC_H
#define	ADC_H
    void InitAdc(); 
    void initAdcPiezo();
    void initAdcBattery();
    void _AD1Interrupt();
    void countFrequencyTable(uint16_t ConcertPitchA);
#endif	/* ADC_H */

