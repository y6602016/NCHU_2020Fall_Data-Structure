#include "Tree.h"
#include "Tree2.h"
#include "Tree3.h"
#include <iostream>
using namespace std;


int main() {
    // Tree<int> t(5);
    // t.Postorder();

    // Tree2 a('A');
    // a.Postorder();

    Tree3<int> b(5);
    b.inOrder();
    cout << endl;
    TreeNode3<int> x(1);
    b.InsertRight(b.getNode(), &x);
    b.inOrder();
}