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
#ifndef _KREQUEST_H_
#pragma once

#include <string>
#include <boost/asio.hpp>
#include <functional>
#include <memory>
#include <utility>
#include <vector>
#include "request/Krequest-request.h"
#include "method/object_templates.h"

namespace Krequest {
    class ClinetBase {
        public:
            virtual ~ClinetBase() = default;
            virtual ClinetBase& SetClientDomain (const std::string& domain) {return *this;};
            virtual ClinetBase& SetClientContentType (const std::string& content_type) {return *this;};
            virtual ClinetBase& SetClientPath (const std::string& path) {return *this;};
            virtual ClinetBase& AddClientHeader (const std::string& key , const std::string& value) {return *this;};
            virtual ClinetBase& SetUserAgent (const std::string& user_agent) {return *this;};
            virtual ClinetBase& SetRequestBody (const std::string& request_body) {return *this;};
            virtual ClinetBase& onCallback (const std::function<void()>& _onCallback) {return *this;};
            virtual ClinetBase& onfailCallbak (const std::function<void()>& _failCallback) {return *this;};
            virtual ClinetBase& StartRequest() {return *this;};
            virtual std::string GetStatusCode() = 0;
            virtual std::string GetHttpVersion() = 0;
            virtual std::string GetStatusMessage() = 0;
            virtual std::vector<char> GetResponseBody() = 0;
        protected:
            std::string __path__;
            std::string __domain__;
            std::string __content_type__;
            std::string __key__;
            std::string __value__;
            std::string __user_agent__;
            std::string __request_body__;
    };

// ============================================= HTTP CLIENT CLASS ==================================================================
    class HttpClientGet : public ClinetBase {
        private:
            std::string status_code;
            std::string http_version;
            std::string status_message;
            std::vector<char> response_body;
            std::shared_ptr<KING::Krequest::MakeTemplateGET> ModleTemplateGet;
            std::shared_ptr<KING::Krequest::HttpClientRequest> HttpClientGet_Object;
        public:
        HttpClientGet(){ 
            ModleTemplateGet = std::make_shared<KING::Krequest::MakeTemplateGET>();
            HttpClientGet_Object = std::make_shared<KING::Krequest::HttpClientRequest>();
        }
        /**
        @param domain string | This param used be for settings your request host
        @brief Get user host 
        */
            HttpClientGet& SetClientDomain(const std::string &domain) override {
                __domain__ = domain; 
                return *this;
            }
            
        /**
        @brief Get HTTP version
        @return string | http version
        */
            std::string GetHttpVersion() override {
                return http_version;
            }
        /**
        @param content_type string | This param used be for settings your request fetch type
        @brief Get user content type  
        */
            HttpClientGet& SetClientContentType(const std::string &content_type) override {
                __content_type__ = content_type; 
                return *this;
            }
        /**
        @param path string | This param used be for settings your request url path
        @brief setting request url path
        */
            HttpClientGet& SetClientPath(const std::string &path) override {
                __path__ = path; 
                return *this;         
            }
        /**
        @param key string | This param used be for settings your header key name
        @param value string | This param used be for settings your header value
        @brief setting request header 
        */
            HttpClientGet& AddClientHeader(const std::string &key, const std::string &value) override {
                __key__ = key;
                __value__ = value;
                return *this;
            }
        /**
        @param user_agent string| This param used be for settings your header key name
        @brief setting request User-Agent
        */
            HttpClientGet& SetUserAgent(const std::string &user_agent) override {
                __user_agent__ = user_agent;
                return *this;
            }
        /**
        @param _onCallback std::function Type -> < void() > | request success function callback
        @brief success function callback 
        */
            HttpClientGet& onCallback(const std::function<void()> &_onCallback) override {
                return *this;
            }
        /**
        @param _failCallback std::function Type -> < void() > | request fail  function callback
        @brief fail function callback
        */
            HttpClientGet& onfailCallbak(const std::function<void ()> &_failCallback) override {
                return *this;
            }
        /**
        @brief Get response status code
        @return string | status code
        */
            std::string GetStatusCode() override {
                return status_code;
            }
        /**
        @brief Get response status messsage
        @return string | status message
        */
            std::string GetStatusMessage() override {
                return status_message;
            }
        /**
        @brief Get response body data
        @return vector Type -> < char > | response body
        */
            std::vector<char> GetResponseBody() override {
                return response_body;
            }

