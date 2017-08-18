#include <gobcode/unicode.hpp>

using namespace std;

namespace unicode {
    bool is_unicode_char(char c){
        return (c & 0xC0) == 0x80;
    }

    int unicode_size(string unicode_string){
        int len = 0;
        const char* s = unicode_string.c_str();
        while(*s){
            len++;
            s++;
            if (is_unicode_char(*s)){
                len++;
                while(is_unicode_char(*s)){
                    s++;
                }
            }
        }
        return len;
    }
}
