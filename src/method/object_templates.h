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
*@file object_templates.h
*@author kwzDev
*@brief ZH-CN > 基于'Boost.Asio'库编写的C++Http客户端请求工具 | EN > Krequest is a lightweight, high-performance,
 and header-only HTTP client library for C++, built on top of the robust Boost.Asio. 
 Designed with simplicity and modern C++ practices in mind, it provides both synchronous 
 and asynchronous APIs to handle HTTP requests effortlessly.
*/

#ifndef __METHOD_TEMPLATES_H__

#pragma once
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <utility>
#include <vector>
#include "../request/Krequest-request.h"

namespace KING {
    namespace Krequest{
        namespace RequestMethod {
            enum method{
                Get,
                Post,
            };
        }
        namespace KINGResponse {
            class request_base{
                public:
                    virtual ~request_base() = default;
                    //config user request function
                    virtual inline void set_host (const std::shared_ptr<std::string>& host_) = 0; //settings response host / domain
                    virtual inline void set_request_templates (const std::shared_ptr<std::string>& request_templates_) = 0; //settings response template
                    virtual inline void start_request() = 0; //

                    //get response data function 
                    virtual inline std::string get_response_status_code () = 0; //get response status code
                    virtual inline std::string get_response_status_message () = 0; //get response status message
                    virtual inline std::vector<char> get_response_body () = 0; //get response body
                    virtual inline std::string get_http_version_ () = 0; //get http version
                protected:
                    std::string _response_status_code;
                    std::string _response_status_message;
                    std::vector<char> _response_body;
                    std::string _http_version;
            };
        }

        class HttpClientRequest : public KINGResponse::request_base {
            private:
                std::shared_ptr<KING::KRQ::HttpResponse> http__;
                std::shared_ptr<std::string> __host_;
                std::shared_ptr<std::string> __templates_;
            public:
                HttpClientRequest(){http__ = std::make_shared<KING::KRQ::HttpResponse>();}
                /**
                @param host | shared_ptr Type -> < std::string > | This param used be for settings request site
                @note this param is cannot a nullptr !
                @brief settings request site
                */
                    inline void set_host(const std::shared_ptr<std::string> &host_) override {
                        __host_ = host_;
                    }
                /**
                @param request_templates_ | shared_ptr Type -> < std::string > | This param used be for settings request templates
                @note this param is cannot a nullptr !
                @brief settings request templates
                */
                    inline void set_request_templates(const std::shared_ptr<std::string> &request_templates_) override {
                        __templates_ = request_templates_;
                    }
                /**
                @brief start ssl request site
                */
                    inline void start_request() override {
                        http__ -> set_host(__host_);
                        http__ -> set_templates(__templates_);
                        http__ -> resolver_host();
                        _response_body = http__ -> getResponseBody();
                        _response_status_code = http__ -> getStatusCode();
                        _response_status_message = http__ -> getStatusMessage();
                        _http_version = http__ -> getHttpVersion();
                    }
                /**
                @brief this function return http version
                @return string | Http version
                */
                    inline std::string get_http_version_() override {
                        return _http_version;
                    }
                /**
                @brief this function return status code
                @return string | Http status code
                */
                    inline std::string get_response_status_code() override {
                        return _response_status_code;
                    }
                /**
                @brief this function return status message
                @return string | staths message
                */
                    inline std::string get_response_status_message() override {
                        return _response_status_message;
                    }
                /**
                @brief this function return resoponse body
                @return vector Type -> < char > | response body            
                */
                    inline std::vector<char> get_response_body() override {
                        return _response_body;
                    }
        };

        class SSLClientRequest : public KINGResponse::request_base {
            private:
                std::shared_ptr<KING::KRQ::SSLResponse> ssl__;
                std::shared_ptr<std::string> __host_;
                std::shared_ptr<std::string> __templates_;
            public:
                SSLClientRequest(){ssl__ = std::make_shared<KING::KRQ::SSLResponse>();}
                /**
                @param host | shared_ptr Type -> < std::string > | This param used be for settings request site
                @note this param is cannot a nullptr !
                @brief settings request site
                */
                    inline void set_host(const std::shared_ptr<std::string> &host_) override {
                        __host_ = host_;
                    }
                /**
                @param request_templates_ | shared_ptr Type -> < std::string > | This param used be for settings request templates
                @note this param is cannot a nullptr !
                @brief settings request templates
                */
                    inline void set_request_templates(const std::shared_ptr<std::string> &request_templates_) override {
                        __templates_ = request_templates_;
                    }
                /**
                @brief start ssl request site
                */
                    inline void start_request() override {
                        ssl__ -> set_host(__host_);
                        ssl__ -> set_templates(__templates_);
                        ssl__ -> resolver_host();
                        _response_body = ssl__ -> getResponseBody();
                        _response_status_code = ssl__ -> getStatusCode();
                        _response_status_message = ssl__ -> getStatusMessage();
                        _http_version = ssl__ -> getHttpVersion();
                    }
                /**
                @brief this function return http version
                @return string | Http version
                */
                    inline std::string get_http_version_() override {
                        return _http_version;
                    }
                /**
                @brief this function return status code
                @return string | Http status code
                */
                    inline std::string get_response_status_code() override {
                        return _response_status_code;
                    }
                /**
                @brief this function return status message
                @return string | staths message
                */
                    inline std::string get_response_status_message() override {
                        return _response_status_message;
                    }

                /**
                @brief this function return resoponse body
                @return vector Type -> < char > | response body            
                */
                    inline std::vector<char> get_response_body() override {
                        return _response_body;
                    }
        };

