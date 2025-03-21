#pragma once

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

// #define MySelf 0

const std::string black_space_sep = " ";
const std::string protocol_sep = "\n";

std::string Encode(std::string& content)
{
    std::string package = std::to_string(content.size());
    package += protocol_sep;
    package += content;
    package += protocol_sep;

    return package;
}

// "len"\n"x op y"\n
bool Decode(std::string& package, std::string* content) 
{
    std::size_t pos = package.find(protocol_sep);
    if (pos == std::string::npos)
    {
        return false;
    }
    std::string len_str = package.substr(0, pos);
    std::size_t len = std::stoi(len_str);
    // package = len_str + content_str + 2
    std::size_t total_len = len_str.size() + len + 2;
    if (package.size() < total_len)
    {
        return false;
    }

    *content = package.substr(pos + 1, len);
    // erase 移除报文 package.erase(0, total_len);
    package.erase(0, total_len);     

    return true;
}

class Request
{
public:
    Request(int data1, int data2, char oper)
        :x(data1), y(data2), op(oper)
    {

    }

    Request()
    {

    }
public:
    bool Serialize(std::string* out)
    {
#ifdef MySelf        
        // 构建报文的有效载荷
        // struct => string, x op y => "len"\n"x op y"
        std::string s = std::to_string(x);
        s += black_space_sep;
        s += op;
        s += black_space_sep; 
        s += std::to_string(y);
        *out = s;
        return true;
#else
        Json::Value root;
        root["x"] = x;
        root["y"] = y;
        root["op"] = op;
        // Json::FastWriter w;
        Json::StyledWriter w;
        *out = w.write(root);
        return true;
#endif
    }

    bool Deserialize(const std::string& in) // "x op y"
    {
#ifdef MySelf
        std::size_t left = in.find(black_space_sep);

        if (left == std::string::npos)
        {
            return false;
        }

        std::string part_x = in.substr(0, left);

        std::size_t right = in.rfind(black_space_sep);
        if (right == std::string::npos)
        {

            return false;
        }
        std::string part_y = in.substr(right + 1);

        if (left + 2 != right)
        {
            return false;
        }

        op = in[left + 1];
        x = std::stoi(part_x);
        y = std::stoi(part_y);
        return true;
#else
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);
        x = root["x"].asInt();
        y = root["y"].asInt();
        op = root["op"].asInt();
        return true;
#endif
    }

    void DebugPrint()
    {
        std::cout << "新请求构建完成: " << x << op << y << "=?" << std::endl;
    }
public:
    // x op y
    int x;
    int y;
    char op; // + - * / %
};









class Response
{
public:
    Response(int res, int c)
        :result(res), code(c)
    {

    }

    Response()
    {
        
    }
public:
    bool Serialize(std::string* out)
    {
#ifdef MySelf
        // "result code"
        // 构建报头的有效载荷
        std::string s = std::to_string(result);
        s += black_space_sep;
        s += std::to_string(code);
        *out = s;
        return true;
#else
        Json::Value root;
        root["result"] = result;
        root["code"] = code;
        // Json::FastWriter w;
        Json::StyledWriter w;
        *out = w.write(root);
        return true;
#endif
    }

    bool Deserialize(const std::string& in) // "result code"
    {
#ifdef MySelf
        std::size_t pos = in.find(black_space_sep);
        if (pos == std::string::npos)
        {
            return false;
        }
        std::string part_left = in.substr(0, pos);
        std::string part_right = in.substr(pos + 1);

        result = std::stoi(part_left);
        code = std::stoi(part_right);
        return true;
#else
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);
        result = root["result"].asInt();
        code = root["code"].asInt();
        return true;
#endif
    }

    void DebugPrint()
    {
        std::cout << "结果响应完成, result: " << result << ", code: " << code << std::endl;
    }
public:
    int result;
    int code; // 0, 可信, 否则!0具体是几，表明对应的错误原因
};