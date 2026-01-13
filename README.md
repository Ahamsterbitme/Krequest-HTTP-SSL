</h1> Beta 0.1 Version</h1>

<div id="language-nav">
    <a href="#en">English</a> | 
    <a href="#zh">中文</a> | 
    <a href="#ru">Русский</a>
</div>

<!-- English Version -->
<div id="en">
    <h2>Version Introduction</h2>
    <ul>
        <li>This is a beta version implementing core functionality with minimal Boost.Asio usage</li>
        <li>Beta API features are limited. VisualUI updates tomorrow, Krequest maintenance every other day</li>
        <li>Please understand the update pace - balancing sleep, psychology, and development 😁</li>
    </ul>

<h2>Framework Introduction</h2>
<img src="github-picture/logo/logo.png" alt="logo">
<h4>Framework Name: Krequest</h4>
<span>Author: KwzDev</span><br>
<span>Version: Beta 0.1</span>
<div>
    This framework will be integrated into Visual Beautiful UI in the future, though you can use it anywhere.
    I chose the Apache License for its flexibility - use it for web scraping, APIs, etc. No built-in JSON
    parser included; use your preferred library like json-cpp (my personal choice). If you'd like specific
    integrations, suggest them in Issues - I'll implement the most requested ones. While I'm not a Java fan,
    OKHttp's clean error handling is worth learning from 🌚 Expected in version 0.3.
</div>

<h2>Beta Quick Start</h2>


```cpp
#include "../src/Krequest.h"
#include <string>
#include <iostream>

using namespace std;
using namespace Krequest;
using namespace Krequest::RequestMethod;

int main() {
    Krequest::HttpClient http;
    http.SetClientDomain("example.com")
        .SetClientContentType("application/json") // Your content type
        .SetClientMethod(RequestMethod::Get) // Currently supports Get, Post
        .SetClientSSL(true); // false = HTTP, true = HTTPS
    
    auto body = http.Request(); // Returns response data
    const string status_code = http.GetStatusGetCode();
    
    // For JSON, use json-cpp or your preferred parser
    // The library returns raw response data
}
```
<h2>My Development Journey 😅</h2>
<p>This experience has been... intense. IDE showed no errors during coding, but compilation unleashed
hundreds of error lines. I initially blamed CMake dependencies, but the real culprit was template
metaprogramming issues with Boost.Asio. After 30+ compilation attempts and debugging parameter mismatches
(seriously, what does this library even want?), I finally got it compiling. Then came segfaults and null
pointer issues. After fixing those, here's this barely functional beta. I need a break now. Please report
any issues directly!</p>

<h2>Proof This Isn't AI-Generated (Error Screenshots)</h2>
<img src="/github-picture/1.png" alt="Compilation Error 1">
<img src="/github-picture/2.png" alt="Compilation Error 2">
<img src="/github-picture/3.png" alt="Compilation Error 3">
<img src="/github-picture/4.png" alt="Compilation Error 4">

<p>Time for a well-deserved rest. Good night, everyone!</p>
</div>

<!-- Russian Version -->
<div id="ru">
    <h2>О версии</h2>
    <ul>
        <li>Бета-версия с базовой функциональностью на минимальном использовании Boost.Asio</li>
        <li>Ограниченный API в бета-версии. Завтра обновление VisualUI, поддержка Krequest через день</li>
        <li>Пожалуйста, поймите темп обновлений - балансирую между сном, психологией и разработкой 😁</li>
    </ul>

<h2>О фреймворке</h2>
    <img src="github-picture/logo/logo.png" alt="логотип">
    <h4>Название: Krequest</h4>
    <span>Автор: KwzDev</span><br>
    <span>Версия: Beta 0.1</span>
    <div>
        Этот фреймворк будет интегрирован в Visual Beautiful UI в будущем, но вы можете использовать его где угодно.
        Я выбрал лицензию Apache для её гибкости - используйте для парсинга, API и т.д. Встроенного JSON-парсера нет;
        используйте свою библиотеку, например json-cpp (мой выбор). Если хотите определённые интеграции, предлагайте
        в Issues - реализую самые популярные. Хотя я не фанат Java, чистая обработка ошибок в OKHttp достойна изучения 🌚
        Ожидается в версии 0.3.
    </div>
<h2>Быстрый старт (Beta)</h2>

```cpp
#include "../src/Krequest.h"
#include <string>
#include <iostream>

using namespace std;
using namespace Krequest;
using namespace Krequest::RequestMethod;

int main() {
    Krequest::HttpClient http;
    http.SetClientDomain("example.com")
        .SetClientContentType("application/json") // Ваш Content-Type
        .SetClientMethod(RequestMethod::Get) // Пока поддерживает Get, Post
        .SetClientSSL(true); // false = HTTP, true = HTTPS
    
    auto body = http.Request(); // Возвращает данные ответа
    const string status_code = http.GetStatusGetCode();
    
    // Для JSON используйте json-cpp или ваш парсер
    // Библиотека возвращает сырые данные ответа
}
```

