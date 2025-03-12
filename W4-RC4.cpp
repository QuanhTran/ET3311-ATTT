#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class RC4 {
private:
    vector<int> S;
    int i, j;

    void keyScheduling(const string& key) {
        S.resize(256);
        for (int i = 0; i < 256; i++) {
            S[i] = i;
        }
        
        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + S[i] + key[i % key.length()]) % 256;
            swap(S[i], S[j]);
        }
        
        this->i = 0;
        this->j = 0;
    }

public:
    RC4(const string& key) {
        keyScheduling(key);
    }

    int keyStreamByte() {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }
    
    string encryptDecrypt(const string& input, vector<int>& keyStream) {
        string output;
        keyStream.clear();
        for (char c : input) {
            int k = keyStreamByte();
            keyStream.push_back(k);
            output += static_cast<char>(c ^ k);
        }
        return output;
    }
};

void printHex(const vector<int>& data) {
    for (int val : data) {
        cout << hex << setw(2) << setfill('0') << val << " ";
    }
    cout << dec << endl;
}

int main() {
    string key = "mysecretkey";
    string plaintext = "Hanoi University of Science and Technology";
    
    RC4 rc4(key);
    vector<int> keyStream;
    string ciphertext = rc4.encryptDecrypt(plaintext, keyStream);
    
    cout << "Keystream: ";
    printHex(keyStream);
    
    cout << "Ciphertext (hex): ";
    printHex(vector<int>(ciphertext.begin(), ciphertext.end()));
    
    return 0;
}
