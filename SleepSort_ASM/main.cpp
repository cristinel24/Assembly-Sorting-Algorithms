#include <iostream>
#include <windows.h>
#include <process.h>
using namespace std;

void routine(void*);
void sleepSort(int [], int);
HANDLE beginThread(int);

int main()
{
    int v[] = { 3,5,12 };
    int v_size = sizeof(v) / sizeof(v[0]);
    
    void (*func)(void*);
    func = routine;


    _asm {
        mov edi, v_size
        lea eax, v
        lea ebx, func

        push ebx
        push edi
        push eax
        call sleepSort
        add esp, 12
    }

    return 0;
}

void routine(void* a) {
    int n = *(int*) a;
    const char output_type[] = "%d ";
    
    /*_asm {
        mov eax, n
        push eax
        call Sleep
        pop eax

        lea ecx, output_type
        push eax
        push ecx
        call printf
        add esp, 8
    }*/

    Sleep(n);

    cout << n << ;''
}

void sleepSort(int a[], int n) {
    HANDLE* threads = new HANDLE[n];
    /*_asm {
        xor esi, esi
        mov ebx, threads
        mov edi, [ebp + 8]
        

        _start_for:
            cmp esi, [ebp + 12]
            jge _end_for
            
            xor edx, edx
            push [edi + 4 * esi]
            call beginThread
            add esp, 4
            mov [ebx + 4 * esi], eax
            
            inc esi
            jmp _start_for

        _end_for:

            mov esi, 0xFFFFFFFF
            mov edi, 1
            
            push esi
            push edi
            push ebx
            push [ebp + 12]
            call WaitForMultipleObjects
            add esp, 16
    }*/
    for (int i = 0; i < n; i++)
        threads[i] = (HANDLE)_beginthread(&routine, 0, &a[i]);
    WaitForMultipleObjects(n,threads, TRUE, INFINITE);
}
HANDLE beginThread(int b) {
    return (HANDLE)_beginthread(&routine, 0, &b);
}