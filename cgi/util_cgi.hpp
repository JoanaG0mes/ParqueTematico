#ifndef UTIL_CGI_HPP
#define UTIL_CGI_HPP

#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;

string url_decode(const string &SRC) {
    string ret;
    char ch;
    int i, ii;
    for (i = 0; i < (int)SRC.length(); i++) {
        if (SRC[i] == '+') ret += ' ';
        else if (SRC[i] == '%') {
            sscanf(SRC.substr(i+1, 2).c_str(), "%x", &ii);
            ch = static_cast<char>(ii);
            ret += ch;
            i += 2;
        } else ret += SRC[i];
    }
    return ret;
}

string readRequestBody() {
    string body;
    const char* lenStr = getenv("CONTENT_LENGTH");
    if (!lenStr) return body;
    int len = atoi(lenStr);
    body.resize(len);
    cin.read(&body[0], len);
    return body;
}

map<string,string> parseForm(const string& body) {
    map<string,string> data;
    size_t pos = 0;
    while (pos < body.size()) {
        size_t eq = body.find('=', pos);
        if (eq == string::npos) break;
        string key = body.substr(pos, eq - pos);
        size_t amp = body.find('&', eq + 1);
        string val = (amp == string::npos)
            ? body.substr(eq + 1)
            : body.substr(eq + 1, amp - eq - 1);
        data[key] = url_decode(val);
        if (amp == string::npos) break;
        pos = amp + 1;
    }
    return data;
}

#endif
