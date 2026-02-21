#include <iostream>
#include<connettodb.h>
#include<reqgenerator.h>
#include <chrono>
#include <ctime>
#include<environment.h>
std::string currentDate()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tm{};
    localtime_r(&t, &tm);  // thread-safe (Linux)

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);

    return buffer;
}
int main()
{
    //foodmaintanceutilitesemergenu
   std::cout<<"welcome to sealine. Vessel coordinator"<<std::endl;
   environment env;
env.buildadjanceyarray();
   return 0;

}
