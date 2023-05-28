/*
VECTOR
*/

#include "funkcijos.h"

// sugeneruoja atsitiktini studento varda ir pavarde
string generate_name(int i)
{
    return "Vardas" + to_string(i);
}
string generate_surname(int i)
{
    return " Pavarde" + to_string(i);
}

// sugeneruoja atsitiktini studento pažymi (nuo 0 iki 10)
int generate_grade()
{
    return rand() % 11;
}

// funkcija, skirta vidurkio arba medianos pasirinkimo nuskaitymui
string read_average_type()
{
    string vidurkis_mediana;

    cout << "Norite, kad galutiniame rezultate butu pateiktas rezultatu vidurkis ar mediana?" << endl
         << "(irasykite 'med' - medianai, 'vid' - vidurkiui): ";

    // nuskaitome vartotojo pasirinkima, kol jis ives tinkama reiksme
    while (vidurkis_mediana != "med" && vidurkis_mediana != "vid")
        cin >> vidurkis_mediana;

    return vidurkis_mediana;
}

bool compare(Studentas a, Studentas b)
{
    return (a.rezultatas < b.rezultatas);
}

// funkcija, apskaiciuojanti mediana arba vidurki
void med_vid(int n, int nd, vector<Studentas> &studentai, string &vidurkis_mediana, vector<Studentas> &neislaike, vector<Studentas> &islaike)
{
    double vid = 0;
    if (vidurkis_mediana == "vid")
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < nd; j++)
                vid += studentai[i].pazymiai[j];
            studentai[i].rezultatas = 0.4 * (vid / nd) + 0.6 * studentai[i].egz;

            if (studentai[i].rezultatas < 5)
                neislaike.push_back(studentai[i]);
            else
                islaike.push_back(studentai[i]);

            vid = 0;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int pazymiu_skaicius = nd;
            // isrikiuojama nuo maziausio iki didziausio
            sort(studentai[i].pazymiai.begin(), studentai[i].pazymiai.end());

            if (pazymiu_skaicius % 2 == 0)
                vid = (studentai[i].pazymiai[pazymiu_skaicius / 2 - 1] + studentai[i].pazymiai[pazymiu_skaicius / 2]) / 2;
            else
                vid = studentai[i].pazymiai[pazymiu_skaicius / 2];

            studentai[i].rezultatas = 0.4 * (vid / nd) + 0.6 * studentai[i].egz;

            if (studentai[i].rezultatas < 5)
                neislaike.push_back(studentai[i]);
            else
                islaike.push_back(studentai[i]);

            vid = 0;
        }
    }
    // surikiuojami studentai pagal rezultata
    sort(neislaike.begin(), neislaike.end(), compare);
    sort(islaike.begin(), islaike.end(), compare);
}

