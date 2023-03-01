#include "Mylib.h"

// studento duomenu struktura
struct Studentas
{
    string vardas, pavarde;
    double pazymiai[100];
    int pazymiu_sk[100];
    double egz;
    double rezultatas;
};

// funkcija, skirta taip / ne atsakymo įvedimui
string nuskaityti_atsakyma()
{
    string atsakymas;
    while (true)
    {
        cin >> atsakymas;
        if (atsakymas == "taip")
            return "taip";
        else if (atsakymas == "ne")
            return "ne";
        else
            cout << "Netinkama ivestis, reikia irasyti 'taip' arba 'ne'." << endl;
    }
}

// funkcija, skirta vidurkio arba medianos pasirinkimo nuskaitymui
string read_average_type()
{
    string vidurkis_mediana;

    cout << "Norite, kad galutiniame rezultate butu pateiktas rezultatu vidurkis ar mediana?" << endl
         << "(irasykite 'med' - medianai, 'vid' - vidurkiui): ";

    // nuskaitome vartotojo pasirinkimą, kol jis įves tinkamą reikšmę
    while (vidurkis_mediana != "med" && vidurkis_mediana != "vid")
        cin >> vidurkis_mediana;

    return vidurkis_mediana;
}

// funkcija, apskaiciuojanti mediana arba vidurki
void med_vid(int n, Studentas studentas[], string &vidurkis_mediana)
{
    vidurkis_mediana = read_average_type();
    double vid = 0;
    if (vidurkis_mediana == "vid")
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < studentas[i].pazymiu_sk[i]; j++)
                vid += studentas[i].pazymiai[j];
            studentas[i].rezultatas = 0.4 * (vid / studentas[i].pazymiu_sk[i]) + 0.6 * studentas[i].egz;
            vid = 0;
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int pazymiu_skaicius = studentas[i].pazymiu_sk[i];
            // isrikiuojama nuo maziausio iki didziausio burbulų rikiavimo algoritmu
            for (int l = 0; l < n; l++)
            {
                for (int j = 0; j < pazymiu_skaicius - 1; j++)
                {
                    for (int k = 0; k < pazymiu_skaicius - j - 1; k++)
                    {
                        if (studentas[l].pazymiai[k] > studentas[l].pazymiai[k + 1])
                        {
                            int temp = studentas[l].pazymiai[k];
                            studentas[l].pazymiai[k] = studentas[l].pazymiai[k + 1];
                            studentas[l].pazymiai[k + 1] = temp;
                        }
                    }
                }

                if (pazymiu_skaicius % 2 == 0)
                    vid = (studentas[i].pazymiai[pazymiu_skaicius / 2 - 1] + studentas[i].pazymiai[pazymiu_skaicius / 2]) / 2;
                else
                    vid = studentas[i].pazymiai[pazymiu_skaicius / 2];

                studentas[i].rezultatas = 0.4 * (vid / pazymiu_skaicius) + 0.6 * studentas[i].egz;
            }
            vid = 0;
        }
    }
}

void rezultatu_spausdinimas(string vidurkis_mediana, Studentas studentas[], int n)
{
    cout << left << setw(15) << "Vardas"
         << left << setw(15) << "Pavarde";
    if (vidurkis_mediana == "vid")
        cout << left << setw(15) << "Galutinis (Vid.)" << endl;

    else
        cout << left << setw(15) << "Galutinis (Med.)" << endl;

    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << left << setw(15) << studentas[i].vardas
             << left << setw(15) << studentas[i].pavarde
             << left << setw(15) << fixed << setprecision(2) << studentas[i].rezultatas << endl;
    }
}

