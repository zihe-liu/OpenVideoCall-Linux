#pragma once
#include<cstdint>
#include<string>
#include<sstream>

typedef struct AppConfig {
    uint32_t uid;
    uint32_t channelProfile;
    uint32_t videoProfile;
    uint32_t audioProfile;
    uint32_t audioScenario;
    uint32_t enableVideo;
    uint32_t enableAudio;

    std::string appId;
    std::string channelId;
}AppConfig;

#define MSG_OPEN 0x1

#define MSG_CLOSE 0x2

#define MSG_CONFIGURE 0x3

#define MSG_ENABLE_VIDEO 0X4

#define MSG_ENABLE_AUDIO 0X5

#define MSG_PRINT_DEVICE_INFO 0x6

#define MSG_EXIT 0x7
