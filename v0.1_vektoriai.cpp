#include "Mylib.h"

// studento duomenu struktura
struct Studentas
{
    string vardas;
    string pavarde;
    vector<double> pazymiai; // pazymio vektorius
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
void med_vid(int n, int nd, vector<Studentas> &studentai, string &vidurkis_mediana)
{
    vidurkis_mediana = read_average_type();
    double vid = 0;
    if (vidurkis_mediana == "vid")
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < nd; j++)
                vid += studentai[i].pazymiai[j];
            studentai[i].rezultatas = 0.4 * (vid / nd) + 0.6 * studentai[i].egz;
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
            vid = 0;
        }
    }
}

void rezultatu_spausdinimas(string vidurkis_mediana, vector<Studentas> &studentai, int n)
{
    cout << left << setw(15) << "Vardas"
         << left << setw(15) << "Pavarde";
    if (vidurkis_mediana == "vid")
        cout << left << setw(15) << "Galutinis (Vid.)" << endl;

    else
        cout << left << setw(15) << "Galutinis (Med.)" << endl;

    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < studentai.size(); i++)
    {
        cout << left << setw(15) << studentai[i].vardas
             << left << setw(15) << studentai[i].pavarde
             << left << setw(15) << fixed << setprecision(2) << studentai[i].rezultatas << endl;
    }
}

int main()
{
    Studentas studentas;
    string atsakymas;
    cout << "Ar yra zinomas tikslus studentu ir namu darbu pazymiu skaiciai? (taip / ne): ";
    atsakymas = nuskaityti_atsakyma();

    // jeigu NEZINOMAS mokiniu ir pazymiu skaicius
    if (atsakymas == "ne")
    {
        // sudaromas strukturos Studentas vektorius
        vector<Studentas> studentai;

        do
        {
            // isvalomas studento pazymiu vektorius kiekvieno naujo studento ivedimo pradzioje
            studentas.pazymiai.clear();

            cout << "Iveskite studento varda ir pavarde " << endl
                 << "(parasius bent viena is reikiamu duomenu spauskite enter):" << endl;
            cin >> studentas.vardas >> studentas.pavarde;

            int pazymys = 0;
            cout << "Iveskite pazymi/-ius 10-baleje sistemoje (kai noresite baigti, iveskite bet koki kita simboli): ";

            while (cin >> pazymys && pazymys >= 0 && pazymys <= 10)
                studentas.pazymiai.push_back(pazymys);

            // jeigu iskarto (nespejus ivesti nei vieno pazymio) ivedama netinkama reiksme - pazymys virsta 0
            if (studentas.pazymiai.size() == 0)
                studentas.pazymiai.push_back(pazymys);

            // kai ivedama netinkama reiksme (norima nutraukti pazymiu ivedima)
            if (cin.fail())
            {
                // isvalo cin cikla
                cin.clear();

                // praignoruoja ivesti
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            cout << "Iveskite egzamino rezultata 10-baleje sistemoje: ";
            while (!(cin >> studentas.egz) || studentas.egz < 0 || studentas.egz > 10)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            studentai.push_back(studentas);

            cout << "Ar norite ivesti daugiau duomenu? (taip / ne): ";
            atsakymas = nuskaityti_atsakyma();
        } while (atsakymas == "taip");

        string vidurkis_mediana;
        med_vid(studentai.size(), studentas.pazymiai.size(), studentai, vidurkis_mediana);
        rezultatu_spausdinimas(vidurkis_mediana, studentai, studentai.size());
    }

    // jeigu ZINOMAS mokiniu ir pazymiu skaicius
    else
    {
        int n, nd;

        cout << "Iveskite norima studentu skaiciu: ";
        cin >> n;
        cout << "Iveskite namu darbu pazymiu skaiciu: ";
        cin >> nd;

        vector<Studentas> studentai;

        for (int i = 0; i < n; i++)
        {
            // isvalomas studento pazymiu vektorius kiekvieno naujo studento ivedimo pradžioje
            studentas.pazymiai.clear();

            cout << "Iveskite studento varda ir pavarde: ";
            cin >> studentas.vardas >> studentas.pavarde;

            int pazymys = 0;

            cout << "Ar norite sugeneruoti atsitiktinius pazymius? (taip / ne): ";
            atsakymas = nuskaityti_atsakyma();
            if (atsakymas == "taip")
            {
                for (int i = 0; i < nd; i++)
                {
                    int randomPazymys = rand() % 10 + 1;
                    studentas.pazymiai.push_back(randomPazymys);
                }
                studentas.egz = rand() % 10 + 1;
            }
            if (atsakymas == "ne")
            {
                cout << "Iveskite studento namu darbu pazymius (10-baleje sistemoje): " << endl;
                for (int j = 0; j < nd; j++)
                {
                    cin >> pazymys;
                    if (pazymys < 0 || pazymys > 10)
                        cin >> pazymys;

                    studentas.pazymiai.push_back(pazymys);
                }

                cout << "Iveskite egzamino rezultata 10-baleje sistemoje: ";
                while (!(cin >> studentas.egz) || studentas.egz < 0 || studentas.egz > 10)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                studentai.push_back(studentas);
            }
        }

        string vidurkis_mediana;
        med_vid(n, nd, studentai, vidurkis_mediana);
        rezultatu_spausdinimas(vidurkis_mediana, studentai, n);
    }
    return 0;
}