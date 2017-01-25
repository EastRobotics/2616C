#ifndef PORTS_H_
  #ifdef __cplusplus
  extern "C" {
  #endif
    #define mDriveFR 7
    #define mDriveFL 4
    #define mDriveBR 10
    #define mDriveBL 1

    #define mLiftU_R 8
    #define mLiftU_L 2
    #define mLiftL_R 9
    #define mLiftL_L 3


    #define mClaw_L 5
    #define mClaw_R 6
  // ^ on power expander ^

    #define aLiftPot 1
    #define aClawPot 2
    #define aGyroscope 3
    #define aPwrExpandSignal 4

    #define dOdomEncoder_YT 1
    #define dOdomEncoder_YL 2
    #define dOdomEncoder_XT 4
    #define dOdomEncoder_XL 5
    #define dLiteDiodeLift 9
    #define dLiteDiodeClaw 10




  #ifdef __cplusplus
  }
  #endif

#endif
