#include"AgoraDefs.h"
#include"opt_parser.h"
#include"OpenVideoCallApp.h"

#include <iostream>
#include <sstream> 

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;

int main(int argc, char * const argv[]) {

    opt_parser parser;

    uint32_t uid = 0;
    parser.add_long_opt("uid", &uid, "User Id default is 0/required", opt_parser::require_argu);

    string appId;
    parser.add_long_opt("appId", &appId, "App Id/required", opt_parser::require_argu);

    string channelId;
    parser.add_long_opt("channel", &channelId, "Channel Id/required", opt_parser::require_argu);

    uint32_t channelProfile = 0;
    parser.add_long_opt("channelProfile", &channelProfile, "channel_profile:(0:COMMUNICATION),(1:broadcast) default is 0/option");

    if (!parser.parse_opts(argc, argv) || appId.empty() || channelId.empty()) {
        ostringstream sout;
        parser.print_usage(argv[0], sout);
        cout<<sout.str()<<endl;
        return -1;
    }

    AppConfig cfg;
    cfg.uid = uid;
    cfg.appId = appId;
    cfg.channelId = channelId;
    cfg.channelProfile = channelProfile; 

    OpenVideoCallApp app;
    app.loadConfig(cfg);
    app.run();

    return 0;
}
