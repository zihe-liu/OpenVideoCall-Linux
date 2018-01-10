#pragma once
#include<cstdint>
#include<string>
#include<sstream>

typedef struct AppConfig {
    uint32_t uid;
    uint32_t channelProfile;
    std::string appId;
    std::string channelId;
}AppConfig;

#define MSG_JOIN_CHANNEL 0x1
#define MSG_LEAVE_CHANNEL 0x2
#define MSG_MUTE_VIDEO 0X3
#define MSG_MUTE_AUDIO 0x4
#define MSG_CONFIGURE_MODEL 0x5
#define MSG_PRINT_DEVICE_INFO 0x6
#define MSG_EXIT 0x7
