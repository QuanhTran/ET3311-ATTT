#include <bits/stdc++.h>
using namespace std;
#define SIZE 100

// Chuyển đổi tất cả ký tự trong chuỗi về chữ thường
void toLowerCase(char plain[], int ps) {
    for (int i = 0; i < ps; i++) {
        if (plain[i] >= 'A' && plain[i] <= 'Z')
            plain[i] += 32;
    }
}

// Hàm loại bỏ tất cả dấu cách trong chuỗi
int removeSpaces(char* plain, int ps) {
    int count = 0;
    for (int i = 0; i < ps; i++) {
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    }
    plain[count] = '\0';
    return count;
}

// Hàm tạo bảng khóa 5x5
void generateKeyTable(char key[], int ks, char keyT[5][5]) {
    int dicty[26] = { 0 };
    for (int i = 0; i < ks; i++) {
        if (key[i] == 'j') key[i] = 'i'; // Gộp 'i' và 'j'
        if (dicty[key[i] - 'a'] == 0) {
            dicty[key[i] - 'a'] = 1;
        }
    }

    int i = 0, j = 0;
    for (int k = 0; k < ks; k++) {
        if (dicty[key[k] - 'a'] == 1) {
            keyT[i][j++] = key[k];
            dicty[key[k] - 'a'] = 2;
            if (j == 5) { i++; j = 0; }
        }
    }
    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0 && k != ('j' - 'a')) {
            keyT[i][j++] = (char)(k + 'a');
            if (j == 5) { i++; j = 0; }
        }
    }
}

// Tìm vị trí của hai ký tự trong ma trận khóa
void search(char keyT[5][5], char a, char b, int arr[]) {
    if (a == 'j') a = 'i';
    if (b == 'j') b = 'i';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i; arr[1] = j;
            }
            if (keyT[i][j] == b) {
                arr[2] = i; arr[3] = j;
            }
        }
    }
}

// Xử lý chuỗi để không có cặp trùng và có độ dài chẵn
int prepareText(char str[], int ptrs) {
    char temp[SIZE];
    int newLen = 0;
    for (int i = 0; i < ptrs; i++) {
        temp[newLen++] = str[i];
        if (i < ptrs - 1 && str[i] == str[i + 1]) {
            temp[newLen++] = 'x'; // Chèn 'X' giữa hai ký tự trùng
        }
    }
    if (newLen % 2 != 0) {
        temp[newLen++] = 'x'; // Thêm 'X' nếu độ dài lẻ
    }
    temp[newLen] = '\0';
    strcpy(str, temp);
    return newLen;
}

// Hàm tính toán phép chia lấy dư với 5
int mod5(int a) { return (a % 5); }

// Mã hóa văn bản Playfair
void encrypt(char str[], char keyT[5][5], int ps) {
    int a[4];
    for (int i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

// Hàm tiền xử lý và mã hóa văn bản 
void encryptByPlayfairCipher(char str[], char key[]) {
    char keyT[5][5];
    int ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    int ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);
    ps = prepareText(str, ps);

    generateKeyTable(key, ks, keyT);
    
    // Hiển thị ma trận khóa 5x5
    cout << "Ma trận khóa 5x5:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << keyT[i][j] << " ";
        }
        cout << endl;
    }
    
    encrypt(str, keyT, ps);
}

int main() {
    char str[SIZE], key[SIZE];

    cout << "Nhập khóa: ";
    cin.getline(key, SIZE);
    
    cout << "Nhập văn bản gốc: ";
    cin.getline(str, SIZE);

    encryptByPlayfairCipher(str, key);

    cout << "Văn bản mã hóa: " << str << endl;

    return 0;
}
