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
*@file method.h
*@author kwzDev
*@brief ZH-CN > 基于'Boost.Asio'库编写的C++Http客户端请求工具 | EN > Krequest is a lightweight, high-performance,
 and header-only HTTP client library for C++, built on top of the robust Boost.Asio. 
 Designed with simplicity and modern C++ practices in mind, it provides both synchronous 
 and asynchronous APIs to handle HTTP requests effortlessly.
*/

#pragma once

#include <map>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <utility>
#include <vector>
#include "../request/Krequest_request.h"

namespace Krequest{
    namespace RequestMethod {
        enum method{
            Get,
            Post,
        };
    }

    class request_model_get {
        private:
        std::shared_ptr<std::string> _url;
        std::shared_ptr<std::string> _content_type; 
        std::shared_ptr<std::string> _user_agent;
        std::map<std::string, std::string> header_;  
        std::shared_ptr<Krequest::request::k_request> kreq;
        public:
            request_model_get():_user_agent(std::make_shared<std::string>
                ("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")),
                 kreq(std::make_shared<Krequest::request::k_request>())
                 {}

            inline void model_url (std::shared_ptr<std::string>&& url){
                _url = std::move(url);
            }
            inline void model_user_agnet (std::shared_ptr<std::string>&& user_agent){
                if (user_agent == nullptr){
                    _user_agent = std::make_shared<std::string>("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0");
                }else {
                    _user_agent = std::move(user_agent);
                }
            }
            inline void model_content (std::shared_ptr<std::string>&& content){
                _content_type = std::move(content);
            }
            inline void model_add_header (const std::shared_ptr<std::string>& k , const std::shared_ptr<std::string>& v) {
                header_[*k] = *v;
            }
            inline std::string get_model (){
                std::string model = 
                "GET " + *_url + " HTTP/1.1 \r\n"
                "Host:" + *_url + "\r\n"
                "User-Agent: " + *_user_agent + "\r\n";
                for (const auto& [k , v] : header_){
                    model += k + ": " + v + "\r\n";
                }
                return model;
            }
            inline std::vector<char> get_response(const std::string& _domain , const std::string& model , bool ssl){
                kreq -> request_model(std::make_shared<std::string>(model));
                kreq -> request(std::make_shared<std::string>(_domain),ssl);
                const std::vector<char> body = kreq -> get_response_body();
                return body;
            }

            inline std::string get_status_code () {
                std::string code = kreq -> get_response_code();
                return code;
            }

            inline std::string get_status_message (){
                std::string status_message = kreq -> get_response_status_message();
                return status_message;
            }

            inline std::string get_http_version (){
                std::string version = kreq -> get_response_version();
                return version;
            }
    };

    class request_model_post {
        private:
        std::shared_ptr<std::string> _url;
        std::shared_ptr<std::string> _body;
        std::shared_ptr<std::string> _user_agent;
        std::shared_ptr<std::string> _content_type;
        std::map<std::string, std::string> header_;
        std::shared_ptr<Krequest::request::k_request> kreq;

        public:
        request_model_post():_user_agent(std::make_shared<std::string>
            ("Mozilla/5.0 (X11; Linux x86_64; rv:146.0) Gecko/20100101 Firefox/146.0")),
            kreq(std::make_shared<Krequest::request::k_request>())
            {}

            inline void model_url (const std::shared_ptr<std::string>&& url){
                _url = std::move(url);
            }

            inline void model_user_agnet(std::shared_ptr<std::string>&& user_agent){
                _user_agent = std::move(user_agent);
            }

            inline void model_content(std::shared_ptr<std::string>&& content){
                _content_type = std::move(content);
            }

            inline void model_body(std::shared_ptr<std::string>&& body){
                _body = std::move(body);
            }

            inline void model_add_header (const std::shared_ptr<std::string>& k , const std::shared_ptr<std::string>& v){
                header_[*k] = *v;
            }

            inline std::string get_model(){
                std::string model = 
                "POST " + *_url + " HTTP/1.1 \r\n"
                "Host:" + *_url + "\r\n"
                "User-Agent: " + *_user_agent + "\r\n";
                for (const auto& [k , v] : header_){
                    model += k + ": " + v + "\r\n";
                }
                model += 
                "Content-Lenght: " + std::to_string((*_body).length()) + "\r\n" 
                + *_body;
                return model;
            }

            inline std::vector<char> get_response(const std::string& _domain ,const std::string& model , bool ssl){
                kreq -> request_model(std::make_shared<std::string>(model));
                kreq -> request(std::make_shared<std::string>(_domain),ssl);
                const std::vector<char> body = kreq -> get_response_body();
                return body;
            }

            inline std::string get_status_code () {
                std::string code = kreq -> get_response_code();
                return code;
            }

            inline std::string get_status_message (){
                std::string status_message = kreq -> get_response_status_message();
                return status_message;
            }

            inline std::string get_http_version (){
                std::string version = kreq -> get_response_version();
                return version;
            }
    };
}