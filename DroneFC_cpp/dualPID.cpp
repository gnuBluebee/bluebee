#include "BluebeeDataType.h"

void dualPID(ControlValue *cv, float *dt) 
   {
    // 지역 변수 선언
    float angle_error;
    float desired_rate;
    float rate_error;
    float stabilize_pterm, rate_pterm;

    // 목표각 - 현재각 빼서 현재 에러값 구함
    // cv->target : cv라는 구조체 포인터의 target 멤버에 주소값을 이용해 접근
    // (*cv).target 과 동일
    angle_error = (cv->target) - (cv->angle_in);

    // 각 P 제어값 생성
    // (Kp 게인값) x (현재 각도 오차)
    stabilize_pterm = (cv->stabilize_kp) * angle_error;

    // 각 I 제어값 생성
    // (현재 각도 오차)*(dt) 를 누적해 나감 (적분)
    (cv->stabilize_iterm) += (cv->stabilize_iterm) * angle_error * (*dt);
    // 현재 목표 각속도 = 각 P 제어값 -> 자세한 내용은 프로젝트 클라우드 -> 개발가이드북 -> 제어참조
    desired_rate = stabilize_pterm;

    // 각속동 오차 구하기
    rate_error = desired_rate - (cv->rate_in);
    // 각속도 P 제어값 생성
    rate_pterm = (cv->rate_kp) * rate_error;
    // 각속도 I 제어값 생성
    (cv->rate_iterm) += (cv->rate_ki) * rate_error * (*dt);
    
    // 최종 제어기 출력 생성
    cv->output = rate_pterm + (cv->rate_iterm) + (cv->stabilize_iterm);    
   }