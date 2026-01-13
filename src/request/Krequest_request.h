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
*@file Krequest_request.h
*@author kwzDev
*@date 2026.1.21 14:49
*@brief ZH-CN > 基于'Boost.Asio'库编写的C++Http客户端请求工具 | EN > Krequest is a lightweight, high-performance,
 and header-only HTTP client library for C++, built on top of the robust Boost.Asio. 
 Designed with simplicity and modern C++ practices in mind, it provides both synchronous 
 and asynchronous APIs to handle HTTP requests effortlessly.
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/ssl/stream_base.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/system/detail/error_code.hpp>
#include <cstddef>
#include <istream>
#include <memory>
#include <openssl/crypto.h>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ssl;
using namespace boost::asio::ip;

#ifdef __clang__
#pragma clang diagnostic push
#endif

namespace Krequest {
    namespace request {
        class k_request : public std::enable_shared_from_this<k_request>{
            private:
            io_context _io;
            tcp::socket _socket;
            tcp::resolver _resolver;

            std::shared_ptr<std::string> _domain;
            std::shared_ptr<std::string> _model;
            bool _ssl;

            std::vector<char> _http_response_body;
            std::string _http_status_code;
            std::string _http_version;
            std::string _status_message;

            std::shared_ptr<boost::asio::ssl::stream<tcp::socket>> ssl_stream;

            bool ssl;

            public:
            k_request():_resolver(_io) , _socket(_io){}

            inline void request_model (const std::shared_ptr<std::string>&& model) {
                _model = std::move(model);
            }

            inline void request (const std::shared_ptr<std::string>& domain ,bool& ssl){
                _domain = domain;
                if(ssl){
                    //ssl connection
                    _resolver.async_resolve(*_domain , "443" , [this , self = shared_from_this()] (const boost::system::error_code& ec 
                        , const tcp::resolver::results_type& endpoints){
                            if (ec){
                                std::cout << "[ERROR] : " << ec.what() << std::endl;
                                return;
                            }
                            onConnection_ssl(endpoints);
                    });
                }
                else{
                    //http connection
                    _resolver.async_resolve(*_domain , "80" , [this , self = shared_from_this()] (const boost::system::error_code ec
                        ,const tcp::resolver::results_type& endpoints){
                            if(ec){
                                std::cout << "[ERROR] : " << ec.what() << std::endl;
                                return;
                            }
                            onConnection_plain(endpoints);
                        });
                    return;
                };
            }

            inline std::string get_response_code () const{
                return _http_status_code;
            }

            inline std::string get_response_version () const{
                return _http_version;
            }

            inline std::string get_response_status_message () const{
                return _status_message;
            }

            inline std::vector<char> get_response_body() const{
                return _http_response_body;
            }
            private:
                inline void onConnection_ssl(const tcp::resolver::results_type& endpoints) {
                    auto ssl_ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::tls_client);
                    ssl_ctx -> set_default_verify_paths();
                    
                    ssl_stream = std::make_shared<boost::asio::ssl::stream<tcp::socket>>(_io, *ssl_ctx);

                    (void) boost::asio::async_connect(ssl_stream -> next_layer() 
                    , endpoints , [this , self = shared_from_this() , ssl_ctx](const boost::system::error_code& ec 
                        , const tcp::endpoint& endpoint) {
                        if (ec) {
                            std::cout << "[ERROR] -->" << ec.what() << "<--" << std::endl;
                        }
                        (void) ssl_stream -> async_handshake(boost::asio::ssl::stream_base::client , 
                            [this , self ](const boost::system::error_code& ec){
                                if (ec){
                                    std::cout << "[SSL_ERROR] --> " 
                                    << ec.what()  << "<-- \a" 
                                    << std::endl;
                                }
                                on_connecte_ssl(*_model , ssl_stream);
                            });
                    });
                }

                inline void onConnection_plain(const tcp::resolver::results_type& endpoints){
                    (void) async_connect( _socket , endpoints , [this, self = shared_from_this()](const boost::system::error_code& ec,const tcp::endpoint& endpoint_){
                        if (ec){
                            std::cout << "[ERROR] --> TCP connection fail --> " 
                            << ec.what() << " <--" << std::endl;
                            return;
                        }
                        on_connecte_plain(*_model);
                    });
                }

