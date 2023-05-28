/*
LIST
*/

#include "Mylib.h"
#include "funkcijos.h"

int main()
{
//     auto start = std::chrono::high_resolution_clock::now(); // paleisti

    list<Studentas> studentai;
    duomenu_nuskaitymas_list(studentai);

//     auto end = std::chrono::high_resolution_clock::now(); // stabdyti
//     std::chrono::duration<double> skirt = end - start;    // skirtumas (s)
//     cout << "Programos veiklos sparta: " << fixed << setprecision(2) << skirt.count() << "s" << endl;
    return 0;
}
