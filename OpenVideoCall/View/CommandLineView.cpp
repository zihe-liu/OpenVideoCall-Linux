#include <stdio.h>
#include <iostream>
#include <string.h>

#include "AgoraDefs.h"
#include"CommandLineView.h"
#include"Controller/EngineController.h"

#define MAXLINE 1024

using std::cout;
using std::endl;


CommandLineView::CommandLineView(){
}

CommandLineView::~CommandLineView() {
}

void CommandLineView::configure(const AppConfig& config) {
    if(m_controller)
        m_controller->sendMsg(this,MSG_CONFIGURE_MODEL,(void*)&config);
}

void CommandLineView::run() {

    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);

    cout<< "input command:" << endl;
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        buf[strlen(buf)-1] = 0;

        stringstream ss(&buf[0]);
        string cmd;
        ss >> cmd;
        if(cmd == "exit") {
            exit();
            break;
        }
        else {
            if(!onCommand(cmd , ss)) {
                cout<< "failed to call command:" << cmd << endl;
            }
        }
        memset(buf, 0, MAXLINE);
    }

    cout<< "exit command line" << endl;
}

bool CommandLineView::onCommand(const string& cmd, stringstream& params) {

    if(cmd.compare("open") == 0 ) {
        return joinChannel();
    } 
    else if(cmd.compare("close") == 0) {
        return leaveChannel();
    }
    else if(cmd.compare("mute_video") == 0) {
        string mute;
        params >> mute;

        int flag = 0;
        sscanf(mute.c_str(),"%d",&flag);
        return muteVideo(flag);
    }
    else if(cmd.compare("mute_audio") == 0) {
        string mute;
        params >> mute;

        int flag = 0;
        sscanf(mute.c_str(),"%d",&flag);
        return muteAudio(flag);
    }  
    else if(cmd.compare("print_device_info") == 0) {
        return printDeviceInfo();
    }  
    else {
        cout<< "WARNING:invalid command: " << cmd <<endl;
        return false;
    }
}

bool CommandLineView::printDeviceInfo() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_PRINT_DEVICE_INFO,NULL);
}

bool CommandLineView::joinChannel() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_JOIN_CHANNEL,NULL);
}

bool CommandLineView::leaveChannel() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_LEAVE_CHANNEL, NULL);
}

bool CommandLineView::muteVideo(int mute) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_MUTE_VIDEO , (void*)&mute);
}

bool CommandLineView::muteAudio(int mute) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_MUTE_AUDIO , (void*)&mute);
}

bool CommandLineView::exit() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_EXIT , NULL);
}
