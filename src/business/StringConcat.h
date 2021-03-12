/**
 * @Created by Manh Vu Duy (manhvdm@gmail.com) on 3/12/2021.
 * @Please contact before using this source code
 */
//

#ifndef BUS_STRINGCONCAT_H
#define BUS_STRINGCONCAT_H

#endif //BUS_STRINGCONCAT_H
#pragma once
template <typename T>
void out(T a, T b) {
    cout << a << " " << b << endl;
}
template <typename T>
void out(T a, T b, T c) {
    cout << a << " " << b << " " << c << endl;
}
template <typename T>
void out(T a, T b, T c, T d) {
    cout << a << " " << b << " " << c << " " << d << endl;
}
template <typename T>
void printArray(T* a, int n) {
    cout << "Print array:" << endl;
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl;
}
template <typename T>
void printArray1N(T* a, int n) {
    cout << "Print array:" << endl;
    for (int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}
template <typename T>
void printArray0N(T* a, int n) {
    cout << "Print array: " << n << endl;
    for (int i = 0; i <= n; i++) cout << a[i] << " ";
    cout << endl;
}
template <typename T>
void printArray2D(T** a, int m, int n) {
    cout << "Print array2D:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}
template <typename T>
void printArray2D1M1N(T** a, int m, int n) {
    cout << "Print array2D:" << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}
template <typename T>
void printArray2D0M0N(T** a, int m, int n) {
    cout << "Print array2D:" << endl;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}
//
template <typename T>
void initArray(T*& a, int n) {
    a = new T[n];
}
template <typename T>
void initArray(T*& a, int n, T default_value) {
    a = new T[n];
    for (int i = 0; i < n; i++) a[i] = default_value;
}
template <typename T>
void initArray2D(T**& a, int m, int n) {
    a = new T * [m];
    for (int i = 0; i < m; i++) {
        a[i] = new T[n];
    }
}
template <typename T>
void initArray2D(T**& a, int m, int n, T default_value) {
    a = new T * [m];
    for (int i = 0; i < m; i++) {
        a[i] = new T[n];
        for (int j = 0; j < n; j++) a[i][j] = default_value;
    }
}
template <typename T>
void deleteArray2D(T**& a, int m, int n) {
    for (int i = 0; i < m; i++) {
        delete a[i];
    }
    delete a;
}
//
template <typename T>
int appearanceTime(T* a, int start, int end, T value) {
    int count = 0;
    for (int i = start; i <= end; i++) if (a[i] == value) count++;
    return count;
}
//
template <typename T>
bool checkPermutationVRP(T* a, int n) {
    for (int i = 0; i < n; i++) if(a[i] != 0){
            for (int j = i + 1; j <= n; j++) if (a[i] == a[j]) return false;
        }
    return true;
}
bool checkSwapSubArray(int start_1, int end_1, int start_2, int end_2) {
    if (start_1 == start_2) return false;
    if (start_1 > end_1 && start_2 > end_2) return false;
    if (start_1 > start_2) {
        swap(start_1, start_2);
        swap(end_1, end_2);
    }
    if (start_2 <= end_1 || end_1 == end_2 || end_1 + 1 == start_2 || end_1 + 1 == end_2) return false;
    return true;
}
int* string_concat_next;
int* string_concat_cache;
int string_concat_pointer;
template <typename T>
void swapSubArray(T* a, int n, int start_1, int end_1, int start_2, int end_2) {
    if (end_1 - start_1 == end_2 - start_2) {
        for (int i = end_1 - start_1; i >= 0; i--) {
            swap(a[start_1 + i], a[start_2 + i]);
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        string_concat_next[i] = i + 1;
        string_concat_cache[i] = a[i];
    }
    if (start_2 > end_2) {
        swap(start_1, start_2);
        swap(end_1, end_2);
    }
    string_concat_next[start_1 - 1] = start_2;
    string_concat_next[end_2] = end_1 + 1;
    if (start_1 > end_1) {
        string_concat_next[start_2 - 1] = end_2 + 1;
    }
    else {
        string_concat_next[start_2 - 1] = start_1;
        string_concat_next[end_1] = end_2 + 1;
    }
    string_concat_pointer = string_concat_next[0];
    for (int i = 1; i < n; i++) {
        a[i] = string_concat_cache[string_concat_pointer];
        string_concat_pointer = string_concat_next[string_concat_pointer];
    }
}
template <typename T>
void insertBefore(T& a, int& n, int index, int value) {
    for (int i = n++; i > index; i--) a[i] = a[i - 1];
    a[index] = value;
}
template <typename T>
void insertAfter(T& a, int& n, int index, int value) {
    for (int i = n++; i > index + 1; i--) a[i] = a[i - 1];
    a[index + 1] = value;
}
