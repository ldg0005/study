#include <iostream>
using namespace std;
 
class DIV {
private :
    int num, div;
public :
    DIV(int n, int d) {
        num = n;
        div = d;
    }
 
    operator double() const {
        return double(num) / double(div);
    }
};
 
 
int main(void) {
    DIV d(1, 3);
    double db = d;
    cout << d;
 
    return 0;
}