        class model_base {
            public:
                virtual ~model_base() = default;
                //http templates get base function
                virtual inline void model_user_agnet (const std::shared_ptr<std::string>&& user_agent) = 0;
                virtual inline void model_host(const std::shared_ptr<std::string>&& domain) = 0;
                virtual inline void model_content(const std::shared_ptr<std::string>&& content_type) = 0;
                virtual inline void model_add_header(const std::string& key , const std::string& value) = 0;
                virtual inline void model_url_path(const std::shared_ptr<std::string>&& path) = 0;
                virtual inline std::string get_model() = 0;

                //http templates post function
                virtual inline void model_body(const std::string& request_body) = 0;
            protected:

                std::map<std::string, std::string> _headers;

                std::shared_ptr<std::string> _content_type;
                std::shared_ptr<std::string> _user_agent;
                std::shared_ptr<std::string> _path;

                std::shared_ptr<std::string> _host;
                std::shared_ptr<std::string> _model;
        };

        class MakeTemplateGET : public model_base{
            public:
                /**
                @param domain | shared_ptr Type -> < std::string > | This param used be for settings your model host
                @brief settings model host
                */
                    inline void model_host(const std::shared_ptr<std::string>&& domain) override {
                        _host = domain;
                    }
                /**
                @param path | shared_ptr Type -> < std::string > | This param used be for settings request path
                @brief settings model path
                */
                    inline void model_url_path(const std::shared_ptr<std::string>&& path) override {
                        _path = path;
                    }

                /**
                @param user_agent | shared_ptr Type -> < std::string > | This param used be for settings request User-Agent 
                */
                    inline void model_user_agnet(const std::shared_ptr<std::string>&& user_agent) override {
                        _user_agent = user_agent;
                    }
                /**
                @param key | std::string | This param used be for headers key name
                @param value | std::strinf | This param used be for headers value 
                */
                    inline void model_add_header(const std::string &key, const std::string &value) override {
                        _headers[key] = value;
                    }
                /**
                @brief get request templates
                @return string | templates
                */
                    inline std::string get_model() override {
                        std::string templates =
                        "GET " + *_path + " HTTP/1.1" + "\r\n"
                        "Host: " + *_host + "\r\n"
                        "User-Agent: " + *_user_agent + "\r\n";
                        for (const auto& [k , v] : _headers) {
                            if (!k.empty() && !v.empty()){
                                templates += k + ": " + v + "\r\n";
                            }else{
                                std::cout << "[WRAING] your request header is empty !" << std::endl;
                            }
                        }
                        templates += "Connection: close\r\n"; 
                        templates += "\r\n";
                        return templates;
                    }
                private:
                    /**
                    @param content_type | shared_ptr Type -> < std::string > | THis param used be for settings your model content_type
                    @brief settings model content-type
                    */
                        inline void model_content(const std::shared_ptr<std::string>&& content_type) override {
                            _content_type = content_type;
                        }
                    void model_body(const std::string &request_body) override {
                        return;
                    }
            };

            class MakeTemplatePOST : public model_base{
                private:
                    std::string _body;
                    size_t content_length;
                public:
                /**
                @param domain | shared_ptr Type -> < std::string > | This param used be for settings your model host
                @brief settings model host
                */
                    inline void model_host(const std::shared_ptr<std::string>&& domain) override {
                        _host = domain;
                    }
                /**
                @param content_type | shared_ptr Type -> < std::string > | THis param used be for settings your model content_type
                @brief settings model content-type
                */
                    inline void model_content(const std::shared_ptr<std::string>&& content_type) override {
                        _content_type = content_type;
                    }
                /**
                @param path | shared_ptr Type -> < std::string > | This param used be for settings request path
                @brief settings model path
                */
                    inline void model_url_path(const std::shared_ptr<std::string>&& path) override {
                        _path = path;
                    }

                /**
                @param user_agent | shared_ptr Type -> < std::string > | This param used be for settings request User-Agent 
                */
                    inline void model_user_agnet(const std::shared_ptr<std::string>&& user_agent) override {
                        _user_agent = user_agent;
                    }
                /**
                @param key | std::string | This param used be for headers key name
                @param value | std::strinf | This param used be for headers value 
                */
                    inline void model_add_header(const std::string &key, const std::string &value) override {
                        _headers[key] = value;
                    }

                /** 
                @param request_body | std::string | This param used be for settings post response body 
                @brief settings request body 
                    const std::string json = "{'hai' : 'hello world!'}"; 
                    object.model_body(json);
                */
                    inline void model_body(const std::string &request_body) override {
                        _body = request_body;
                        content_length = _body.size();
                    }
                /**
                @brief get request templates
                @return string | templates
                */
                    inline std::string get_model() override {
                        std::string templates =
                        "POST " + *_path + " HTTP/1.1" + "\r\n"
                        "Content-Type: " + *_content_type + "\r\n"
                        "Host: " + *_host + "\r\n"
                        "User-Agent: " + *_user_agent + "\r\n";
                        for (const auto& [k , v] : _headers) {
                            if (!k.empty() && !v.empty()){
                                templates += k + ": " + v + "\r\n";
                            }else{
                                std::cout << "[WARING] your request header is empty !" << std::endl;
                            }
                        }

                        templates += "Content-Length: " + std::to_string(content_length) + "\r\n";
                        templates += "Connection: close\r\n"; 
                        templates += "\r\n";
                        templates += _body;
                    
                        return templates;
                    }
            };
    }
}
#endif