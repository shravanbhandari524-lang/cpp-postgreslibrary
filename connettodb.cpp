#include "connettodb.h"

// connecting to database
connettodb::connettodb()
{
    std::cout<<std::endl<<"connectin to sealinedatabase db."<<std::endl;
    sldbConn = PQconnectdb("host=localhost dbname=sealinedatabase user=cppprogram password=azsxdewq123mk>><");
    if(PQstatus(sldbConn)!=CONNECTION_OK)
    {
        std::cout<<"Error : "<<PQerrorMessage(sldbConn)<<std::endl;
        exit(0);
    }
    else
    {
        std::cout<<"connected to sldbConn."<<std::endl;
    }

    std::cout<<std::endl;
    //ctor
}
//inserting new demand client into sldbConn db
void connettodb::insertDemandClient(const std::string& vesselid,const std::string& imo,const std::string & vesselname,const std::string& owner,const std::string& date,const std::string& workforcesize)
{
    std::cout<<"inserting new row to sldbConn -> demandlist."<<std::endl;
    const char* paramVal[5]= {vesselid.c_str(),imo.c_str(),vesselname.c_str(),owner.c_str(),date.c_str()};
    const char* paramVal1[2]= {vesselid.c_str(),workforcesize.c_str()};
    PGresult* res1 = PQexecParams(sldbConn,"insert into listofall (vesselid,imo,vesselname,owner,date) values ($1,$2,$3,$4,$5)",5,nullptr,paramVal,nullptr,nullptr,0);

    if(PQresultStatus(res1)!=PGRES_COMMAND_OK)
    {
        std::cout<<"Error "<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res1);
PQfinish(sldbConn);
        exit(0);

    }
    PGresult* res=PQexecParams(sldbConn,"insert into demandlist (vesselid,workforcesize) values($1,$2)",2,nullptr,paramVal1,nullptr,nullptr,0);
    if((PQresultStatus(res)==PGRES_COMMAND_OK)&&PQresultStatus(res1)==PGRES_COMMAND_OK)
    {
        std::cout<<"row inserted."<<std::endl;
    }
    else
    {
        std::cout<<"Error "<<PQerrorMessage(sldbConn)<<std::endl;

        PQclear(res1);
        PQfinish(sldbConn);
      exit(0);
    }
    PQclear(res);
    PQclear(res1);
}
//inseting new supply client into sldbConn db
void connettodb::insertSupplyClient(const std::string& vesselid,const std::string& imo,const std::string& vesselname,const std::string& owner,const std::string& date,const std::string & services,const std::string& workforcesize)
{
    std::cout<<"inserting new row to sldbConn -> supplylist."<<std::endl;
    const char* paramVal[5]= {vesselid.c_str(),imo.c_str(),vesselname.c_str(),owner.c_str(),date.c_str()};
    const char* paramVal1[3]= {vesselid.c_str(),services.c_str(),workforcesize.c_str()};
    PGresult* res1 = PQexecParams(sldbConn,"insert into listofall (vesselid,imo,vesselname,owner,date) values ($1,$2,$3,$4,$5)",5,nullptr,paramVal,nullptr,nullptr,0);

    if(PQresultStatus(res1)!=PGRES_COMMAND_OK)
    {
        std::cout<<"Error "<<PQerrorMessage(sldbConn)<<std::endl;

        PQclear(res1);
        PQfinish(sldbConn);
        exit(0);


    }
    PGresult* res=PQexecParams(sldbConn,"insert into supplylist (vesselid,services,workforcesize) values($1,$2,$3)",3,nullptr,paramVal1,nullptr,nullptr,0);

    if(PQresultStatus(res)==PGRES_COMMAND_OK)
    {
        std::cout<<"row inserted."<<std::endl;
    }
    else
    {
        std::cout<<"Error "<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res);
        PQclear(res1);
        PQfinish(sldbConn);
        exit(0);


    }
    PQclear(res);
    PQclear(res1);
}
//clear all the databses table of rows
void connettodb::cleardatabase(int choice)
{
    PGresult* res;
    switch(choice)
    {
    case 1 :
        std::cout<<"deleting from sldbConn -> demandlist."<<std::endl;
        res = PQexec(sldbConn,"delete from demandlist;");
        break;
    case 2 :
        std::cout<<"deleting from sldbConn -> supplylist."<<std::endl;
        res = PQexec(sldbConn,"delete from supplylist;");
        break;
    case 3 :
        std::cout<<"deleting from sldbConn -> listofall"<<std::endl;
        res=PQexec(sldbConn,"delete from listofall;");
        break;

    }
    PQclear(res);
}
//search for single demand ship
std::string connettodb::searchSupplyClient(const std::string& vesselid)
{
    std::cout<<"searching vessel id : "<<vesselid<<std::endl;
    std::string query = "select * from listofall l join supplylist s on l.vesselid = s.vesselid  where l.vesselid = $1 and s.vesselid = $1 ";
    const char* paramval[1]= {vesselid.c_str()};
    std::string result;
    PGresult* res = PQexecParams(sldbConn,query.c_str(),1,nullptr,paramval,nullptr,nullptr,0);
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {
        int n = PQnfields(res);
        int rows=PQntuples(res);
        if(rows>0)
        {
            std::cout<<"foudn vessel id"<<vesselid<<std::endl;
            for(int i=0; i<n; i++)
            {
                result += " ";
                result += (PQgetisnull(res,0,i)? " null ":PQgetvalue(res,0,i));
            }
        }
        else
        {
            std::cout<<"vessel id : "<<vesselid<<" is not found."<<std::endl;
            result="0";
        }

    }
    else
    {
        std::cout<<"Error : "<<PQerrorMessage(sldbConn)<<std::endl<<std::endl;
        PQclear(res);
        PQfinish(sldbConn);

        exit(0);
    }
    PQclear(res);

    return result;
}
//search for single supply ship
std::string connettodb::searchDemandClient(const std::string& vesselid)
{
    std::cout<<"searching vesselid : "<<vesselid<<std::endl;
    std::string result;
    std::string query = "select * from listofall l join demandlist d on l.vesselid = d.vesselid  where l.vesselid = $1 and d.vesselid=$1";
    const char* paramval[1]= {vesselid.c_str()};
    PGresult* res=PQexecParams(sldbConn,query.c_str(),1,nullptr,paramval,nullptr,nullptr,0);
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {

        int n = PQnfields(res);
        int rows =PQntuples(res);
        if(rows>0)
        {
            std::cout<<"found vessel id : "<<vesselid<<std::endl;
            for(int i =0; i<n; i++)
            {

                result += " ";
                result +=(PQgetisnull(res,0,i) ?  " null " : PQgetvalue(res,0,i) );
            }

        }
        else
        {
            std::cout<<"vessel id : "<<vesselid<<" is not found in sldbConn -> demandlist"<<std::endl<<std::endl;
            result = "0";
        }

    }
    else
    {
        std::cout<<"Error"<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res);
        PQfinish(sldbConn);
        exit(0);
    }
    PQclear(res);

    return result;
}

