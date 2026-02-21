#ifndef CONNETTODB_H
#define CONNETTODB_H
#include<string>
#include<vector>
#include<postgresql/libpq-fe.h>
#include<iostream>
#include<cstdlib>

class connettodb
{
    public:
        connettodb();
        void insertDemandClient(const std::string& ,const std::string& ,const std::string &, const std::string& ,const std::string&,const std::string &);
        void insertSupplyClient(const std::string&  ,const std::string&  ,const std::string&  ,const std::string&  ,const std::string&  ,const std::string &  ,const std::string&  );
        std::string searchDemandClient(const std::string& vesselid);
        std::string searchSupplyClient(const std::string& vesselid);
        std::vector<std::string> getalllistofall();
        std::vector<std::string> getalldemand();
        std::vector<std::string> getallsupply();
        void cleardatabase(int);
        virtual ~connettodb();

    protected:

    private:
        PGconn* sldbConn = nullptr;


};

#endif // CONNETTODB_H