            HttpClientGet& StartRequest() override {
                //get templates
                ModleTemplateGet -> model_host(std::make_shared<std::string>(__domain__));
                ModleTemplateGet -> model_add_header(__key__, __value__);
                ModleTemplateGet -> model_user_agnet(std::make_shared<std::string>(__user_agent__));
                ModleTemplateGet -> model_url_path(std::make_shared<std::string>(__path__));
                const std::string __templates_ = ModleTemplateGet -> get_model();

                HttpClientGet_Object -> set_host(std::make_shared<std::string>(__domain__));
                HttpClientGet_Object -> set_request_templates(std::make_shared<std::string>(__templates_));
                HttpClientGet_Object -> start_request();

                response_body = HttpClientGet_Object -> get_response_body();
                status_code = HttpClientGet_Object -> get_response_status_code();
                status_message = HttpClientGet_Object -> get_response_status_message();
                http_version = HttpClientGet_Object -> get_http_version_();

                return *this;
            }      
    };
    
      class HttpClientPost : public ClinetBase {
        private:
            std::string status_code;
            std::string http_version;
            std::string status_message;
            std::vector<char> response_body;
            std::shared_ptr<KING::Krequest::MakeTemplatePOST> ModleTemplatePost;
            std::shared_ptr<KING::Krequest::HttpClientRequest> HttpClientPost_Object;
        public:

        HttpClientPost(): ModleTemplatePost(){
            ModleTemplatePost = std::make_shared<KING::Krequest::MakeTemplatePOST>();
            HttpClientPost_Object = std::make_shared<KING::Krequest::HttpClientRequest>();
        }
        /**
        @param domain string | This param used be for settings your request host
        @brief Get user host 
        */
            HttpClientPost& SetClientDomain(const std::string &domain) override {
                __domain__ = domain; 
                return *this;
            }
        /**
        @param content_type string | This param used be for settings your request fetch type
        @brief Get user content type  
        */
            HttpClientPost& SetClientContentType(const std::string &content_type) override {
                __content_type__ = content_type; 
                return *this;
            }
        
        /**
        @brief Get HTTP version
        @return string | http version
        */
            std::string GetHttpVersion() override {
                return http_version;
            }
        /**
        @param path string | This param used be for settings your request url path
        @brief setting request url path
        */
            HttpClientPost& SetClientPath(const std::string &path) override {
                __path__ = path; 
                return *this;         
            }
        /**
        @param key string | This param used be for settings your header key name
        @param value string | This param used be for settings your header value
        @brief setting request header 
        */
            HttpClientPost& AddClientHeader(const std::string &key, const std::string &value) override {
                __key__ = key;
                __value__ = value;
                return *this;
            }
        /**
        @param request_bodt string | This param used be for settings your post request body data
        @brief setting request body
        */
            HttpClientPost& SetRequestBody(const std::string &request_body) override {
                __request_body__ = request_body;
                return *this;
            }
        /**
        @param user_agent string| This param used be for settings your header key name
        @brief setting request User-Agent
        */
            HttpClientPost& SetUserAgent(const std::string &user_agent) override {
                __user_agent__ = user_agent;
                return *this;
            }
        /**
        @param _onCallback std::function Type -> < void() > | request success function callback
        @brief success function callback 
        */
            HttpClientPost& onCallback(const std::function<void()> &_onCallback) override {
                return *this;
            }
        /**
        @param _failCallback std::function Type -> < void() > | request fail  function callback
        @brief fail function callback
        */
            HttpClientPost& onfailCallbak(const std::function<void ()> &_failCallback) override {
                return *this;
            }
        /**
        @brief Get response status code
        @return string | status code
        */
            std::string GetStatusCode() override {
                return status_code;
            }
        /**
        @brief Get response status messsage
        @return string | status message
        */
            std::string GetStatusMessage() override {
                return status_message;
            }
        /**
        @brief Get response body data
        @return vector Type -> < char > | response body
        */
            std::vector<char> GetResponseBody() override {
                return response_body;
            }

