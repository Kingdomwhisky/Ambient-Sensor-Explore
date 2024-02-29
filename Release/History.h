Modify Date:2023-12-26
SW Version: V1.00 T03
SW Release Name: FW_Ambsensor_C310S_V1.00T03_20231226

Description:
1.第一版软件上传；


/*----------------------------------------------------------------------------------------------*/
Modify Date:2024-02-27
SW Version: V1.00T03
SW Release Name: FW_Ambsensor_C310S_V1.00T03_20240227

Description:
1.Git本地测试,命令行形式进行代码管理；
2.远程仓库Push测试；
3.文件还原测试；
4.删除Output文件，编译验证上传；


/*----------------------------------------------------------------------------------------------*/
Modify Date:2024-02-29
SW Version: V1.00T03
SW Release Name: FW_Ambsensor_C310S_V1.00T03_20240229

Description:
1. 环境光处理函数修改优化(RTD2014UserAdjust.c)：
    bit ambiLumi_filter(WORD ambiLumi, WORD *pFilteredValue);
    BYTE UserGetDICOMALCAmbiSensor(void);
    
    将以前的各组环境光补偿曲线的判读区间定义参数封装化：
    //Range for curve(Added by KW)
    #define Range_ALC0_L	0
    #define Range_ALC0_H	15

    #define Range_ALC1_L	15
    #define Range_ALC1_H	60
    …………
    目的是为了使函数的可读性更加直观，能够更方便地被应用和修改；