std::vector<std::string> connettodb::getalllistofall()
{
    std::cout<<"collecting all rows from listofall."<<std::endl;
    std::vector<std::string> result;
    std::string ress;
    PGresult* res = PQexec(sldbConn,"select * from listofall;");
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {

        int n = PQnfields(res);
        int rows = PQntuples(res);
        if(rows>0)
        {
            std::cout<<"got all rows."<<std::endl;
            for(int i =0; i<rows; i++)
            {
                for(int j=0; j<n; j++)
                {

                    ress += " ";
                    ress +=(PQgetisnull(res,i,j) ?  " null " : PQgetvalue(res,i,j) );
                }
                result.emplace_back(ress);
                ress.clear();

            }
        }
    }
    else
    {
        std::cout<<"Error"<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res);
        PQfinish(sldbConn);
    }
    return result;
}
std::vector<std::string> connettodb::getalldemand()
{
    std::cout<<"collecting all rows from demandlist."<<std::endl;
    std::vector<std::string> result;
    std::string ress;
    PGresult* res = PQexec(sldbConn,"select * from listofall l join demandlist d on l.vesselid = d.vesselid;");
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {

        int n = PQnfields(res);
        int rows = PQntuples(res);
        if(rows>0)
        {
            std::cout<<"got all rows."<<std::endl;
            for(int i =0; i<rows; i++)
            {
                for(int j=0; j<n; j++)
                {

                    ress += " ";
                    ress +=(PQgetisnull(res,i,j) ?  " null " : PQgetvalue(res,i,j) );
                }
                result.emplace_back(ress);
                ress.clear();

            }
        }
    }
    else
    {
        std::cout<<"Error"<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res);
        PQfinish(sldbConn);
    }
    return result;
}
std::vector<std::string> connettodb::getallsupply()
{
    std::cout<<"collecting all rows from supplylist."<<std::endl;
    std::vector<std::string> result;
    std::string ress;
    PGresult* res = PQexec(sldbConn,"select * from listofall l join supplylist s on l.vesselid = s.vesselid;");
    if(PQresultStatus(res)==PGRES_TUPLES_OK)
    {

        int n = PQnfields(res);
        int rows = PQntuples(res);
        if(rows>0)
        {
            std::cout<<"got all rows."<<std::endl;
            for(int i =0; i<rows; i++)
            {
                for(int j=0; j<n; j++)
                {

                    ress += " ";
                    ress +=(PQgetisnull(res,i,j) ?  " null " : PQgetvalue(res,i,j) );
                }
                result.emplace_back(ress);
                ress.clear();

            }
        }
    }
    else
    {
        std::cout<<"Error"<<PQerrorMessage(sldbConn)<<std::endl;
        PQclear(res);
        PQfinish(sldbConn);
    }
    return result;
}
//destructor
connettodb::~connettodb()
{
    //dtor
    PQfinish(sldbConn);
}
