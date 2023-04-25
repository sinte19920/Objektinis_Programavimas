# V1.0

Nuo šios versijos yra pradedama naudoti makefile. Didžiausi pakeitimai (lyginant su v.05), kad yra 2 strategijos: pirma, kurioje studentai yra išskirstomi į du skirtingus vektorius ("islaike" ir "neislaike"), nors toks rūšiavimo būdas buvo naudojamas nuo ankstesnių versijų, o antra, kurioje studentai, gavę galutinį pažymį 5 ir daugiau yra paliekami "studentai" vektoriuje, o likę pašalinami (dirbama su tuo pačiu vektorium). Yra kiekvieną kartą paklausiama, kurią strategija vartotojas nori panaudoti.

### Studentų rūšiavimo į grupes sparta:

**Pirma strategija**
|  Įrašų skaičius  |  std::vector  |   std::list   |   std:deque   |
|------------------|---------------|---------------|---------------|
|    1 000         |  0.020s       |   0.013s      |   0.019s      |
|    10 000        |  0.223s       |   0.165s      |   0.219s      |
|    100 000       |  2.749s       |   2.185s      |   2.925s      |
|    1 000 000     |  34.626s      |   25.726s     |   34.346s     |

**Antra strategija**
|  Įrašų skaičius  |  std::vector  |   std::list   |   std:deque   |
|------------------|---------------|---------------|---------------|
|    1 000         |  0.009s       |   0.009s      |   0.010s      |
|    10 000        |  0.102s       |   0.102s      |   0.116s      |
|    100 000       |  1.260s       |   1.048s      |   1.429s      |
|    1 000 000     |  15.825s      |   11.257s     |   16.815s     |
