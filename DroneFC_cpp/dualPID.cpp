#include "BluebeeDataType.h"

void dualPID(ControlValue *cv, float *dt) 
   {

    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm;
    float rate_pterm, rate_dterm;
    float prev_rate = 0;

    // 각도 오차
    angle_error = (cv->target) - (cv->angle_in);
    // 각도 P 제어값 생성
    stabilize_pterm = (cv->stabilize_kp) * angle_error;
    // 각도 I 제어값 생성
    (cv->stabilize_iterm) += (cv->stabilize_iterm) * angle_error * (*dt);
    // 각속도 목표값 생성
    desired_rate = stabilize_pterm;
    // 각속도 오차 
    rate_error = desired_rate - (cv->rate_in);
    // 각속도 P 제어값 생성
    rate_pterm = (cv->rate_kp) * rate_error;
    // 각속도 I 제어값 생성
    (cv->rate_iterm) += (cv->rate_ki) * rate_error * (*dt);
    // 각속도 D 제어값 생성
    rate_dterm = (cv->rate_kd) * ((cv->rate_in - prev_rate) * (*dt));

    // 최종 제어값 생성
    cv->output = rate_pterm + rate_dterm + (cv->rate_iterm) + (cv->stabilize_iterm);    
   }