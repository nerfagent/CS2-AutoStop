#include <iostream>
#include <windows.h>

void pressKeys(bool Wkey, bool Akey, bool Skey, bool Dkey) {
    // Press W, A, S, D
    if (Skey)
        keybd_event(0x57, 0, 0, 0); // W key down
    if (Dkey)
        keybd_event(0x41, 0, 0, 0); // A key down
    if (Wkey)
        keybd_event(0x53, 0, 0, 0); // S key down
    if (Akey)
        keybd_event(0x44, 0, 0, 0); // D key down
}

void autoRelease() {
    // Release W, A, S, D
    keybd_event(0x57, 0, KEYEVENTF_KEYUP, 0); // W key up
    keybd_event(0x41, 0, KEYEVENTF_KEYUP, 0); // A key up
    keybd_event(0x53, 0, KEYEVENTF_KEYUP, 0); // S key up
    keybd_event(0x44, 0, KEYEVENTF_KEYUP, 0); // D key up
}

void mainBrake(int button) {
    std::cout << "Press Space key to trigger W, A, S, D keys..." << std::endl;

    while (true) {
        bool temp = false;

        bool Wkey = (GetAsyncKeyState(0x57) & 0x8000);
        bool Akey = (GetAsyncKeyState(0x41) & 0x8000);
        bool Skey = (GetAsyncKeyState(0x53) & 0x8000);
        bool Dkey = (GetAsyncKeyState(0x44) & 0x8000);

        // Check if Space key is pressed VK_SPACE
        if (GetAsyncKeyState(button) & 0x8000) {
            std::cout << "Brake!" << std::endl;
            pressKeys(Wkey, Akey, Skey, Dkey);
            temp = true;
            Sleep(10);
            std::cout << "Release!" << std::endl;
            autoRelease();
        }
        while (GetAsyncKeyState(button) & 0x8000) {
            Sleep(10);
        }
        Sleep(10); // Small delay to avoid high CPU usage
    }
}

int main() {
    int button = VK_SPACE; // Trigger button
    mainBrake(button);

    return 0;
}