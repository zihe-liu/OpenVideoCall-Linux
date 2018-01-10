#pragma once
#include"Controller/MsgHandler.h"

using std::string;
using std::stringstream;

struct AppConfig;

class CommandLineView : public MsgHandler{
    public:
        CommandLineView();
        ~CommandLineView();

        void run();
        void configure(const AppConfig& config);

    private:
        bool onCommand(const string& cmd, stringstream& params);

        bool joinChannel(); 
        bool leaveChannel(); 
        bool muteAudio(int mute); 
        bool muteVideo(int mute);
        bool printDeviceInfo(); 
        bool exit(); 
};