<h2>Мой путь разработки 😅</h2>
<p>Этот опыт был... интенсивным. IDE не показывала ошибок при написании кода, но компиляция обрушила
сотни строк ошибок. Сначала я винил зависимости CMake, но настоящей проблемой оказалась метапрограммирование
шаблонов в Boost.Asio. После 30+ попыток компиляции и отладки несоответствий параметров (серьёзно, чего эта
библиотека вообще хочет?), я наконец добился компиляции. Затем последовали segmentation fault и проблемы с
нулевыми указателями. После их исправления получилась эта едва функциональная бета. Мне нужен перерыв.
Сообщайте о проблемах напрямую!</p>

<h2>Доказательство, что это не код от ИИ (скриншоты ошибок)</h2>
<img src="/github-picture/1.png" alt="Ошибка компиляции 1">
<img src="/github-picture/2.png" alt="Ошибка компиляции 2">
<img src="/github-picture/3.png" alt="Ошибка компиляции 3">
<img src="/github-picture/4.png" alt="Ошибка компиляции 4">

<p>Время заслуженного отдыха. Спокойной ночи, всем!</p>
</div>

<h1> Krequest Beta 0.1 Version </h1>

<div>
    <h2>版本介绍</h2>
    <ul>
        <li>这是 测试版本 只是通过 少量的 Boost.Asio 实现我的主要功能</li>
        <li>Beta API 功能 十分稀少 我明天要更新 VisualUI 不会更新Krequest 但是我是两天维护不同框架</li>
        <li>希望大家可以原谅我的更新速度 平时我也有点压力 不管是睡眠上或者是 心理上请大家可以谅解下 😁</li>
    </ul>
</div>

<div>
    <h2>框架介绍</h2>
    <img src="github-picture/logo/logo.png" alt="logo">
    <h4>框架名: Krequest</h4>
    <span>作者: KwzDev</span><br>
    <span>版本: Beta 0.1</span>
    <div>
        此框架未来将会用于Visual Beautiful UI当中,额当然你也可以用到其他地方我这次选择的
        Apache 许可证十分宽松 你可以用到任何地方 包括爬虫 我没有写 专门用户 Json 处理的工具
        当然你可以自由选择 Json 处理工具 比如说 json-cpp 这就是我经常 用的如果 大家觉得我可以集成
        可以在提议中告诉我我会挑选最多的工具集成在这个框架中 我虽然不是特别喜欢Java但是他的OKhttp库我感觉可以参考学习下 清晰的 错误回调处理 我感觉可以学习下🌚等待我预计 0.3 会有
    </div>
</div>

<h2>Beat版本快速开始</h2>

```cpp     
#include "../src/Krequest.h"
#include <string>
#include <iostream>

using namespace std;
using namespace Krequest;
using namespace Krequest::RequestMethod;

int main () {
    Krequest::HttpClient http;
    http.SetClientDomain("域名")
        .SetClientContentType("Contnet-Type : application/json") //填写你的请求获取参数类型
        .SetClientMethod(RequestMethod::Get) //暂时支持 Get , Post
        .SetClientSSL(true); //false 关闭 SSL支持 true 开启SSL支持
    auto body = http.Request(); //这里会返回响应数据,需要一个变量接收
    const string status_code = http.GetStatusGetCode(); //这里因为一些设计问题需要指定方法获取 注意 '你需要自己清楚你获取的响应是什么(图片,视频,音频,文件)!对应你自己的工具解析 这里只会完好无损的返回服务器响应数据'

    //如果是Json 推荐 使用 jsono-cpp 或者其他JSON解析库 获取Body值
}

```
<h2>我的绝望心理😅</h2>
<p>这个我真的要说太牛逼了,我写的时候Ide不报错当我开心准备编译时候......<br>
突然几百行报错我靠了我都不知道那错了一直以为是CMake依赖问题但是我不管怎么改变的都没有用
然后我问AI才知道是模板元编程问题然后我再那各种改Boost.Asio的参数我也不知道参数到底是什么他想要什么
我也是懵的然后30次make尝试后我终于可以编译了但是我运行又是段错误,空指针在我改正后勉强做出这个可用版本我现在需要休息了
如果有什么问题直接提议就好啦</p>
<h2>还有我担心你们说我是AI写的代码我的报错图片是最好的证明</h2>
<img src="/github-picture/1.png" alt="github-picture">
<img src="/github-picture/2.png" alt="github-picture">
<img src="/github-picture/3.png" alt="github-picture">
<img src="/github-picture/4.png" alt="github-picture">
<span>我现在需要好好休息了,晚安我的朋友们</span>