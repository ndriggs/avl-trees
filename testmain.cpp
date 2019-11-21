#include "AVL.h"

using namespace std;

int main(int argc, char *argv[]){
    int a, b, c, d, e, f, g;
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    d = atoi(argv[4]);
    e = atoi(argv[5]);
    f = atoi(argv[6]);
    g = atoi(argv[7]);
    
    AVL set;
    cout << "adding " << a << endl;
    set.add(a);
    cout << "adding " << b << endl;
    set.add(b);
    cout << "adding " << c << endl;
    set.add(c);
    cout << "adding " << d << endl;
    set.add(d);
    cout << "adding " << e << endl;
    set.add(e);
    cout << "adding " << f << endl;
    set.add(f);
    cout << "adding " << g << endl;
    set.add(g);
    
    
    return 0;
}