#include "../src/Krequest.h"
#include <string>

using namespace std;
using namespace Krequest;
using namespace Krequest::RequestMethod;

int main () {
    Krequest::HttpClient http;
    http.SetClientDomain("www.xxx.cn")
        .SetClientContentType("Contnet-Type : application/json")
        .SetClientMethod(RequestMethod::Get)
        .SetClientSSL(true);
    auto body = http.Request();
    const string status_code = http.GetStatusGetCode();
    //使用 jsono-cpp 或者其他JSON解析 body 获取值
    //Use json-cpp or other JSON parsers to parse the body and extract values
}