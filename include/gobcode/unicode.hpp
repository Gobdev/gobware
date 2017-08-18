#ifndef gobcode_unicode
#define gobcode_unicode
#include <string>

using namespace std;

namespace unicode {
    bool is_unicode_char(char c);
    int unicode_size(string unicode_string);
}
#endif