            HttpClientPost& StartRequest() override {
                //get templates
                ModleTemplatePost -> model_host(std::make_shared<std::string>(__domain__));
                ModleTemplatePost -> model_add_header(__key__, __value__);
                ModleTemplatePost -> model_user_agnet(std::make_shared<std::string>(__user_agent__));
                ModleTemplatePost -> model_content(std::make_shared<std::string>(__content_type__));
                ModleTemplatePost -> model_url_path(std::make_shared<std::string>(__path__));
                ModleTemplatePost -> model_body(__request_body__);
                const std::string __templates_ = ModleTemplatePost -> get_model();

                HttpClientPost_Object -> set_host(std::make_shared<std::string>(__domain__));
                HttpClientPost_Object -> set_request_templates(std::make_shared<std::string>(__templates_));
                HttpClientPost_Object -> start_request();

                response_body = HttpClientPost_Object -> get_response_body();
                status_code = HttpClientPost_Object -> get_response_status_code();
                status_message = HttpClientPost_Object -> get_response_status_message();
                http_version = HttpClientPost_Object -> get_http_version_();

                return *this;
            }      
    };
//========================================== SSL CLIENT CLASS ===================================================
     class SSLClientGet : public ClinetBase {
        private:
            std::string status_code;
            std::string http_version;
            std::string status_message;
            std::vector<char> response_body;
            std::shared_ptr<KING::Krequest::MakeTemplateGET> ModleTemplateGet;
            std::shared_ptr<KING::Krequest::SSLClientRequest> SSLClientGet_Object;
        public:
        SSLClientGet(){ ModleTemplateGet = std::make_shared<KING::Krequest::MakeTemplateGET>() 
            , SSLClientGet_Object = std::make_shared<KING::Krequest::SSLClientRequest>();} 
        /**
        @param domain string | This param used be for settings your request host
        @brief Get user host 
        */
            SSLClientGet& SetClientDomain(const std::string &domain) override {
                __domain__ = domain; 
                return *this;
            }
        /**
        @param content_type string | This param used be for settings your request fetch type
        @brief Get user content type  
        */
            SSLClientGet& SetClientContentType(const std::string &content_type) override {
                __content_type__ = content_type; 
                return *this;
            }
        /**
        @param path string | This param used be for settings your request url path
        @brief setting request url path
        */
            SSLClientGet& SetClientPath(const std::string &path) override {
                __path__ = path; 
                return *this;         
            }
        /**
        @param key string | This param used be for settings your header key name
        @param value string | This param used be for settings your header value
        @brief setting request header 
        */
            SSLClientGet& AddClientHeader(const std::string &key, const std::string &value) override {
                __key__ = key;
                __value__ = value;
                return *this;
            }
        /**
        @param user_agent string| This param used be for settings your header key name
        @brief setting request User-Agent
        */
            SSLClientGet& SetUserAgent(const std::string &user_agent) override {
                __user_agent__ = user_agent;
                return *this;
            }
        /**
        @param _onCallback std::function Type -> < void() > | request success function callback
        @brief success function callback 
        */
            SSLClientGet& onCallback(const std::function<void()> &_onCallback) override {
                return *this;
            }
        /**
        @param _failCallback std::function Type -> < void() > | request fail  function callback
        @brief fail function callback
        */
            SSLClientGet& onfailCallbak(const std::function<void ()> &_failCallback) override {
                return *this;
            }
        /**
        @brief Get response status code
        @return string | status code
        */
            std::string GetStatusCode() override {
                return status_code;
            }
        /**
        @brief Get response status messsage
        @return string | status message
        */
            std::string GetStatusMessage() override {
                return status_message;
            }
        
        /**
        @brief Get HTTP version
        @return string | http version
        */
            std::string GetHttpVersion() override {
                return http_version;
            }
        /**
        @brief Get response body data
        @return vector Type -> < char > | response body
        */
            std::vector<char> GetResponseBody() override {
                return response_body;
            }

            SSLClientGet& StartRequest() override {
                //get templates
                ModleTemplateGet -> model_host(std::make_shared<std::string>(__domain__));
                ModleTemplateGet -> model_add_header(__key__, __value__);
                ModleTemplateGet -> model_user_agnet(std::make_shared<std::string>(__user_agent__));
                ModleTemplateGet -> model_url_path(std::make_shared<std::string>(__path__));
                const std::string __templates_ = ModleTemplateGet -> get_model();

                SSLClientGet_Object -> set_host(std::make_shared<std::string>(__domain__));
                SSLClientGet_Object -> set_request_templates(std::make_shared<std::string>(__templates_));
                SSLClientGet_Object -> start_request();

                response_body = SSLClientGet_Object -> get_response_body();
                status_code = SSLClientGet_Object -> get_response_status_code();
                status_message = SSLClientGet_Object -> get_response_status_message();
                http_version = SSLClientGet_Object -> get_http_version_();

                return *this;
            }      
    };
    
