#pragma once
#include <cstdint>
#include <string>

namespace agora {
    namespace rtc {
        class IRtcEngineEventHandler;
        class IRtcEngine;
        class RtcEngineParameters;
    }
}

using namespace agora::rtc;
using std::string;

class AGEngine 
{
    public:
        AGEngine(IRtcEngineEventHandler* handler, const char* appId);
        ~AGEngine();

        const char* getSDKVersion();

        bool setLogFilePath(const char* logPath = NULL);

        bool joinChannel(const char* channelId, int uid, int channelProfie);

        bool leaveChannel();

        const char* getChannelName();

        const char* getCallID();

        bool enableVideo(bool enable = true);

        bool isVideoEnabled();

        bool isScreenCaptureEnabled();

        bool muteLocalAudio(bool mute = true);

        bool isLocalAudioMuted();

        bool muteLocalVideo(bool mute = true);

        bool isLocalVideoMuted();

        bool enableAudioRecording(bool enable, const char* filePath);

        bool enableNetworkTest(bool bEnable);

        bool enableEchoTest(bool enable = true);

        bool setLogFilter(int type, const char* logPath);

        bool setEncryptionSecret(const char* key, int encryptType = 0);

        bool enableLocalRender(bool enable);

        int createMessageStream();

        bool sendChatMessage(int streamId, const char* chatMessage);

        bool release();

        IRtcEngine* getRtcEngine() { return m_agoraEngine;} 

    private:
        IRtcEngine*     m_agoraEngine;
        RtcEngineParameters* m_parameters;
};
