#include "BluebeeDataType.h"

void dualPID(ControlValue *cv, float *dt) 
   {

    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm, rate_pterm;

    angle_error = (cv->target) - (cv->angle_in);

    stabilize_pterm = (cv->stabilize_kp) * angle_error;
    (cv->stabilize_iterm) += (cv->stabilize_iterm) * angle_error * (*dt);

    desired_rate = stabilize_pterm;

    rate_error = desired_rate - (cv->rate_in);

    rate_pterm = (cv->rate_kp) * rate_error;
    (cv->rate_iterm) += (cv->rate_ki) * rate_error * (*dt);

    cv->output = rate_pterm + (cv->rate_iterm) + (cv->stabilize_iterm);    
   }