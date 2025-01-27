// デュアルモニター設定を変更する
// 2023/09/14 mutoxu=N

// 実行時にコマンドライン引数を渡すことで動作を設定できる
// change_display_mode.exe <mode>
// <mode>
// 0: PC画面のみ
// 1: 拡張
// 2: セカンドスクリーンのみ

#include <windows.h>
#include <winuser.h>

#include <iostream>

using namespace std;

bool isNumber(string &str) {
    auto it = str.begin();
    while (it != str.end() && isdigit(*it)) it++;
    return !str.empty() && it == str.end();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: change_display_mode.exe <mode>" << endl;
        cerr << "\t0: Internal Only" << endl;
        cerr << "\t1: Extend" << endl;
        cerr << "\t2: External Only" << endl;
        return 1;
    }

    // option
    string opt_mode_str = argv[1];
    if (!isNumber(opt_mode_str)) {
        cerr << "Option #1 must be number.";
        return 2;
    }

    int opt_mode = stoi(opt_mode_str);
    if ((opt_mode < 0 || 2 < opt_mode)) {
        cerr << "Option #1 must be between 0 and 2." << endl;
        return 3;
    }

    switch (opt_mode) {
        case 0:
            cout << "Changing display mode to \"internal\"" << endl;
            SetDisplayConfig(0, NULL, 0, NULL,
                             SDC_TOPOLOGY_INTERNAL | SDC_APPLY);
            break;

        case 1:
            cout << "Changing display mode to \"extend\"" << endl;
            SetDisplayConfig(0, NULL, 0, NULL, SDC_TOPOLOGY_EXTEND | SDC_APPLY);
            break;

        case 2:
            cout << "Changing display mode to \"external\"" << endl;
            SetDisplayConfig(0, NULL, 0, NULL,
                             SDC_TOPOLOGY_EXTERNAL | SDC_APPLY);
            break;
    }

    return 0;
}