      class SSLClientPost : public ClinetBase {
        private:
            std::string status_code;
            std::string http_version;
            std::string status_message;
            std::vector<char> response_body;
            std::shared_ptr<KING::Krequest::MakeTemplatePOST> ModleTemplatePost;
            std::shared_ptr<KING::Krequest::SSLClientRequest> SSLClientPost_Object;
        public:
        SSLClientPost(){ModleTemplatePost = std::make_shared<KING::Krequest::MakeTemplatePOST>() 
            , SSLClientPost_Object = std::make_shared<KING::Krequest::SSLClientRequest>();}
        /**
        @param domain string | This param used be for settings your request host
        @brief Get user host 
        */
            SSLClientPost& SetClientDomain(const std::string &domain) override {
                __domain__ = domain; 
                return *this;
            }
        /**
        @param content_type string | This param used be for settings your request fetch type
        @brief Get user content type  
        */
            SSLClientPost& SetClientContentType(const std::string &content_type) override {
                __content_type__ = content_type; 
                return *this;
            }
        /**
        @param path string | This param used be for settings your request url path
        @brief setting request url path
        */
            SSLClientPost& SetClientPath(const std::string &path) override {
                __path__ = path; 
                return *this;         
            }
        /**
        @param key string | This param used be for settings your header key name
        @param value string | This param used be for settings your header value
        @brief setting request header 
        */
            SSLClientPost& AddClientHeader(const std::string &key, const std::string &value) override {
                __key__ = key;
                __value__ = value;
                return *this;
            }
        /**
        @param request_bodt string | This param used be for settings your post request body data
        @brief setting request body
        */
            SSLClientPost& SetRequestBody(const std::string &request_body) override {
                __request_body__ = request_body;
                return *this;
            }
        /**
        @param user_agent string| This param used be for settings your header key name
        @brief setting request User-Agent
        */
            SSLClientPost& SetUserAgent(const std::string &user_agent) override {
                __user_agent__ = user_agent;
                return *this;
            }
        /**
        @param _onCallback std::function Type -> < void() > | request success function callback
        @brief success function callback 
        */
            SSLClientPost& onCallback(const std::function<void()> &_onCallback) override {
                return *this;
            }
        /**
        @param _failCallback std::function Type -> < void() > | request fail  function callback
        @brief fail function callback
        */
            SSLClientPost& onfailCallbak(const std::function<void ()> &_failCallback) override {
                return *this;
            }
        /**
        @brief Get response status code
        @return string | status code
        */
            std::string GetStatusCode() override {
                return status_code;
            }
        /**
        @brief Get response status messsage
        @return string | status message
        */
            std::string GetStatusMessage() override {
                return status_message;
            }
        
        /**
        @brief Get HTTP version
        @return string | http version
        */
            std::string GetHttpVersion() override {
                return http_version;
            }
        /**
        @brief Get response body data
        @return vector Type -> < char > | response body
        */
            std::vector<char> GetResponseBody() override {
                return response_body;
            }

            SSLClientPost& StartRequest() override {
                //get templates
                ModleTemplatePost -> model_host(std::make_shared<std::string>(__domain__));
                ModleTemplatePost -> model_add_header(__key__, __value__);
                ModleTemplatePost -> model_user_agnet(std::make_shared<std::string>(__user_agent__));
                ModleTemplatePost -> model_content(std::make_shared<std::string>(__content_type__));
                ModleTemplatePost -> model_url_path(std::make_shared<std::string>(__path__));
                ModleTemplatePost -> model_body(__request_body__);
                const std::string __templates_ = ModleTemplatePost -> get_model();

                SSLClientPost_Object -> set_host(std::make_shared<std::string>(__domain__));
                SSLClientPost_Object -> set_request_templates(std::make_shared<std::string>(__templates_));
                SSLClientPost_Object -> start_request();

                response_body = SSLClientPost_Object -> get_response_body();
                status_code = SSLClientPost_Object -> get_response_status_code();
                status_message = SSLClientPost_Object -> get_response_status_message();
                http_version = SSLClientPost_Object -> get_http_version_();

                return *this;
            }      
    };
}
#endif