                inline void on_connecte_ssl(const std::string& request_model ,const std::shared_ptr<boost::asio::ssl::stream<
                    boost::asio::ip::tcp::socket>>& ssl_stream) {
                    if (request_model == ""){
                        std::cout << "[ERROR] --> request model is not empty ! " << std::endl;
                        return;
                    }

                    boost::asio::async_write(*ssl_stream , boost::asio::buffer(request_model),[
                        this , self = shared_from_this() , ssl_stream ](const boost::system::error_code& ec ,
                            const std::size_t bytes_transferred){
                            if (ec) {
                            std::cout << "[ERROR] --> " 
                            << ec.what() << " <--" << std::endl;
                            return;
                        }
                        get_response(*ssl_stream);
                    });
                }

                inline void on_connecte_plain(const std::string& request_model){
                    if (request_model == ""){
                        std::cout << "[ERROR] --> request model is not empty ! " << std::endl;
                        return;
                    }

                    boost::asio::async_write(_socket , boost::asio::buffer(request_model), 
                    [ this , self = shared_from_this() ](const boost::system::error_code& ec 
                        , const size_t bytes_transferred){
                        if (ec){
                            std::cout << "[ERROR] --> " 
                            << ec.what() << " <--" << std::endl;
                            return;
                        }
                        get_response(_socket);
                    });
                }

                template<typename stream_Type>
                inline void get_response(stream_Type& stream){
                        auto response_buffer = std::make_shared<boost::asio::streambuf>();
                        boost::asio::async_read_until(stream , *response_buffer , "\r\n\r\n",
                        [this,self = shared_from_this() , &stream , response_buffer](
                            const boost::system::error_code ec , const std::size_t bytes_transferred
                        ){
                            if (ec){
                                std::cout << "[ERROR] --> " 
                                << ec.what() << "< --" 
                                << std::endl;
                                return;
                            }

                            std::istream response_stream(response_buffer.get());
                            std::string http_version;
                            std::string status_code;
                            std::string status_message;

                            std::getline(response_stream >> std::ws, status_message);

                            _http_status_code = status_code;
                            _status_message = status_message;
                            _http_version = http_version;
                            

                            //get body

                            std::size_t content_lenght = 0;
                            std::string header_line;
                            std::unordered_map<std::string, std::string> headers;

                            while (getline(response_stream , header_line) && header_line != "\r") {
                                size_t colon_pos = header_line.find(":");

                                if (colon_pos != std::string::npos) {
                                    std::string key = header_line.substr(0,colon_pos);
                                    std::string value = header_line.substr(colon_pos + 2);
                                    headers[key] = value;

                                    if (key == "Content-Length"){
                                        content_lenght = std::stoul(value);
                                    }
                                }
                            }

                            if (content_lenght > 0){
                                std::size_t already_in_buffer = response_buffer->size();

                                if (already_in_buffer >= content_lenght){
                                    std::vector<char> body(content_lenght);
                                    response_stream.read(body.data(), content_lenght);
                                    _http_response_body = body;
                                }else{
                                    std::vector<char> body(content_lenght);
                                    response_stream.read(body.data(), already_in_buffer);
                                    std::size_t remaining = content_lenght - already_in_buffer;

                                    (void) boost::asio::async_read(stream,boost::asio::buffer
                                        (body.data() + already_in_buffer,remaining),[
                                            this,self = shared_from_this() , body = std::move(body),
                                            content_lenght
                                        ](boost::system::error_code ec,std::size_t){
                                            if (ec){
                                                std::cout << "[ERROR] --> " 
                                                << ec.what() << "<-- " 
                                                << std::endl;
                                                return;
                                            }
                                            _http_response_body = body;
                                        });
                                }
                            }else{
                                std::cout << "[WRAING] --> this response is empty" 
                                << "<-- " << std::endl;
                                return;
                            }
                        });
                }
        };
    };
}