int main()
{
    Studentas studentas[1000];
    string atsakymas;
    cout << "Ar yra zinomas tikslus studentu ir namu darbu pazymiu skaiciai? (taip / ne): ";
    atsakymas = nuskaityti_atsakyma();

    // jeigu NEZINOMAS mokiniu ir pazymiu skaicius
    if (atsakymas == "ne")
    {
        int studentu_sk = 0;
        int pazymiu_sk;
        do
        {
            pazymiu_sk = 0;

            cout << "Iveskite studento varda ir pavarde " << endl
                 << "(parasius bent viena is reikiamu duomenu spauskite enter):" << endl;
            cin >> studentas[studentu_sk].vardas >> studentas[studentu_sk].pavarde;

            int pazymys = 0;
            cout << "Iveskite pazymi/-ius 10-baleje sistemoje (kai noresite baigti, iveskite bet koki kita simboli): ";

            while (cin >> pazymys && pazymys >= 0 && pazymys <= 10)
            {
                studentas[studentu_sk].pazymiai[pazymiu_sk] = pazymys;
                pazymiu_sk++;
            }
            studentas[studentu_sk].pazymiu_sk[studentu_sk] = pazymiu_sk;

            // kai ivedama netinkama reiksme (norima nutraukti pazymiu ivedima)
            if (cin.fail())
            {
                // isvalo cin cikla
                cin.clear();
                // praignoruoja ivesti
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (studentas[studentu_sk].pazymiu_sk[studentu_sk] == 0)
            {
                studentas[studentu_sk].pazymiai[pazymiu_sk] = pazymys;
                studentas[studentu_sk].pazymiu_sk[studentu_sk]++;
            }

            cout << "Iveskite egzamino rezultata 10-baleje sistemoje: ";
            while (!(cin >> studentas[studentu_sk].egz) || studentas[studentu_sk].egz < 0 || studentas[studentu_sk].egz > 10)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Ar norite ivesti daugiau duomenu? (taip / ne): ";
            atsakymas = nuskaityti_atsakyma();
            studentu_sk++;
        } while (atsakymas == "taip");

        cout << "Studentu skaicius: " << studentu_sk << endl;
        for (int i = 0; i < studentu_sk; i++)
        {
            cout << i + 1 << "-ojo studento pazymiai: ";
            for (int j = 0; j < studentas[i].pazymiu_sk[i]; j++)
                cout << studentas[i].pazymiai[j] << " ";

            cout << "  Egzamino rezultatas: " << studentas[i].egz << endl;
        }

        string vidurkis_mediana;
        med_vid(studentu_sk, studentas, vidurkis_mediana);
        rezultatu_spausdinimas(vidurkis_mediana, studentas, studentu_sk);
    }

    // jeigu ZINOMAS mokiniu ir pazymiu skaicius
    else
    {
        int n, nd;

        cout << "Iveskite norima studentu skaiciu: ";
        cin >> n;
        cout << "Iveskite namu darbu pazymiu skaiciu: ";
        cin >> nd;

        for (int i = 0; i < n; i++)
        {
            studentas[i].pazymiu_sk[i] = nd;
            cout << "Iveskite studento varda ir pavarde: ";
            cin >> studentas[i].vardas >> studentas[i].pavarde;

            int pazymys = 0;

            cout << "Ar norite sugeneruoti atsitiktinius pazymius? (taip / ne): ";
            atsakymas = nuskaityti_atsakyma();
            if (atsakymas == "taip")
            {
                srand(time(NULL));
                for (int l = 0; l < nd; l++)
                {
                    int randomPazymys = rand() % 10 + 1;
                    studentas[i].pazymiai[l] = randomPazymys;
                }
                studentas[i].egz = rand() % 10 + 1;
            }
            if (atsakymas == "ne")
            {
                cout << "Iveskite " << i + 1 << "-ojo studento namu darbu pazymius (10-baleje sistemoje): " << endl;
                for (int j = 0; j < nd; j++)
                {
                    if (cin >> pazymys && pazymys >= 0 && pazymys <= 10)
                        studentas[i].pazymiai[j] = pazymys;
                }

                cout << "Iveskite egzamino rezultata 10-baleje sistemoje: ";
                while (!(cin >> studentas[i].egz) || studentas[i].egz < 0 || studentas[i].egz > 10)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            cout << endl;
            cout << i + 1 << "-ojo studento pazymiai: ";
            for (int j = 0; j < studentas[i].pazymiu_sk[i]; j++)
                cout << studentas[i].pazymiai[j] << " ";
            cout << endl
                 << "Egzamino rezultatas: " << studentas[i].egz << endl;
        }

        string vidurkis_mediana;
        med_vid(n, studentas, vidurkis_mediana);
        rezultatu_spausdinimas(vidurkis_mediana, studentas, n);
    }
    return 0;
}