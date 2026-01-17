#include "../src/Krequest.h"
#include <memory>

using namespace std;
using namespace KING::Krequest::RequestMethod;
using namespace KING::Krequest;

int main () {

    string makejson = "{\"name\" : \"jack\"}"; //test json

    //SSL request Get
    auto SSLGET = make_shared<Krequest::SSLClientGet>(); //make method object
    SSLGET->SetClientDomain("xxx.com") //settings domain
        .SetClientPath("/") //settings request api path 
        .SetUserAgent("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")
        .StartRequest();
        const string status_code = SSLGET -> GetStatusCode();
        const string http_version = SSLGET -> GetHttpVersion();
        const string status_message = SSLGET -> GetStatusMessage();
        cout << "STATUS CODE : " << status_code << "\n"
             << "HTTP VERSION : " << http_version << "\n"
             << "STATUS MESSAGE : " << status_message 
             << std::endl;
    
    //SSL request Post
    auto SSLPOST = make_shared<Krequest::SSLClientPost>(); //make method object
    SSLGET->SetClientDomain("xxx.com") //settings domain
        .SetClientPath("/api/v1/xxx") //settings request api path 
        .SetClientContentType("application/json") //setting fetch type
        .AddClientHeader("author", "kezDev") //add request headers
        .SetUserAgent("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")
        .SetRequestBody(makejson)
        .StartRequest();
        const string status_code_post = SSLGET -> GetStatusCode();
        const string http_version_post = SSLGET -> GetHttpVersion();
        const string status_message_post = SSLGET -> GetStatusMessage();
        cout << "STATUS CODE : " << status_code_post << "\n"
             << "HTTP VERSION : " << http_version_post << "\n"
             << "STATUS MESSAGE : " << status_message_post 
             << std::endl;
    
    //Base http Get
    auto HTTPGET = make_shared<Krequest::HttpClientGet>();
    HTTPGET->SetClientDomain("xxx.com")
        .SetClientPath("/")
        .SetUserAgent("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")
        .StartRequest();
        const string status_code_http_get = HTTPGET -> GetStatusCode();
        const string http_version_http_get = HTTPGET -> GetHttpVersion();
        const string status_message_http_get = HTTPGET -> GetStatusMessage();
        cout << "STATUS CODE : " << status_code_http_get << "\n"
             << "HTTP VERSION : " << http_version_http_get << "\n"
             << "STATUS MESSAGE : " << status_message_http_get 
             << std::endl;

    //Base http Get 
    auto HTTPPOST = make_shared<Krequest::HttpClientPost>();
    HTTPPOST->SetClientDomain("xxx.com")
        .SetClientPath("/api/xxx")
        .SetUserAgent("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")
        .AddClientHeader("author", "kwzDev")
        .SetClientContentType("application/json")
        .SetRequestBody(makejson)
        .StartRequest();
        const string status_code_http_post = HTTPPOST -> GetStatusCode();
        const string http_version_http_post = HTTPPOST -> GetHttpVersion();
        const string status_message_http_post = HTTPPOST -> GetStatusMessage();
        cout << "STATUS CODE : " << status_code_http_post << "\n"
             << "HTTP VERSION : " << http_version_http_post << "\n"
             << "STATUS MESSAGE : " << status_message_http_post 
             << std::endl;
}