#ifndef GEOCODINGAPI_H
#define GEOCODINGAPI_H
#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include <iostream>
#include <Wt/Http/Client.h>
#include <Wt/WResource.h>
#include <Wt/Http/Message.h>

class GeocodingAPI
{
public:
    bool sendData();
    static void handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response);
    std::string _text;
    GeocodingAPI();
    ~GeocodingAPI();
    Wt::Http::Client aaa;
};

#endif // GEOCODINGAPI_H


