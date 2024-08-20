# Objektinio užduotis 3
  Programa skaičiuojanti galutinį studento rezultatą pagal pateiktus namų darbų ir egzamino rezultatus.

## Funkcionalumas
  - Meniu kuriame galima pasirinkti, ką atsitiktinai generuoti.
  - Duomenų skaitymas iš išankstinio failo.
  - Duomenų įvedimas.
  - Duomenų failo kūrimas. 
  - Galutinio balo skaičiavimas pagal vidurkį ir medianą.
  - Galima skaityti duomenis iš tam tikru formatu pateiktų teksto failų.
  - "Pažengusių" ir "Žlugusių" mokinių išvedimas atskiruose failuose.

## Perdengti operatoriai
  Jei naudojama "cin >> klasė" arba "cout << klasė>" atspausdinama arba įrašoma atitinkama klasės informacija visur pasitaikanti šioje užduotyje. Jei rašoma kažkas kitas, o ne klasė, jie veikia kaip įprastai. Pakeisti kur spausdinama galima arba keičiant freopen parametrus arba kode pritaikant ifstream ir ofstream, kas leistų naudoti skirtingus raktažodžius spausdinimui į skirtingas vietas.

## Naudojimosi instrukcijos
  - Įjungti programą.
  - Sekti terminale matomus žingsnius.
  - Jei prašome vesti failo pavadinimą, vesti be ".txt" pabaigoje.
  - Gauti rezultatus.

## Sistemos specifikacijos

- **CPU**: AMD Ryzen 5 5600H 3.30 GHz
- **RAM**: DDR4 16GB
- **HDD**: SSD 512GB

## Greičio testai (5 testų vidurkis) ms

#### Vector
| Failas | Skaitymo trukmė | Rūšiavimo trukmė | Skirstymo trukmė |
| :--- | ---- | ---- | ---- |
| stud1000 | 11 | 0 | 1 |
| stud10000 | 87 | 16 | 1 |
| stud100000 | 907 | 147 | 25 |
| stud1000000 | 8296 | 1911 | 292 |
| stud10000000 | 90697 | 25683 | 2911 |

#### List
| Failas | Skaitymo trukmė | Rūšiavimo trukmė | Skirstymo trukmė |
| :--- | ---- | ---- | ---- |
| stud1000 | 14 | 0 | 1 |
| stud10000 | 160 | 6 | 17 |
| stud100000 | 1160 | 78 | 144 |
| stud1000000 | 11753 | 1202 | 1570 |
| stud10000000 | 120384 | 18116 | 40532 |

#### Deque
| Failas | Skaitymo trukmė | Rūšiavimo trukmė | Skirstymo trukmė |
| :--- | ---- | ---- | ---- |
| stud1000 | 12 | 2 | 1 |
| stud10000 | 97 | 29 | 6 |
| stud100000 | 918 | 394 | 71 |
| stud1000000 | 9375 | 5177 | 937 |
| stud10000000 | 96751 | 69256 | 61005 |

## Skirstymas pagal skirtingas strategijas (3 testų vidurkis) ms

#### Vector
| Failas | 1 strategija | 2 strategija (originali) | 3 strategija |
| :--- | ---- | ---- | ---- |
| stud1000 | 0 | 1 | 1 |
| stud10000 | 3 | 1 | 6 |
| stud100000 | 28 | 25 | 31 |
| stud1000000 | 372 | 262 | 335 |
| stud10000000 | 5580 | 2911 | 3398 |

#### List
| Failas | 1 strategija | 2 strategija (originali) | 3 strategija |
| :--- | ---- | ---- | ---- |
| stud1000 | 1 | 1 | 1 |
| stud10000 | 20 | 17 | 10 |
| stud100000 | 242 | 144 | 149 |
| stud1000000 | 2628 | 1570 | 1806 |
| stud10000000 | 60549 | 40532 | 25499 |

#### Deque
| Failas | 1 strategija | 2 strategija (originali) | 3 strategija |
| :--- | ---- | ---- | ---- |
| stud1000 | 1 | 1 | 0 |
| stud10000 | 12 | 6 | 6 |
| stud100000 | 159 | 71 | 70 |
| stud1000000 | 1698 | 937 | 884 |
| stud10000000 | 102817 | 61005 | 52611 |

## Klasių ir struktūrų spartos palyginimas (naudojant vektorių)

#### Struktūra
| Failas | Skaitymo trukmė | Rušiavimo trukmė | Skirtsymo trukmė |
| :--- | ---- | ---- | ---- |
| stud1000000 | 8996 | 1911 | 292 |
| stud10000000 | 90697 | 25683 | 2911 |

#### Klasė
| Failas | Skaitymo trukmė | Rušiavimo trukmė | Skirtsymo trukmė |
| :--- | ---- | ---- | ---- |
| stud1000000 | 8152 | 2805 | 125 |
| stud10000000 | 86862 | 37644 | 1424 |

## Optimizavimo "flag'ų" palyginimas (stud1000000)

|  | Skaitymo, rūšiavimo ir skirtsymo trukmė (ms) | .exe dysis |
| :--- | ---- | ---- |
| Struct -O1 | 10118 | 466 KB |
| Struct -O2 | 10166 | 466 KB |
| Struct -O3 | 10388 | 466 KB |
| Class -O1 | 12071 | 451 KB |
| Class -O2 | 11781 | 451 KB |
| Class -O3 | 11082 | 451 KB |

## Release'ų istorija

- V.pradinė: pirma prelimenati programa, kuri skaičiuoja ranka įvestus mokinio duomeis ir išveda galutinius rezultatus.
- v0.1: nereikia iš anksto nustatyti duomenų kiekio, padarytas atsitiktinės generacijos funkcionalumas. Programa padaryta naudojant vektorius ir, atskirai, naudojant masyvus.
- v0.2: programa gali duomenis priimti iš failo.
- v0.3: programa paskirstyta per kelis failus, pridėtas išimčių valdymas.
- v0.4: programoje galima generuoti naujus failus, duomenys atspausdinami į 2 atskirus failus, atliekama laiko analizė.
- v1.0: atliktas programos testavimas su skirtingais konteineriais, naudotos skirtingos mokinių skirstymo strategijos, padarytos jų efektyvumo strategijos.
- v1.1: programa perdaryta naudojant custom klases o ne struktūras.
- v1.2: pritaikyta rule of five, sukurti move ir copy operatoriai
- v1.5: klasė padalinta į dvi dalis, viena iš kurių abstrakti bazinė.

## Tyrimas

Buvo atliktas mokinių dalijimo į 2 konteinerius skirtingų strategijų testavimas, kuris padėjo paoptimizuoti greitį naudojant list ir deque, bet sparta naudojant vector sumažėjo. Visais atvejais 1 stratejija buvo pati lėčiausia ir taip pat ji prasčiausia programos naudojamos vietos atžvilgiu. 

## Kompiuterio paruošimas programai

Čia gidas Windows sistemoms.
- Atsisiųskite c++ kompiliatorių. Gidas čia: https://www.geeksforgeeks.org/installing-mingw-tools-for-c-c-and-changing-environment-variable/. 
- Atsisiųskite make. Gidas čia: https://linuxhint.com/install-use-make-windows/.

## Programos diegimas ir paleidimas

1. Atsisiųskite programos kodą iš repozitorijos.
2. Terminale pasiekite atsisiuntimo aplanką.
3. Terminale parašykite "make" (pirmą kartą, kai leidžiate programą).
4. Jei norite patikrinti testus, naudokite "make test".
5. Paleiskite programą terminale įvesdami .\prog.exe (Windows) arba .\prog (Linux)
