#include "GeocodingAPI.h"
#include <functional>
#include <Wt/Http/Response.h>

using namespace std::placeholders;
GeocodingAPI::GeocodingAPI()
{

}

GeocodingAPI::~GeocodingAPI()
{

}
bool GeocodingAPI::sendData()
{
    auto client = std::make_unique<Wt::Http::Client>();
    client->addChild(std::make_unique<Wt::Http::Client>());
    client->setTimeout(std::chrono::seconds{15});
    client->setMaximumResponseSize(10 * 1024);
    client->done().connect(std::bind(&GeocodingAPI::handleHttpResponse, _1, _2));
    //client->get("http://open.mapquestapi.com/geocoding/v1/address?key=QVzy1lJxne6weTYGA3Rg0WkoME3j7Hmn&location=Washington,DC");
    bool bResult = false;
//    if (client->get("http://open.mapquestapi.com/geocoding/v1/address?key=QVzy1lJxne6weTYGA3Rg0WkoME3j7Hmn&location=Washington,DC")) {
//        bResult = true;
//      } else {
//         // in case of an error in the %URL
//       }
    //Wt::Http::Client requete;
    //requete.setTimeout(std::chrono::seconds{15});
    //requete.setMaximumResponseSize(10 * 1024);
    //Wt::Http::Message message;
    //Wt::Signal<Wt::AsioWrapper::error_code, Wt::Http::Message>&  done =  requete.done();
    //GeocodingAPI::handleHttpResponse(done);
    //requete.get("http://open.mapquestapi.com/geocoding/v1/address?key=QVzy1lJxne6weTYGA3Rg0WkoME3j7Hmn&location=Washington,DC");
    //GeocodingAPI::handleHttpResponse(requete.done().);
    /*

*/
//boost::bind(&Communication::handleHTTPResponse,_1,_2))
    return 1;
}

void GeocodingAPI::handleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response)
{
   std::cout<<"DONEEE"<<std::endl;
   if (!err && response.status() == 200) {
       std::cout<<response.body()<<std::endl;
       response.body();
   }
}

