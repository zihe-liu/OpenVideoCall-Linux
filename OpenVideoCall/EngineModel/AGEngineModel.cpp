#include"AGEngineModel.h"
#include"AGEngine.h"
#include"AGCameraManager.h"
#include"AGAudInputManager.h"
#include"AGPlayoutManager.h"

#include<iostream>

using std::cout;
using std::endl;
using std::stringstream;

AGEngineModel AGEngineModel::m_model;

AGEngineModel* AGEngineModel::Get() {
    return &m_model;
}

AGEngineModel::AGEngineModel() {

    registerHandler(MSG_JOIN_CHANNEL,(handler_ptr)&AGEngineModel::onJoinChannelMsg);
    registerHandler(MSG_LEAVE_CHANNEL, (handler_ptr)&AGEngineModel::onLeaveChannelMsg);
    registerHandler(MSG_MUTE_VIDEO, (handler_ptr)&AGEngineModel::onMuteVideoMsg);
    registerHandler(MSG_MUTE_AUDIO, (handler_ptr)&AGEngineModel::onMuteAudioMsg);
    registerHandler(MSG_CONFIGURE_MODEL, (handler_ptr)&AGEngineModel::onConfigureMsg);
    registerHandler(MSG_PRINT_DEVICE_INFO, (handler_ptr)&AGEngineModel::onPrintDeviceInfoMsg);
    registerHandler(MSG_EXIT, (handler_ptr)&AGEngineModel::onExitMsg);

    m_engineEventHandler.setEventReceiver(this);
}

AGEngineModel::~AGEngineModel() {
    release();
}

void AGEngineModel::initialize() {
    if(!m_engine){
        m_engine = new AGEngine(&m_engineEventHandler, m_cfg.appId.c_str());
    }

    m_cameraMgr = new AGCameraManager();
    m_cameraMgr->create(m_engine->getRtcEngine());

    m_audInMgr = new AGAudInputManager();
    m_audInMgr->create(m_engine->getRtcEngine());

    m_playoutMgr = new AGPlayoutManager();
    m_playoutMgr->create(m_engine->getRtcEngine());
}

bool AGEngineModel::onJoinChannelMsg(void* msg) {
    cout << "model onJoinChannelMsg" <<endl;

    return m_engine->joinChannel(m_cfg.channelId.c_str(), m_cfg.uid, m_cfg.channelProfile); 
}

bool AGEngineModel::onLeaveChannelMsg(void* msg) {
    cout << "model onLeaveChannelMsg" <<endl;

    return m_engine->leaveChannel(); 
}

bool AGEngineModel::onMuteVideoMsg(void* msg) {
    int* mute = reinterpret_cast<int*>(msg);

    cout << "model onMuteVideoMsg: " << *mute <<endl;
    return true;
}

bool AGEngineModel::onMuteAudioMsg(void* msg) {
    int* mute = reinterpret_cast<int*>(msg);

    cout << "model onMuteAudioMsg: " << *mute <<endl;
    return true;
}

bool AGEngineModel::onConfigureMsg(void* msg) {
    AppConfig* cfg = reinterpret_cast<AppConfig*>(msg);
    m_cfg = *cfg;

    cout << "model onConfigureMsg"<<endl;
    return true;
}

bool AGEngineModel::onPrintDeviceInfoMsg(void* msg) {
    cout << "model onPrintDeviceInfoMsg"<<endl;

    cout <<"camera device number is:" << m_cameraMgr->getDeviceCount() << endl;
    cout <<"current camera device id is:" << m_cameraMgr->getCurDeviceId() << endl;

    cout <<"audio input device number is:" << m_audInMgr->getDeviceCount() << endl;
    cout <<"current audio input device id is:" << m_audInMgr->getCurDeviceId() << endl;

    cout <<"audio playout device number is:" << m_playoutMgr->getDeviceCount() << endl;
    cout <<"current audio playout device id is:" << m_playoutMgr->getCurDeviceId() << endl;

    return true;
}

bool AGEngineModel::onExitMsg(void* msg) {
    m_engine->leaveChannel();
    m_engine->release();

    release();

    return true;
}

void AGEngineModel::release() {
    if(m_cameraMgr) {
        delete m_cameraMgr;
        m_cameraMgr = NULL;
    }

    if(m_audInMgr) {
        delete m_audInMgr;
        m_audInMgr = NULL;
    }

    if(m_playoutMgr) {
        delete m_playoutMgr;
        m_playoutMgr = NULL;
    }

    if(m_engine) {
        delete m_engine;
        m_engine = NULL;
    }
}


void AGEngineModel::onEvent(int id, void* pData) {
    cout << "on event:"<<id<< endl;
}

