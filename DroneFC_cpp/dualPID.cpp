void dualPID(
   float *target_angle,
   float *angle_in,
   float *rate_in, 
   float *stabilize_kp, 
   float *stabilize_ki, 
   float *rate_kp, 
   float *rate_ki, 
   float *stabilize_iterm, 
   float *rate_iterm, 
   float *output,
   float *dt
   ) 
   {

    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm, rate_pterm;

    angle_error = *(target_angle) - *(angle_in);

    stabilize_pterm = *(stabilize_kp) * angle_error;
    *(stabilize_iterm) += *(stabilize_ki) * angle_error * *(dt);

    desired_rate = stabilize_pterm;

    rate_error = desired_rate - *(rate_in);

    rate_pterm = *(rate_kp) * rate_error;
    *(rate_iterm) += *(rate_ki) * rate_error * *(dt);

    *output = rate_pterm + *(rate_iterm) + *(stabilize_iterm);    
   }