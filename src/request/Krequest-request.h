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
*@file Krequest-request.h
*@author kwzDev
*@date 2026.1.21 14:49
*@brief ZH-CN > 基于'Boost.Asio'库编写的C++Http客户端请求工具 | EN > Krequest is a lightweight, high-performance,
 and header-only HTTP client library for C++, built on top of the robust Boost.Asio. 
 Designed with simplicity and modern C++ practices in mind, it provides both synchronous 
 and asynchronous APIs to handle HTTP requests effortlessly.
*/

#define BOOST_ASIO_DISABLE_CONCEPTS 1
#define BOOST_ASIO_NO_DEPRECATED 1
#define BOOST_ASIO_NO_TS_EXECUTORS 1
#ifndef _KREQUEST_REQUEST_H

#pragma once
#include <boost/asio/ssl/stream_base.hpp>
#include <openssl/ssl.h>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/resolver_base.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/detail/error_code.hpp>
#include <boost/asio/ssl.hpp>
#include <cstddef>
#include <istream>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include <utility>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost::asio::ssl;

namespace KING {
    namespace KRQ {
        template<typename Derived>
        class Requestbase {
            protected:
            //request tools base http 
                boost::asio::io_context _io;
                boost::asio::ip::tcp::socket _socket;
                std::shared_ptr<std::string> _host;
                std::shared_ptr<std::string> _model_template;
                std::shared_ptr<tcp::resolver> _resolver;
            //request tool ssl            
                std::shared_ptr<boost::asio::ssl::context> ssl_ctx;
                std::unique_ptr<boost::asio::ssl::stream<tcp::socket&>> ssl_stream;
            public:
                //method function  
                virtual ~Requestbase() = default;
                Requestbase(): _io(boost::asio::io_context()) , _socket(_io) , _resolver(std::make_shared<tcp::resolver>(_io)) {
                    ssl_ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);
                    ssl_stream = std::make_unique<boost::asio::ssl::stream
                    <boost::asio::ip::tcp::socket&>>(_socket , *ssl_ctx);
                    ssl_ctx->set_options(
                        ssl::context::default_workarounds |
                        ssl::context::no_sslv2 |
                        ssl::context::no_sslv3
                    );
                    ssl_ctx->set_default_verify_paths();
                }
                virtual inline void set_templates(const std::shared_ptr<std::string>& model_template) = 0;
                virtual inline void set_host(const std::shared_ptr<std::string>& host) = 0;
                virtual inline void resolver_host() = 0;
                virtual inline void connection_tcp(const std::shared_ptr<Derived>& _self , const tcp::resolver::results_type& _endpoint) = 0;
                virtual inline void sendTemplate(const std::shared_ptr<Derived>& _self) = 0;
                virtual inline std::string getStatusCode() = 0;
                virtual inline std::string getHttpVersion() = 0;
                virtual inline std::string getStatusMessage() = 0;
                virtual inline std::vector<char> getResponseBody() = 0;

                //response result
                std::string _status_code;
                std::string _status_message;
                std::string _http_version;
                std::vector<char> _response_body;
        };
        class SSLResponse : public std::enable_shared_from_this<SSLResponse> , 
            Requestbase<SSLResponse> 
            {
                public:
                    /** 
                    @brief get status code 
                    @return string | status code
                    */
                    inline std::string getStatusCode() override {
                        return _status_code;
                    }
                    /**
                    @brief get response body
                    @return vector <char> | response body
                    */
                    inline std::vector<char> getResponseBody() override {
                        return _response_body;
                    }
                    /**
                    @brief get http version 
                    @return string | http version
                    */
                    inline std::string getHttpVersion() override {
                        return _http_version;
                    }
                    /**
                    @brief get status message
                    @return string | http status message
                    */
                    inline std::string getStatusMessage() override {
                        return _status_message;
                    }
                    /**
                    @param model_template shared_ptr -> Type < std::string > | This param used be for settinsg request data
                    @brief settings request data
                    */
                    inline void set_templates(const std::shared_ptr<std::string>& model_template) override{
                        if (model_template == nullptr){
                            std::cout << "[ERROR] Your model_templates is nullptr" << std::endl;
                            return;
                        }
                        _model_template = model_template;
                    }
                    /**
                    @param host shared_ptr Type -> < std::string > | This param used be for settings request host
                    @brief settings request host
                    */
                    inline void set_host(const std::shared_ptr<std::string>& host) override{
                        if (host == nullptr){
                            std::cout << "[ERROR] Your host is nullptr!" << std::endl;
                            return;
                        }
                        _host = host;
                    }

                    /**
                    @brief resolver domain
                    */
                    inline void resolver_host() override {
                        std::shared_ptr<SSLResponse> self = shared_from_this();
                        _resolver->async_resolve(*_host , "443" , [this , self]
                            (boost::system::error_code ec , boost::asio::ip::tcp::resolver::results_type endpoints){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a" 
                                    << ec.what() << "\a<== [ERROR]" << std::endl;
                                    return;
                                }
                                connection_tcp(self, endpoints);
                        });
                        _io.run();
                    }

