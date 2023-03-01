Kodas nuskaito studento duomenis (vardas, pavardė, pažymiai) ir išsaugomi į masyvus (v0.1_masyvai.cpp) arba vektorius (v0.1_vektoriai.cpp). Išsaugojęs duomenis, apskaičiuojamas galutinis studento pažymys su mediana arba vidurkiu, priklausomai nuo vartotojo poreikio. Apskaičiuojamas galutinis pažymys pagal šią formulę: Galutinis = 0.4 * vidurkis + 0.6 * egzaminas arba Galutinis = 0.4 * mediana + 0.6 * egzaminas. Galutiniame rezultate išvedami šie duomenys: studento vardas, pavardė ir galutinis pažymys. Taip pat kode galima pasirinkti, ar sugeneruoti atsitiktinius pažymius. Kodą galima naudoti net ir tuo metu, jeigu nežinomas studentų ir pažymių skaičius. Kiekvieną kartą įvesties metu, įvedus netinkamą įvestį, prašoma pakartoti, kol ji bus teisinga (išimtis taikoma tik tuo metu, kai pažymių skaičius nežinomas ir kaip tik prašoma klaidinga įvestis, norint parodyti, kad pažymių tam studentui daugiau nebebus priskirta).

#### išsamesni visi koduose vykdomi žingsniai aprašyti čia:

### v0.1_vektoriai

### kode galima rasti:
1. studento/-ų duomenų struktūrą.
2. "main" funkciją:
  2.1. paklausiama, ar yra iš anksto žinomas duomenų kiekis, kurį reikės įrašyti (atsakymas nuskaitomas su "nuskaityti_atsakyma" funkcija). Yra tik du pasirinkimai - "taip" arba "ne", netinkamos įvesties metu prašoma pakartoti iki tol, kol bus teisinga.
  • Jeigu atsakymas "ne":
  2.1.1. prašoma įvesti studento vardą ir pavardę.
  2.1.2. prašoma įvesti pažymį/-ius (norint nutraukti ciklą reikia įvesti bet kokį kita simbolį, kuris nepriklauso intervalui nuo 0 iki 10 įskaitytinai)
  2.1.3. įvedus netinkamą įvestį (ciklo nutraukimui) ji yra anuliuojama ir praignpruojama (neišsaugoma).
  2.1.4. prašoma įvesti egzamino rezultatą 10-balėje sistemoje (netinkamos įvesties metu prašoma pakartoti iki tol, kol bus teisinga).
  2.1.5. įvesti studento duomenys yra pridedami į vektorių, kuriame jie turi būti išsaugomi (pagal užduoties nurodymus).
  2.1.6. paklausiama, ar toliau vartotojas nori įvesti naujo studento duomenis, jeigu atsakymas "taip" - ciklas pasikartoja, jeigu atsakymas "ne", studento duomenų ciklas nutraukiamas (netinkamos įvesties metu prašoma pakartoti iki tol, kol bus teisinga).
  • Jeigu atsakymas "taip":
  2.1.1. prašoma įvesti studentų ir jų pažymių skaičius.
  2.1.2. prašoma įvesti studento vardą ir pavardę.
  2.1.3. paklausiama, ar sugeneruoti atsitiktinius pažymius (atsakymas turi būti "taip" arba "ne", kitu atveju prašoma pakartoti iki tol, kol bus teisinga).
    • Jeigu atsakymas "taip":
    2.1.3.1. sugeneruojami atsitiktiniai pažymiai nuo 0 iki 10 įskaitytinai (kiekvieną kartą paleidus kodą sugeneruojami skirtingi pažymiai).
    • Jeigu atsakymas "ne":
    2.1.3.1. prašoma įvesti pažymius nuo 0 iki 10 įskaitytinai (įvedus neteisingą simbolį jis praignoruojamas)
    2.1.3.2. prašoma įvesti egzamino rezultatą 10-balėje sistemoje (netinkamos įvesties metu prašoma pakartoti iki tol, kol bus teisinga).
    2.1.3.3. įvesti studento duomenys yra pridedami į vektorių, kuriame jie turi būti išsaugomi (pagal užduoties nurodymus).
  
###  abiejų ciklų pabaigoje atliekami tie patys veiksmai:
  2.1.1. panaudojama "med_vid" funkcija, kuri paklausia, ar vartotojas studento rezultatą nori gauti apskaičiuotą vidurkiu arba medianą ("vid" arba "med", netinkamos įvesties metu prašoma pakartoti iki tol, kol bus teisinga). Po rezultato pasirinkimo apskaičiuojama arba mediana arba vidurkis.
  2.1.2. "rezultatu_spausdinimas" funkcija išspausdina studento/-ų vardą, pavardę ir pasirinktos formos rezultatą (vidurkis arba mediana).
3. "nuskaityti_atsakyma" funkcija (nuskaito "taip" arba "ne" įvestis).
4. "read_average_type" funkcija (nuskaito norimo rezultato tipa "mediana" arba "vidurkis").
5. "med_vid" funkcija (apskaičiuoja medianą arba vidurkį).
6. "rezultatu_spausdinimas" funkcija, atspausdinanti galutinį rezultatą (duomenis).

### v0.1_masyvai

kodo veikimo principas analogiškas anksčiau aprašytam "v0.1_vektoriai" kodui, tik kad visa informacija yra išsaugoma masyve/-uose.