void duomenu_nuskaitymas(vector<Studentas> &studentai)
{
    srand(time(NULL));
    Studentas studentas;
    vector<Studentas> neislaike;
    vector<Studentas> islaike;
    string failu_pav[4] = {"", "", "", ""};

    // studentu skaicius skirtas failams
    int num_students[] = {1000, 10000, 100000, 1000000};

    string atsakymas;
    cout << "Ar norite pasirinkti failus darbui is jau egzistuojanciu? (taip/ne): ";
    cin >> atsakymas;

    if (atsakymas == "taip" || atsakymas == "Taip") {
        string failas;
        bool failasRastas = false;

        cout << "Failu sarasas: ";
            system("dir *.txt");

        cout << "Pasirinkite faila: ";
            cin >> failas;

        ifstream skait(failas);

        while (!failasRastas) {
            if (skait.is_open()) {
                failasRastas = true;
            } else {
                cout << "Klaida, tokio failo [" << failas << "] nera." << endl;
                cin >> failas;
            }
        }

        string vidurkis_mediana = read_average_type();

        string pirmoji_eilute;
        // praignoruojama pirmoji eilute
        getline(skait, pirmoji_eilute);

        string eilute;

        auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
        while (getline(skait, eilute)) {
            istringstream iss(eilute);
            Studentas studentas;

            iss >> studentas.vardas >> studentas.pavarde;

            int pazymys;
            while (iss >> pazymys) {
                studentas.pazymiai.push_back(pazymys);
            }

            if (!studentas.pazymiai.empty()) {
                studentas.egz = studentas.pazymiai.back();
                studentas.pazymiai.pop_back();
            }

            studentai.push_back(studentas);
        }

        auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
        cout << "Duomenu is failo " << failas << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

        int studentu_sk = studentai.size();
        int nd_sk = studentai[0].pazymiai.size();

        auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

        med_vid(studentu_sk, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
        studentai.clear();

        auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
        cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

        string filename1 = "islaike" + to_string(studentu_sk) + ".txt";
        string filename2 = "neislaike" + to_string(studentu_sk) + ".txt";

        ofstream fr(filename1);
        ofstream fr1(filename2);

        auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
        // rasomi studentu duomenys i faila
        fr << left << setw(18) << "Vardas"
        << left << setw(18) << "Pavarde";
        if (vidurkis_mediana == "vid")
            fr << left << setw(15) << "Galutinis (Vid.)" << endl;
        else
            fr << left << setw(15) << "Galutinis (Med.)" << endl;

        fr << "----------------------------------------------------" << endl;
        for (int j = 0; j < islaike.size(); j++)
        {
            fr << left << setw(18) << islaike[j].vardas;
            fr << left << setw(18) << islaike[j].pavarde;

            // rasomas galutinis pazymys i faila
            double average_grade = islaike[j].rezultatas;
            fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
        }

        auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
        cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

        auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
        // rasomi studentu duomenys i faila
        fr1 << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
        if (vidurkis_mediana == "vid")
            fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
        else
            fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

        fr1 << "----------------------------------------------------" << endl;
        for (int j = 0; j < neislaike.size(); j++)
        {
            fr1 << left << setw(18) << neislaike[j].vardas;
            fr1 << left << setw(18) << neislaike[j].pavarde;

            // rasome galutini pazymi i faila
            double average_grade = neislaike[j].rezultatas;
            fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
        }
        auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
        std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
        cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
        cout << endl;
        fr.close();
        fr1.close();
        skait.close();
    }

    else{

        int nd_sk;
        cout << "Iveskite skaiciu, kiek kiekvienas studentas tures pazymiu (nuo 1 iki 15 iskaitytinai): ";
        while (true)
        {
            cin >> nd_sk;

            if (cin.fail() || nd_sk < 1 || nd_sk > 15)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "klaida, skaicius turi buti nuo 1 iki 15\n";
            }

            else
                break;
        }

        string vidurkis_mediana = read_average_type();

        for (int i = 0; i < 4; i++)
        {
            int n = num_students[i];
            string filename = "studentai" + to_string(n) + ".txt";
            failu_pav[i] = filename;
            
            auto start = std::chrono::high_resolution_clock::now(); // paleisti

            ofstream outfile(filename);

            // pirmoji eilute
            outfile << left << setw(19) << "Vardas";
            outfile << left << setw(17) << "Pavarde";
            for (int j = 0; j < nd_sk; j++)
            {
                string nd = "ND" + to_string(j + 1);
                outfile << left << setw(5) << nd;
            }
            outfile << left << setw(5) << "Egz." << endl;

            for (int j = 1; j <= n; j++)
            {
                string vardas = generate_name(j);
                string pavarde = generate_surname(j);
                outfile << left << setw(18) << vardas;
                outfile << left << setw(18) << pavarde;

                // atsitiktiniai pazymiai
                for (int k = 0; k < nd_sk; k++)
                {
                    int grade = generate_grade();
                    outfile << left << setw(5) << grade;
                }

                // egzamino pazymys
                int exam_grade = generate_grade();
                outfile << left << setw(5) << exam_grade << endl;
            }
            outfile.close();
            auto end = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt = end - start;    // skirtumas (s)
            cout << "Failo " << filename << " kurimo sparta: " << fixed << setprecision(2) << skirt.count() << "s" << endl;

            auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
            ifstream fd(failu_pav[i]);

            string pirmoji_eilute;
            // praignoruojama pirmoji eilute
            getline(fd, pirmoji_eilute);

            for (int j = 1; j <= n; j++)
            {
                studentas.pazymiai.clear();

                fd >> studentas.vardas >> studentas.pavarde;

                int pazymys;
                for (int k = 0; k < nd_sk; k++)
                {
                    fd >> pazymys;
                    studentas.pazymiai.push_back(pazymys);
                }
                fd >> studentas.egz;

                studentai.push_back(studentas);
            }

            auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
            cout << "Duomenu is failo " << failu_pav[i] << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

            int studentu_sk = studentai.size();

            auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

            med_vid(studentu_sk, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
            studentai.clear();

            auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
            cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

            string filename1 = "islaike" + to_string(n) + ".txt";
            string filename2 = "neislaike" + to_string(n) + ".txt";

            ofstream fr(filename1);
            ofstream fr1(filename2);

            auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
            // rasomi studentu duomenys i faila
            fr << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr << left << setw(15) << "Galutinis (Med.)" << endl;

            fr << "----------------------------------------------------" << endl;
            for (int j = 0; j < islaike.size(); j++)
            {
                fr << left << setw(18) << islaike[j].vardas;
                fr << left << setw(18) << islaike[j].pavarde;

                // rasomas galutinis pazymys i faila
                double average_grade = islaike[j].rezultatas;
                fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }

            auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
            cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

            auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
            // rasomi studentu duomenys i faila
            fr1 << left << setw(18) << "Vardas"
                << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

            fr1 << "----------------------------------------------------" << endl;
            for (int j = 0; j < neislaike.size(); j++)
            {
                fr1 << left << setw(18) << neislaike[j].vardas;
                fr1 << left << setw(18) << neislaike[j].pavarde;

                // rasome galutini pazymi i faila
                double average_grade = neislaike[j].rezultatas;
                fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }
            auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
            std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
            cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
            cout << endl;
            fd.close();
            fr.close();
            fr1.close();
        }
    }
}

/*
LIST --------------------------------------------------------------------
*/

void med_vid_list(int n, int nd, list<Studentas> &studentai, string &vidurkis_mediana, list<Studentas> &neislaike, list<Studentas> &islaike)
{
    double vid = 0;
    if (vidurkis_mediana == "vid")
    {
        for (auto &s : studentai)
        {
            for (auto &p : s.pazymiai)
                vid += p;
            s.rezultatas = 0.4 * (vid / nd) + 0.6 * s.egz;

            if (s.rezultatas < 5)
                neislaike.push_back(s);
            else
                islaike.push_back(s);

            vid = 0;
        }
    }
    else
    {
        for (auto &s : studentai)
        {
            int pazymiu_skaicius = nd;
            // isrikiuojama nuo maziausio iki didziausio
            // s.pazymiai.sort();

            if (pazymiu_skaicius % 2 == 0)
                vid = (s.pazymiai[pazymiu_skaicius / 2 - 1] + s.pazymiai[pazymiu_skaicius / 2]) / 2;
            else
                vid = s.pazymiai[pazymiu_skaicius / 2];

            s.rezultatas = 0.4 * (vid / nd) + 0.6 * s.egz;

            if (s.rezultatas < 5)
                neislaike.push_back(s);
            else
                islaike.push_back(s);

            vid = 0;
        }
    }
    // surikiuojami studentai pagal rezultata
    neislaike.sort(compare);
    islaike.sort(compare);
}

void duomenu_nuskaitymas_list(list<Studentas> &studentai)
{
    srand(time(NULL));
    Studentas studentas;
    list<Studentas> neislaike;
    list<Studentas> islaike;
    string failu_pav[4] = {"", "", "", ""};

    // studentu skaicius skirtas failams
    int num_students[] = {1000, 10000, 100000, 1000000};

    string atsakymas;
    cout << "Ar norite pasirinkti failus darbui is jau egzistuojanciu? (taip/ne): ";
    cin >> atsakymas;

    if (atsakymas == "taip" || atsakymas == "Taip") {
        string failas;
        bool failasRastas = false;

        cout << "Failu sarasas: ";
            system("dir *.txt");

        cout << "Pasirinkite faila: ";
            cin >> failas;

        ifstream skait(failas);

        while (!failasRastas) {
            if (skait.is_open()) {
                failasRastas = true;
            } else {
                cout << "Klaida, tokio failo [" << failas << "] nera." << endl;
                cin >> failas;
            }
        }

        string vidurkis_mediana = read_average_type();

        string pirmoji_eilute;
        // praignoruojama pirmoji eilute
        getline(skait, pirmoji_eilute);

        string eilute;

        auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
        while (getline(skait, eilute)) {
            istringstream iss(eilute);
            Studentas studentas;

            iss >> studentas.vardas >> studentas.pavarde;

            int pazymys;
            while (iss >> pazymys) {
                studentas.pazymiai.push_back(pazymys);
            }

            if (!studentas.pazymiai.empty()) {
                studentas.egz = studentas.pazymiai.back();
                studentas.pazymiai.pop_back();
            }

            studentai.push_back(studentas);
        }

        auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
        cout << "Duomenu is failo " << failas << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

        int studentu_sk = studentai.size();
        int nd_sk = 0;
        if (!studentai.empty()) {
            nd_sk = studentai.begin()->pazymiai.size();
        }
        auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

        med_vid_list(studentu_sk, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
        studentai.clear();

        auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
        cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

        string filename1 = "islaike" + to_string(studentu_sk) + ".txt";
        string filename2 = "neislaike" + to_string(studentu_sk) + ".txt";

        ofstream fr(filename1);
        ofstream fr1(filename2);

        auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
            // rasomi studentu duomenys i faila
            fr << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr << left << setw(15) << "Galutinis (Med.)" << endl;

            fr << "----------------------------------------------------" << endl;
            for (auto &i : islaike)
            {
                fr << left << setw(18) << i.vardas;
                fr << left << setw(18) << i.pavarde;

                // rasomas galutinis pazymys i faila
                double average_grade = i.rezultatas;
                fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }

            auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
            cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

            auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
            // rasomi studentu duomenys i faila
            fr1 << left << setw(18) << "Vardas"
                << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

            fr1 << "----------------------------------------------------" << endl;
            for (auto &n : neislaike)
            {
                fr1 << left << setw(18) << n.vardas;
                fr1 << left << setw(18) << n.pavarde;

                // rasome galutini pazymi i faila
                double average_grade = n.rezultatas;
                fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }
            auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
            std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
            cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
            cout << endl;
        fr.close();
        fr1.close();
        skait.close();
    }

    else{
        int nd_sk;
        cout << "Iveskite skaiciu, kiek kiekvienas studentas tures pazymiu (nuo 1 iki 15 iskaitytinai): ";
        while (true)
        {
            cin >> nd_sk;

            if (cin.fail() || nd_sk < 1 || nd_sk > 15)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "klaida, skaicius turi buti nuo 1 iki 15\n";
            }

            else
                break;
        }

        string vidurkis_mediana = read_average_type();

        for (int i = 0; i < 4; i++)
        {
            int n = num_students[i];
            string filename = "studentai" + to_string(n) + ".txt";
            failu_pav[i] = filename;

            auto start = std::chrono::high_resolution_clock::now(); // paleisti

            ofstream outfile(filename);

            // pirmoji eilute
            outfile << left << setw(19) << "Vardas";
            outfile << left << setw(17) << "Pavarde";
            for (int j = 0; j < nd_sk; j++)
            {
                string nd = "ND" + to_string(j + 1);
                outfile << left << setw(5) << nd;
            }
            outfile << left << setw(5) << "Egz." << endl;

            for (int j = 1; j <= n; j++)
            {
                string vardas = generate_name(j);
                string pavarde = generate_surname(j);
                outfile << left << setw(18) << vardas;
                outfile << left << setw(18) << pavarde;

                // atsitiktiniai pazymiai
                for (int k = 0; k < nd_sk; k++)
                {
                    int grade = generate_grade();
                    outfile << left << setw(5) << grade;
                }

                // egzamino pazymys
                int exam_grade = generate_grade();
                outfile << left << setw(5) << exam_grade << endl;
            }
            outfile.close();
            auto end = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt = end - start;    // skirtumas (s)
            cout << "Failo " << filename << " kurimo sparta: " << fixed << setprecision(2) << skirt.count() << "s" << endl;

            auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
            ifstream fd(failu_pav[i]);

            string pirmoji_eilute;
            // praignoruojama pirmoji eilute
            getline(fd, pirmoji_eilute);

            for (int j = 1; j <= n; j++)
            {
                studentas.pazymiai.clear();

                fd >> studentas.vardas >> studentas.pavarde;

                int pazymys;
                for (int k = 0; k < nd_sk; k++)
                {
                    fd >> pazymys;
                    studentas.pazymiai.push_back(pazymys);
                }
                fd >> studentas.egz;

                studentai.push_back(studentas);
            }

            auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
            cout << "Duomenu is failo " << failu_pav[i] << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

            int studentu_sk = studentai.size();

            auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

            med_vid_list(n, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
            studentai.clear();

            auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
            cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

            string filename1 = "islaike" + to_string(n) + ".txt";
            string filename2 = "neislaike" + to_string(n) + ".txt";

            ofstream fr(filename1);
            ofstream fr1(filename2);

            auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
            // rasomi studentu duomenys i faila
            fr << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr << left << setw(15) << "Galutinis (Med.)" << endl;

            fr << "----------------------------------------------------" << endl;
            for (auto &i : islaike)
            {
                fr << left << setw(18) << i.vardas;
                fr << left << setw(18) << i.pavarde;

                // rasomas galutinis pazymys i faila
                double average_grade = i.rezultatas;
                fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }

            auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
            cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

            auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
            // rasomi studentu duomenys i faila
            fr1 << left << setw(18) << "Vardas"
                << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

            fr1 << "----------------------------------------------------" << endl;
            for (auto &n : neislaike)
            {
                fr1 << left << setw(18) << n.vardas;
                fr1 << left << setw(18) << n.pavarde;

                // rasome galutini pazymi i faila
                double average_grade = n.rezultatas;
                fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }
            auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
            std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
            cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
            cout << endl;
            fd.close();
            fr.close();
            fr1.close();
        }
    }
}

/*
DEQUE --------------------------------------------------------------------
*/

void med_vid_deq(int n, int nd, deque<Studentas> &studentai, string &vidurkis_mediana, deque<Studentas> &neislaike, deque<Studentas> &islaike)
{
    double vid = 0;
    if (vidurkis_mediana == "vid")
    {
        for (auto &s : studentai)
        {
            for (auto &p : s.pazymiai)
                vid += p;
            s.rezultatas = 0.4 * (vid / nd) + 0.6 * s.egz;

            if (s.rezultatas < 5)
                neislaike.push_back(s);
            else
                islaike.push_back(s);

            vid = 0;
        }
    }
    else
    {
        for (auto &s : studentai)
        {
            int pazymiu_skaicius = nd;
            // isrikiuojama nuo maziausio iki didziausio
            sort(s.pazymiai.begin(), s.pazymiai.end());

            if (pazymiu_skaicius % 2 == 0)
                vid = (s.pazymiai[pazymiu_skaicius / 2 - 1] + s.pazymiai[pazymiu_skaicius / 2]) / 2;
            else
                vid = s.pazymiai[pazymiu_skaicius / 2];

            s.rezultatas = 0.4 * (vid / nd) + 0.6 * s.egz;

            if (s.rezultatas < 5)
                neislaike.push_back(s);
            else
                islaike.push_back(s);

            vid = 0;
        }
    }
    // surikiuojami studentai pagal rezultata
    sort(neislaike.begin(), neislaike.end(), compare);
    sort(islaike.begin(), islaike.end(), compare);
}

void duomenu_nuskaitymas_deq(deque<Studentas> &studentai)
{
    srand(time(NULL));
    Studentas studentas;
    deque<Studentas> neislaike;
    deque<Studentas> islaike;
    string failu_pav[4] = {"", "", "", ""};

    // studentu skaicius skirtas failams
    int num_students[] = {1000, 10000, 100000, 1000000};

    string atsakymas;
    cout << "Ar norite pasirinkti failus darbui is jau egzistuojanciu? (taip/ne): ";
    cin >> atsakymas;

    if (atsakymas == "taip" || atsakymas == "Taip") {
        string failas;
        bool failasRastas = false;

        cout << "Failu sarasas: ";
            system("dir *.txt");

        cout << "Pasirinkite faila: ";
            cin >> failas;

        ifstream skait(failas);

        while (!failasRastas) {
            if (skait.is_open()) {
                failasRastas = true;
            } else {
                cout << "Klaida, tokio failo [" << failas << "] nera." << endl;
                cin >> failas;
            }
        }

        string vidurkis_mediana = read_average_type();

        string pirmoji_eilute;
        // praignoruojama pirmoji eilute
        getline(skait, pirmoji_eilute);

        string eilute;

        auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
        while (getline(skait, eilute)) {
            istringstream iss(eilute);
            Studentas studentas;

            iss >> studentas.vardas >> studentas.pavarde;

            int pazymys;
            while (iss >> pazymys) {
                studentas.pazymiai.push_back(pazymys);
            }

            if (!studentas.pazymiai.empty()) {
                studentas.egz = studentas.pazymiai.back();
                studentas.pazymiai.pop_back();
            }

            studentai.push_back(studentas);
        }

        auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
        cout << "Duomenu is failo " << failas << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

        int studentu_sk = studentai.size();
        int nd_sk = 0;
        if (!studentai.empty()) {
            nd_sk = studentai.begin()->pazymiai.size();
        }
        auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

        med_vid_deq(studentu_sk, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
        studentai.clear();

        auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
        std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
        cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

        string filename1 = "islaike" + to_string(studentu_sk) + ".txt";
        string filename2 = "neislaike" + to_string(studentu_sk) + ".txt";

        ofstream fr(filename1);
        ofstream fr1(filename2);

        auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
            // rasomi studentu duomenys i faila
            fr << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr << left << setw(15) << "Galutinis (Med.)" << endl;

            fr << "----------------------------------------------------" << endl;
            for (auto &i : islaike)
            {
                fr << left << setw(18) << i.vardas;
                fr << left << setw(18) << i.pavarde;

                // rasomas galutinis pazymys i faila
                double average_grade = i.rezultatas;
                fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }

            auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
            cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

            auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
            // rasomi studentu duomenys i faila
            fr1 << left << setw(18) << "Vardas"
                << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

            fr1 << "----------------------------------------------------" << endl;
            for (auto &n : neislaike)
            {
                fr1 << left << setw(18) << n.vardas;
                fr1 << left << setw(18) << n.pavarde;

                // rasome galutini pazymi i faila
                double average_grade = n.rezultatas;
                fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }
            auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
            std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
            cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
            cout << endl;
        fr.close();
        fr1.close();
        skait.close();
    }

    else{
        int nd_sk;
        cout << "Iveskite skaiciu, kiek kiekvienas studentas tures pazymiu (nuo 1 iki 15 iskaitytinai): ";
        while (true)
        {
            cin >> nd_sk;

            if (cin.fail() || nd_sk < 1 || nd_sk > 15)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "klaida, skaicius turi buti nuo 1 iki 15\n";
            }

            else
                break;
        }

        string vidurkis_mediana = read_average_type();

        for (int i = 0; i < 4; i++)
        {
            int n = num_students[i];
            string filename = "studentai" + to_string(n) + ".txt";
            failu_pav[i] = filename;

            auto start = std::chrono::high_resolution_clock::now(); // paleisti

            ofstream outfile(filename);

            // pirmoji eilute
            outfile << left << setw(19) << "Vardas";
            outfile << left << setw(17) << "Pavarde";
            for (int j = 0; j < nd_sk; j++)
            {
                string nd = "ND" + to_string(j + 1);
                outfile << left << setw(5) << nd;
            }
            outfile << left << setw(5) << "Egz." << endl;

            for (int j = 1; j <= n; j++)
            {
                string vardas = generate_name(j);
                string pavarde = generate_surname(j);
                outfile << left << setw(18) << vardas;
                outfile << left << setw(18) << pavarde;

                // atsitiktiniai pazymiai
                for (int k = 0; k < nd_sk; k++)
                {
                    int grade = generate_grade();
                    outfile << left << setw(5) << grade;
                }

                // egzamino pazymys
                int exam_grade = generate_grade();
                outfile << left << setw(5) << exam_grade << endl;
            }
            outfile.close();
            auto end = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt = end - start;    // skirtumas (s)
            cout << "Failo " << filename << " kurimo sparta: " << fixed << setprecision(2) << skirt.count() << "s" << endl;

            auto start1 = std::chrono::high_resolution_clock::now(); // Paleisti
            ifstream fd(failu_pav[i]);

            string pirmoji_eilute;
            // praignoruojama pirmoji eilute
            getline(fd, pirmoji_eilute);

            for (int j = 1; j <= n; j++)
            {
                studentas.pazymiai.clear();

                fd >> studentas.vardas >> studentas.pavarde;

                int pazymys;
                for (int k = 0; k < nd_sk; k++)
                {
                    fd >> pazymys;
                    studentas.pazymiai.push_back(pazymys);
                }
                fd >> studentas.egz;

                studentai.push_back(studentas);
            }

            auto end1 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt1 = end1 - start1;  // skirtumas (s)
            cout << "Duomenu is failo " << failu_pav[i] << " skaitymo sparta: " << fixed << setprecision(2) << skirt1.count() << "s" << endl;

            int studentu_sk = studentai.size();

            auto start2 = std::chrono::high_resolution_clock::now(); // paleisti

            med_vid_deq(n, nd_sk, studentai, vidurkis_mediana, neislaike, islaike);
            studentai.clear();

            auto end2 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt2 = end2 - start2;  // skirtumas (s)
            cout << "Studentu rusiavimo i dvi grupes sparta: " << fixed << setprecision(2) << skirt2.count() << "s" << endl;

            string filename1 = "islaike" + to_string(n) + ".txt";
            string filename2 = "neislaike" + to_string(n) + ".txt";

            ofstream fr(filename1);
            ofstream fr1(filename2);

            auto start3 = std::chrono::high_resolution_clock::now(); // paleisti
            // rasomi studentu duomenys i faila
            fr << left << setw(18) << "Vardas"
            << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr << left << setw(15) << "Galutinis (Med.)" << endl;

            fr << "----------------------------------------------------" << endl;
            for (auto &i : islaike)
            {
                fr << left << setw(18) << i.vardas;
                fr << left << setw(18) << i.pavarde;

                // rasomas galutinis pazymys i faila
                double average_grade = i.rezultatas;
                fr << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }

            auto end3 = std::chrono::high_resolution_clock::now(); // stabdyti
            std::chrono::duration<double> skirt3 = end3 - start3;  // skirtumas (s)
            cout << "Islaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt3.count() << "s" << endl;

            auto start4 = std::chrono::high_resolution_clock::now(); // Paleisti
            // rasomi studentu duomenys i faila
            fr1 << left << setw(18) << "Vardas"
                << left << setw(18) << "Pavarde";
            if (vidurkis_mediana == "vid")
                fr1 << left << setw(15) << "Galutinis (Vid.)" << endl;
            else
                fr1 << left << setw(15) << "Galutinis (Med.)" << endl;

            fr1 << "----------------------------------------------------" << endl;
            for (auto &n : neislaike)
            {
                fr1 << left << setw(18) << n.vardas;
                fr1 << left << setw(18) << n.pavarde;

                // rasome galutini pazymi i faila
                double average_grade = n.rezultatas;
                fr1 << left << setw(15) << fixed << setprecision(2) << average_grade << endl;
            }
            auto end4 = std::chrono::high_resolution_clock::now(); // Stabdyti
            std::chrono::duration<double> skirt4 = end4 - start4;  // Skirtumas (s)
            cout << "Neislaikiusiu studentu spausdinimo sparta: " << fixed << setprecision(2) << skirt4.count() << "s" << endl;
            cout << endl;
            fd.close();
            fr.close();
            fr1.close();
        }
    }
}
