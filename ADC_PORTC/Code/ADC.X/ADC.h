/* 
 * File:   ADC.h
 * Author: IBRAHIM NAZIR SANGI
 *
 * Created on July 13, 2013, 3:21 AM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ConfigModuleADC(void);
void ChangeChannelADC(unsigned char CHANNEL);
unsigned int SamplingAndConversionADC(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

