#ifndef BMI_HEAT_H_INCLUDED
#define BMI_HEAT_H_INCLUDED

#if defined(__cplusplus)
extern "C" {
#endif

#include <bmi.h>
#include "heat.h"

Bmi* register_bmi_heat(Bmi *model);
HeatModel* new_bmi_heat(void);

#if defined(__cplusplus)
}
#endif

#endif
