#pragma once

#include"Controller/MsgHandler.h"
#include"IAGEventReceiver.h"
#include"AGEngineEventHandler.h"
#include"AgoraDefs.h"

class EngineController;
class AGEngine;
class AGCameraManager;
class AGAudInputManager;
class AGPlayoutManager;

class AGEngineModel : public MsgHandler
                      ,public IAGEventReceiver
{
    public:
        static AGEngineModel* Get();

        //event callback handler
        void onEvent(int id, void* pData);

        void initialize();

    private:
        AGEngineModel();
        ~AGEngineModel();

        //message handler
        bool onJoinChannelMsg(void* msg);
        bool onLeaveChannelMsg(void* msg);
        bool onMuteVideoMsg(void* msg);
        bool onMuteAudioMsg(void* msg);
        bool onConfigureMsg(void* msg);
        bool onPrintDeviceInfoMsg(void* msg);
        bool onExitMsg(void* msg); 

        void release(); 
    private:
        AGEngineEventHandler m_engineEventHandler;
        AGEngine*   m_engine;
        AGCameraManager*  m_cameraMgr;
        AGAudInputManager* m_audInMgr;
        AGPlayoutManager* m_playoutMgr;

        AppConfig m_cfg;

    private:
        static AGEngineModel m_model; 
};

