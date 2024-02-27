
#if(_A0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE)
0x82,

#else
0x00,

#endif

#if(((_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE) && (_D0_DDC_CHANNEL_SEL == _DDC0)) ||\
    ((_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE) && (_D1_DDC_CHANNEL_SEL == _DDC0)))
0x82,

#else
0x00,

#endif

#if(((_D0_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE) && (_D0_DDC_CHANNEL_SEL == _DDC1)) ||\
    ((_D1_EMBEDDED_DDCRAM_MAX_SIZE == _EDID_SIZE_NONE) && (_D1_DDC_CHANNEL_SEL == _DDC1)))
0x82,

#else
0x00,

#endif

#if((_D0_DDC_CHANNEL_SEL == _DDC0) && (_D1_DDC_CHANNEL_SEL == _DDC1))
0x00, 0xFD, 0x80, 0x00, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x80, 0x00, 0x00, 0x00,

#elif((_D0_DDC_CHANNEL_SEL == _DDC1) && (_D1_DDC_CHANNEL_SEL == _DDC0))
0x00, 0xFD, 0x80, 0x00, 0xFF, 0x00, 0x00, 0xFE, 0x00, 0x80, 0x00, 0x00, 0x00,

#else
0x00, 0xFD, 0x80, 0x00, 0xFE, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,

#endif

