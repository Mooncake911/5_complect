#include <iostream>
#include <sstream>
#include <string>
#include <array>
using namespace std;

//////////////////////////////////////////////////Task 1////////////////////////////////////////////////////////////////
/* Covert to string operation */
namespace impl
{
    template <class T>
    string to_str(const T &val) { return to_string(val); }
    inline string to_str(const char *p) { return p; }
    inline const string& to_str(const string &s) { return s; }
}

/* Massage function */
template<typename... Args>
void message(std::ostream& out, string model, Args&&... args) {
    string result;
    size_t pos = 0;
    size_t predPos;
    string toReplace = "%";
    // Convert args to list of string.
    string parameters[] { "", impl::to_str(args)... };
    // Reserves rough estimate of final size of string.
    result.reserve(model.size());

    // Change all %
    for (auto &p: parameters) {
        predPos = pos;
        pos = model.find(toReplace, pos);
        result += p;
        if (pos == std::string::npos){  // end of string model
            break;
        }
        result.append(model, predPos, pos - predPos);
        pos += toReplace.size();
    }
    result.append(model, predPos, model.size() - predPos);
    model.swap(result);

    out << model <<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////Task 2////////////////////////////////////////////////////////////////
template<typename T, size_t N>
array < T, N>  cat(array <T, N>& value){
    return value;
}
template<typename T, size_t N, size_t M, typename... Args>
array < T, N+M> cat(array < T, N>& first, array < T, M>& second, Args&&... args){
    array<T, N + M> x = {};
    for (size_t i = 0; i < N + M; i++) {
        if (i < N) {
            x[i] = first[i];
        }
        else {
            x[i] = second[i - N];
        }
    }
    return cat(x, args...);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////Task 3////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    cout << "~ Task 1 ~" << endl;
    message(std::cout,"% + % = %", "a", 2, 3.23, "d");

    cout << "~ Task 2 ~" << endl;
    array<float, 3> vec1{ 1.0f,2.0f,3.0f };
    array<float, 3> vec2{ 4.0f,5.0f,6.0f };
    array<float, 6> vec3 = cat(vec1, vec2);
    for (int i = 0; i < sizeof(vec3)/sizeof(vec3[0]); ++i){
        cout << vec3[i];
    }
    cout << "\n";
    
    return 0;
}
