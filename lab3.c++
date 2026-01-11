#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
    // 1.
    list<int> myList = {1, 2, 3, 4, 5};

    // a)
    for (list<int>::iterator it = myList.begin(); it != myList.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // b)
    for (list<int>::reverse_iterator rit = myList.rbegin(); rit != myList.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << endl;

    // c)
    if (!myList.empty()) {
        cout << *myList.rbegin() << endl;
    }

    // 2.
    // a)
    fill_n(back_inserter(myList), 3, 99);

    // b)
    fill_n(front_inserter(myList), 3, 11);

    // c)
    list<int>::iterator itMid = myList.begin();
    advance(itMid, myList.size() / 2);
    fill_n(inserter(myList, itMid), 3, 55);

    // (Display list after 2)
    copy(myList.begin(), myList.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // 3.
    // a)
    const string filename = "file.txt";
    {
        ofstream outFile(filename);
        outFile << "one two three four five";
    }

    // b)
    vector<string> myVector;

    // c)
    ifstream inFile(filename);
    if (inFile.is_open()) {
        istream_iterator<string> in_start(inFile), in_end;
        copy(in_start, in_end, back_inserter(myVector));
        inFile.close();
    }

    // d)
    ostream_iterator<string> out_it(cout, " ");
    copy(myVector.begin(), myVector.end(), out_it);
    cout << endl;

    // e)
    vector<string> newVals = {"INSERT_A", "INSERT_B"};
    vector<string>::iterator vecMid = myVector.begin() + (myVector.size() / 2);
    myVector.insert(vecMid, newVals.begin(), newVals.end());

    // f)
    copy(myVector.begin(), myVector.end(), out_it);
    cout << endl;

    // g)
    ofstream outFileSave(filename);
    if (outFileSave.is_open()) {
        ostream_iterator<string> file_out(outFileSave, "\n");
        copy(myVector.begin(), myVector.end(), file_out);
        outFileSave.close();
    }

    return 0;
}
