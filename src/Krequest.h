// Copyright (c) 2026 kwzDev
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
*@file Krequest.h
*@author kwzDev
*@brief ZH-CN > 基于'Boost.Asio'库编写的C++Http客户端请求工具 | EN > Krequest is a lightweight, high-performance,
 and header-only HTTP client library for C++, built on top of the robust Boost.Asio. 
 Designed with simplicity and modern C++ practices in mind, it provides both synchronous 
 and asynchronous APIs to handle HTTP requests effortlessly.
*/

#pragma once

#include <boost/asio.hpp>
#include "method/method_model.h"
#include <memory>
#include <utility>
#include <vector>

namespace Krequest {
    class HttpClient {
        private:
        Krequest::request_model_get model_get;
        Krequest::request_model_post model_post;
        std::string _domain;
        std::string _user_agent;
        std::string _content_type;
        std::string _key;
        std::string _value;
        bool ssl;
        Krequest::RequestMethod::method method;

        public:
            HttpClient& SetClientDomain (const std::string& client_domain){
                _domain = client_domain;
                return *this;
            }

            HttpClient& SetClientContentType (const std::string& content_type){
                _content_type = content_type;
                return *this;
            }

            HttpClient& SetClientMethod (Krequest::RequestMethod::method&& client_method){
                method = std::move(client_method);
                return *this;
            }

            HttpClient& AddHeader(const std::string& key , const std::string& value){
                _key = key;
                _value = value;
                return *this;
            }

            HttpClient& SetClientSSL(bool _ssl){
                ssl = _ssl;
                return *this;
            }

            HttpClient& SetUserAgnet(const std::string& user_agent){
                _user_agent = std::move(user_agent);
                return *this;
            }

            inline std::vector<char> Request () {
                switch (method) {
                    case Krequest::RequestMethod::Get:{
                        model_get.model_url(std::make_shared<std::string>(_domain));
                        model_get.model_content(std::make_shared<std::string>(_content_type));
                        model_get.model_user_agnet(std::make_shared<std::string>(_user_agent));
                        model_get.model_add_header(std::make_shared<std::string>(_key), std::make_shared<std::string>(_value));
                        std::string request_templates_get = model_get.get_model();
                        //reqeuest code
                        std::vector<char> respons = model_get.get_response(_domain, request_templates_get,ssl);
                        return respons;                
                        break;
                    }
                    case Krequest::RequestMethod::method::Post:{
                        model_post.model_url(std::make_shared<std::string>(_domain));
                        model_post.model_content(std::make_shared<std::string>(_user_agent));
                        model_post.model_user_agnet(std::make_shared<std::string>(_user_agent));
                        model_post.model_add_header(std::make_shared<std::string>(_key), std::make_shared<std::string>(_value));
                        std::string request_templates_post = model_post.get_model();
                        //request code
                        std::vector<char> respons = model_post.get_response(_domain, request_templates_post,ssl);
                        return respons;
                    }
                }
            }

            inline std::string GetStatusPostCode(){
                return model_post.get_status_code();
            }

            inline std::string GetStatusGetCode(){
                return model_get.get_status_code();
            }
    };
}
