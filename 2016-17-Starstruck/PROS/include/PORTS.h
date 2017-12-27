#ifndef PORTS_H_
  #ifdef __cplusplus
  extern "C" {
  #endif
    #define mDriveFR 9
    #define mDriveFL 2
    #define mDriveBR 8
    #define mDriveBL 3

    #define mLiftU_R 6
    #define mLiftU_L 4
    #define mLiftL_R 7
    #define mLiftL_L 5
      // ^ on power expander ^
    #define mClaw_L 1
    #define mClaw_R 10


    #define aLiftPot 1
    #define aClawPot 2
    #define aGyroscope 3
    #define aPwrExpandSignal 4

    #define dOdomEncoder_YT 1
    #define dOdomEncoder_YL 2

    #define dClawEncoder_TOP 11
    #define dClawEncoder_BOT 12
//    #define dOdomEncoder_XT 4
//    #define dOdomEncoder_XL 5
//    ^unused




  #ifdef __cplusplus
  }
  #endif

#endif
