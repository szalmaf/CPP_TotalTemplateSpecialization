//
//  main.cpp
//  C++_TotalTemplateSpecialization
//
//  Created by Ferenc Szalma on 9/9/16.
//  Copyright © 2016 Ferenc Szalma. All rights reserved.
//

#include <iostream>
#include <string>

class CompanyA {
public:
    void sendClearText(const std::string & msg) {};
    void sendEncrypted(const std::string & msg) {};
};

class CompanyB {
public:
    void sendClearText(const std::string & msg) {};
    void sendEncrypted(const std::string & msg) {};
};

class CompanyZ {
public:
    void sendEncrypted(const std::string & msg) {};
};

class MsgInfo {

};

template<typename Company>
class MsgSender { // Base class
public:
    void sendClear(const MsgInfo & info) {
        std::string msg;
        Company c;
        c.sendClearText(msg);
    }
    void sendSecret(const MsgInfo & info) {
        std::string msg;
        Company c;
        c.sendEncrypted(msg);
    }
};

template<>
class MsgSender<CompanyZ> { // total template specialization of MsgSender to CompanyZ
public:
    void sendSecret(const MsgInfo & info) {
        std::string msg;
        CompanyZ c;
        c.sendEncrypted(msg);
    }
};

template<typename Company>
class LoggingMsgSender : public MsgSender<Company> {
public:
//    using MsgSender<Company>::sendClear; // brings sendClear into scope for sendClear(info)
    void sendClearMsg(const MsgInfo & info) {
//        sendClear(info); // won't compile w/o using above
        this->sendClear(info); // will compile even w/o using
        MsgSender<Company>::sendClear(info); // will also compile
    }
};



int main(int argc, const char * argv[]) {
    
    // MsgSender usage example
    MsgInfo mi;
    MsgSender<CompanyB> mscb;
    mscb.sendClear(mi);
    
    // LoggingMsgSender usage example
    LoggingMsgSender<CompanyA> lms;
    lms.sendClearMsg(MsgInfo());
    
    // Total specialized usage example
    LoggingMsgSender<CompanyZ> lmZ;
//    lmZ.sendClearMsg(mi); // won't compile as specialized
    lmZ.sendSecret(mi);
    
}
