#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"

using namespace std;

int main()
{  
    DSString myString = "Hello, World!";
    cout << myString << endl;

    // this uses the one argument constructor in DSString and then the inherited operator=
    myString = "Good bye!";
    cout << myString << endl;

    cout << "substr: " << myString.substring(5, 3) << endl;

    DSString a = "test";
    DSString b = a;

    cout << boolalpha;
    cout << (a == b) << endl;

    // use initialization list (see DSVector.h)
    vector<DSString> strings = {DSString("bbb"), DSString("aaa"), DSString("ddd"), DSString("eee"), DSString("ccc")};

    // find strings
    for (const auto &s : strings)
        cout << s << "\n";

    cout << "found ddd: " << (find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << endl;
    cout << "found zzz: " << (find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << endl;

    // sorting
    sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        cout << s << "\n";

    // now we can do more efficient search
    cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << endl;
    cout << "found zzz: " << binary_search(strings.begin(), strings.end(), DSString("zzz")) << endl;
    return 0;
}