                /**
                @param _self shared_ptr -> Type < KING::KQR::HttpResponse >| This param used be for async function callback
                @param _endpoint tcp::resolver::endpoint_type | This param used be for tcp shake hands 
                */
                    inline void connection_tcp(const std::shared_ptr<KING::KRQ::SSLResponse> &_self, const tcp::resolver::results_type &_endpoint) override {
                        (void) boost::asio::async_connect(ssl_stream -> next_layer() , _endpoint , [this , _self ]
                            (boost::system::error_code ec ,tcp::endpoint endpoint_){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a" 
                                    << ec.what() << "<== [ERROR]" << std::endl;
                                    return;
                                }

                                if (!SSL_set_tlsext_host_name(ssl_stream->native_handle(), _host->c_str())) {
                                    std::cout << "[ERROR] SNI setting fail" << std::endl;
                                    return;
                                }

                                sslHandshake(_self);
                            });
                    }
                /**
                @param _self shared_ptr -> Type < KING::KQR::HttpResponse >| This param used be for async function callback
                */
                    inline void sslHandshake (const std::shared_ptr<KING::KRQ::SSLResponse>& _self) {
                        (void) ssl_stream -> async_handshake(boost::asio::ssl::stream_base::client , [this , _self]
                            (boost::system::error_code ec){
                                if (ec) {
                                    std::cout << "[ERROR] ==> TCP handshake error \a" 
                                    << ec.what() << "<== [ERROR]" << std::endl;
                                    return;
                                }
                                sendTemplate(_self);
                            });
                    }

                /**
                @param _self shared_ptr -> Type < KING::KQR::HttpResponse >| This param used be for async function callback
                */
                    inline void sendTemplate(const std::shared_ptr<KING::KRQ::SSLResponse> &_self) override {
                        if (_model_template == nullptr) {
                            std::cout << "[ERROR] Your model_templates is nullptr" << std::endl;
                            return;
                        }
                        (void) async_write(*ssl_stream , boost::asio::buffer(*_model_template) , [this , _self]
                            (boost::system::error_code ec , size_t bytes_transferred){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a" 
                                    << ec.what() << "<== [ERROR]" << std::endl;
                                    return;
                                }
                                resolverResponse(*ssl_stream, _self);
                            });
                    }

                /**
                @param _socket basic_stream_socket Type -> < boost::asio::ip::tcp::socket > | This param used be for async read a response data
                @param 
                */
                    template<typename SocketType>
                    inline void resolverResponse (SocketType& socket , const std::shared_ptr<SSLResponse>& _self) {
                        auto response_buffer = std::make_shared<boost::asio::streambuf>();
                        boost::asio::async_read_until(socket , *response_buffer , "\r\n\r\n" , [this , &socket , _self , response_buffer](
                            boost::system::error_code ec , std::size_t bytes_transferred){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a" 
                                    << ec.what() << "\a <==" << std::endl;
                                    return;
                                }

                                std::istream response_stream(response_buffer.get());
                                std::string http_version;
                                std::string http_status_code;   
                                std::string http_status_message;

                                std::string status_line;
                                std::getline(response_stream , status_line);

                                std::istringstream status_stream(status_line);
                                status_stream >> http_version >> http_status_code;
                                std::getline(status_stream >> std::ws , http_status_message);

                                _status_code = http_status_code;
                                _http_version = http_version;
                                _status_message = http_status_message;

                                //get body
                                std::size_t content_lenght = 0;
                                std::string header_line;
                                std::unordered_map<std::string,std::string> headers;

                                while (getline(response_stream , header_line) && header_line != "\r") {
                                    size_t colon_pos = header_line.find(":");

                                    if (colon_pos != std::string::npos) {
                                        std::string key = header_line.substr(0 , colon_pos);
                                        std::string value = header_line.substr(colon_pos + 2);
                                        headers[key] = value;

                                        if (key == "Content-Length") {
                                            content_lenght = std::stoul(value);
                                        }
                                    }
                                }

                                if (content_lenght > 0) {
                                    std::size_t already_in_buffer = response_buffer -> size();

                                    if (already_in_buffer >= content_lenght) {
                                        std::vector<char> body(content_lenght);
                                        response_stream.read(body.data(), already_in_buffer);
                                        std::size_t remaining = content_lenght - already_in_buffer;

                                        (void) boost::asio::async_read(socket, boost::asio::buffer
                                            (body.data() + already_in_buffer,remaining),[
                                                this , _self , body = std::move(body) , content_lenght
                                            ](boost::system::error_code ec , std::size_t bytes__){
                                                if (!ec  && bytes__ > 0) {
                                                    _response_body = body;
                                                }else if (ec) {                
                                                    std::cout << "[WRAING] ==> this response is empty" 
                                                    << "<== " << std::endl;
                                                }
                                                _io.stop();
                                                return;
                                            });
                                    }
                                }else {
                                    return;
                                }
                            });
                    }
            };

        class HttpResponse : public std::enable_shared_from_this<HttpResponse> ,
            Requestbase<HttpResponse>
            {
                public:
                    /** 
                    @brief get status code 
                    @return string | status code
                    */
                    inline std::string getStatusCode() override{
                        return _status_code;
                    }

                    /**
                    @brief get http version 
                    @return string | http version
                    */
                    inline std::string getHttpVersion() override {
                        return _http_version;
                    }

                    /**
                    @brief get response body
                    @return vector <char> | response body
                    */
                    inline std::vector<char> getResponseBody() override{
                        return _response_body;
                    }

                    /**
                    @brief get status message
                    @return string | http status message
                    */
                    inline std::string getStatusMessage() override {
                        return _status_message;
                    }

                    /**
                    @param model_template shared_ptr -> Type < std::string > | This param used be for settinsg request data
                    @brief settings request data
                    */
                    inline void set_templates(const std::shared_ptr<std::string>& model_template) override{
                        if (model_template == nullptr) {
                            std::cout << "[ERROR] Your model_templates is nullptr" << std::endl;
                            return;
                        }
                        _model_template = model_template;
                    }

                    /**
                    @param host shared_ptr Type -> < std::string > | This param used be for settings request host
                    @brief settings request host
                    */
                    inline void set_host(const std::shared_ptr<std::string>& host) override{
                        if (host == nullptr){
                            std::cout << "[ERROR] Your host is nullptr!" << std::endl;
                            return;
                        }
                        _host = host;
                    }

                    /**
                    @brief resolver domain
                    */
                    void resolver_host() override{
                        const shared_ptr<HttpResponse> self = shared_from_this();
                        _resolver -> async_resolve(*_host , "80" , [this , self](
                            const boost::system::error_code ec , const tcp::resolver::results_type endpoints
                        ){
                            if (ec){
                                std::cout << "[ERROR] : ===>> \a" 
                                << ec.what() << "\a<<=== [ERROR]" 
                                << std::endl;
                                return;
                            }

                            //connection host
                            connection_tcp(self , endpoints);
                        });
                        _io.run();
                    }
                private:
                /**
                @param _self shared_ptr -> Type < KING::KQR::HttpResponse >| This param used be for async function callback
                @param _endpoint tcp::resolver::endpoint_type | This param used be for tcp shake hands 
                */
                    inline void connection_tcp(const std::shared_ptr<KING::KRQ::HttpResponse> &_self
                        , const tcp::resolver::results_type& _endpoint) override {
                            (void) async_connect(_socket , _endpoint
                            , [this , _self]
                                (const boost::system::error_code ec , boost::asio::ip::tcp::endpoint connected_endpoint){
                                    if(ec){
                                        std::cout << "[ERROR] ==> \a" 
                                        << ec.what() << "\a <== [ERROR]" << std::endl;
                                        return;
                                    }
                                    std::cout << "[INFO] \a Start request \n" << *_model_template << std::endl;
                                    //success send templates
                                    sendTemplate(_self);
                            });
                            _io.run();
                        }
                /**
                @param _self shared_ptr Type -> < KING::KQR::HttpResponse > | This param used be for async function callback
                */
                    inline void sendTemplate(const std::shared_ptr<KING::KRQ::HttpResponse>& _self) override {
                        if (_model_template == nullptr){
                            std::cout << "[ERROR] ==> \a" 
                            << "Your model is nullptr !" << "\a <== [ERROR]"
                            << std::endl;
                            return;
                        }

                        (void) async_write(_socket , boost::asio::buffer(*_model_template),[this , _self]
                            (const boost::system::error_code ec , const size_t bytes_transferred){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a"
                                    << ec.what() << std::endl;
                                    return;
                                }
                                resolverResponse(_socket, _self);
                            });
                    }
                    
                    
                /**
                @param _socket basic_stream_socket Type -> < boost::asio::ip::tcp::socket > | This param used be for async read a response data
                @param _self shared_ptr Type -> < KING::KQR:: class_name > | This param used be for async function callback
                */
                    template<typename SocketType , typename FunctionType>
                    inline void resolverResponse (SocketType& socket , const std::shared_ptr<FunctionType>& _self) {
                        auto response_buffer = std::make_shared<boost::asio::streambuf>();
                        boost::asio::async_read_until(socket , *response_buffer , "\r\n\r\n" , [this , &socket , _self , response_buffer](
                            const boost::system::error_code ec , const std::size_t bytes_transferred){
                                if (ec) {
                                    std::cout << "[ERROR] ==> \a" 
                                    << ec.what() << "\a <==" << std::endl;
                                    return;
                                }

                                std::istream response_stream(response_buffer.get());
                                std::string http_version;
                                std::string http_status_code;   
                                std::string http_status_message;

                                std::string status_line;
                                std::getline(response_stream , status_line);

                                std::istringstream status_stream(status_line);
                                status_stream >> http_version >> http_status_code;
                                std::getline(status_stream >> std::ws , http_status_message);

                                _status_code = http_status_code;
                                _http_version = http_version;
                                _status_message = http_status_message;

                                //get body
                                std::size_t content_lenght = 0;
                                std::string header_line;
                                std::unordered_map<std::string,std::string> headers;

                                while (getline(response_stream , header_line) && header_line != "\r") {
                                    size_t colon_pos = header_line.find(":");

                                    if (colon_pos != std::string::npos) {
                                        std::string key = header_line.substr(0 , colon_pos);
                                        std::string value = header_line.substr(colon_pos + 2);
                                        headers[key] = value;

                                        if (key == "Content-Length") {
                                            content_lenght = std::stoul(value);
                                        }
                                    }
                                }

                                if (content_lenght > 0) {
                                    std::size_t already_in_buffer = response_buffer -> size();

                                    if (already_in_buffer >= content_lenght) {
                                        std::vector<char> body(content_lenght);
                                        response_stream.read(body.data(), already_in_buffer);
                                        std::size_t remaining = content_lenght - already_in_buffer;

                                        (void) boost::asio::async_read(socket, boost::asio::buffer
                                            (body.data() + already_in_buffer,remaining),[
                                                this , _self , body = std::move(body) , content_lenght
                                            ](const boost::system::error_code& ec , std::size_t){
                                                _response_body = body;
                                            });
                                    }
                                }else {
                                    _io.stop();
                                    _socket.close();
                                    return;
                                }
                            });
                    }
        };
    }
}
#endif