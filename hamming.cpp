#include <iostream>
using namespace std;


void sender() {
    int d1, d2, d3, d4;
    int h[8];

    cout << "enter 4 data bits: ";
    cin >> d1 >> d2 >> d3 >> d4;


    h[3] = d1;
    h[5] = d2;
    h[6] = d3;
    h[7] = d4;


    h[1] = h[3] ^ h[5] ^ h[7];
    h[2] = h[3] ^ h[6] ^ h[7];
    h[4] = h[5] ^ h[6] ^ h[7];

    cout << "\\ hamming Code: ";
    for (int i = 1; i <= 7; i++)
        cout << h[i];
    cout << endl;
}


void receiver() {
    int r[8];
    int s1, s2, s4, error;

    cout << "\n enter received 7-bit Hamming code: ";
    for (int i = 1; i <= 7; i++)
        cin >> r[i];

    s1 = r[1] ^ r[3] ^ r[5] ^ r[7];
    s2 = r[2] ^ r[3] ^ r[6] ^ r[7];
    s4 = r[4] ^ r[5] ^ r[6] ^ r[7];

    error = s4 * 4 + s2 * 2 + s1;

    if (error == 0) {
        cout << "nooo error ." << endl;
    } else {
        cout << "error detected at " << error << endl;

   
        r[error] = r[error] ^ 1;

        cout << "corrected Hamming Code: ";
        for (int i = 1; i <= 7; i++)
            cout << r[i];
        cout << endl;
    }
}

int main() {
    sender();
    receiver();
    return 0;
}
