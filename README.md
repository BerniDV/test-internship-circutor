# test-internship-circutor

## Precondicions

El programa funciona suposant que:

- No hi ha més signes de puntuació que els mostrats en l'enunciat.
- Tots els caràcters a excepció dels signes de puntuació poden ser representats amb una lletra minúscula.
- No hi ha cap salt de línia al final de l'output.
- Els signes de puntuació són gramaticalment correctes i van seguits d'un espai.
- L'input està representat per una sola entrada, ja que per com està programat un cop s'ha analitzat el primer input el programa finalitza.



## Prova Circutor


### Compilador

Durant el desenvolupament d'aquesta prova s'ha utilitzat el compilador `g++`, aquest compilador es pot descarregar en un entorn linux instal·lant el paquet `build-essentials` per a desenvolupadors amb la següent comanda:

```
$ sudo apt update
$ sudo apt install build-essential
```

Si la instal·lació ha sigut correcta, s'ha de poder veure la versió del compilador amb la següent comanda:

```
$ g++ --version
```

Per executar el programa primerament s'han de compilar els diferents fitxers .cpp i fer un link amb el compilador, per fer tot això cal executar la següent comanda des del directori [src](/src):

```
$ g++ -std=c++11 main.cpp TextFormatter.cpp -o word-sorter
```

Des d'aquest moment hi haurà un executable anomenat **word-sorter** en el directori


### Execució

Per executar el programa anteriorment compilat s'executarà la següent comanda en el directori on ha sigut generat l'executable:

```
$ ./word-sorter
```

No obstant això, en aquest cas la consola esperarà a l'input de l'usuari. Per consumir l'input des d'un fitxer s'ha de situar aquest fitxer en el directori de [inputs](/test/inputs) i executar la següent comanda des del directori de l'[executable](/src):

```
$ ./word-sorter < ../test/inputs/NomInput
```

On **NomInput** és el nom del fitxer que representa l'entrada de l'usuari.

En cas de voler imprimir l'output en un altre fitxer i que aquest no sigui imprès per consola s'ha d'executar la següent comanda:

```
$ ./word-sorter < ../test/inputs/NomInput > ../test/outputs/NomOutput
```

En aquest cas es generarà un fitxer amb el nom **NomOutput** en el directori de [outputs](/test/outputs) amb el resultat de l'execució.


### Comparació

Per tal de comparar la sortida del programa amb la solució correcta s'ha de crear un fitxer amb la solució en el directori de [solucions](/test/solutions) i executar la següent comanda adaptant el nom de la solució i de l'output:

```
$ diff ../test/outputs/NomOutput ../test/solutions/NomSolution
```

L'anterior comanda imprimirà per consola les diferències que hi ha entre els dos fitxers, en cas de ser idèntics no imprimirà res.


### Solució

L'execució del programa comença en el fitxer [main.cpp](src/main.cpp), la primera decisió ha sigut transformar tot el fitxer d'input en un únic string, d'aquesta manera se simplifica molt els següents passos on s'ha de canviar el format d'aquest text. A més, durant l'input s'eliminen els salts de línia i es canvien per espais, això es fa ja que altrament la paraula del final d'una línia es concatenaria amb la primera paraula de la següent línia. 
Aquest comportament s'ha aconseguit amb un bucle while, on mentre que hi hagi una següent línia s'incorpora un espai i es concatena amb la resta del string.

A continuació s'ha decidit que tota la lògica referent a canviar el format del text ha de ser encapsulada, d'aquesta manera s'augmenta la llegibilitat i la cohesió del codi. Per fer-ho s'ha
creat una classe **TextFormatter** amb totes les funcionalitats necessàries, aquesta classe ha sigut dividida en un fitxer [.h](/headers/TextFormatter.h) amb les capçaleres i un fitxer [.cpp](/src/TextFormatter.cpp) amb les implementacions. D'aquesta manera se segueixen els estàndards de c++ i s'agilitza la funció del linker del compilador a l'importar la classe.

La següent decisió ha sigut utilitzar una referència d'un r-value per passar per paràmetre el text a ser modificat en la constructora del **TextFormatter**, això ha sigut així, ja que passar per valor el string (és a dir, fer una còpia de l'objecte perquè la seva modificació en la classe no repercuteixi en l'estat del string original) és molt costós tenint en compte la potencial llargada del text, pel fet que aquesta no s'especifica en l'enunciat. La segona opció és passar per referència (és a dir, la direcció de memòria) del string; no obstant això, significaria
que l'usuari (client en cas d'una potencial refactorització d'aquesta classe per usar-la com interfície reusable) té la capacitat de canviar el contingut d'aquest text en meitat de la lògica del **TextFormater**, i per tant, obtenir un comportament indefinit.
Per solucionar aquest problema, i que la solució sigui eficient, s'ha decidit utilitzar **move semantics** (característica incorporada en c++11), d'aquesta manera el client ha de transformar explícitament el paràmetre en una referència a r-value i se li comunica que el contingut de la direcció de memòria que conté el text serà consumit, i per tant, l'accés posterior a aquesta direcció desencadenarà un comportament indefinit. D'aquesta manera
el compilador pot copiar el contingut del text extraient-lo directament de la direcció de memòria proporcionada, i no ha de fer passos intermedis en una altra direcció per poder utilitzar-lo.

A continuació s'ha implementat les diferents funcionalitats necessàries per canviar el format del text, tot i que moltes d'aquestes funcions es podrien haver fet manualment iterant el string i fent servir el codi **ASCI** vinculat a cada caràcter, s'ha decidit utilitzar les funcionalitats que c++ proporciona en la seva `std`, d'aquesta manera es delega el control d'errors menors a la tecnologia c++, que en si mateix segueix tots els estàndards de la indústria i no es perd temps reinventant la roda.

En aquest cas, les úniques funcions que aporta valor comentar-les és l'ús d'un lambda (incorporada en c++11) per tal de simular un punter a una funció en la funcionalitat **LowercaseAllWords**. D'aquesta manera el codi és altament llegible. 
També és necessari mencionar l'ús d'**istringstream** per emplenar el buffer i agafar les paraules del text en blocs com si fos un input de l'usuari, en comptes d'iterar per cada caràcter i extreure una paraula cada vegada que es troba un espai, ja que aquest seria un procediment molt ineficient.

Una vegada es té totes les paraules separades en un vector amb el format correcte s'han d'ordenar. Atès que realment l'ordre no és total, sinó que només s'ordena per la primera lletra, i que les paraules amb la mateixa primera lletra mantenen l'ordre en què apareixen en el text, no es pot utilitzar un algoritme d'ordenament estàndard.
En aquest cas, s'ha decidit aprofitar-se de les característiques matemàtiques que té un diccionari per ordenar automàticament en un temps O(log n) totes les paraules.

El diccionari conté com a clau les inicials en minúscula que apareixen en el text, i com a valor conté un vector de strings per guardar aquelles paraules que comencen amb la inicial de la clau en l'ordre que van apareixent.
Atès que l'arbre que implementa internament l'algoritme dels diccionaris en c++ ordena les claus ascendentment, només s'haurà de recórrer el diccionari en temps O(n)  per obtenir de forma totalment automàtica i eficient totes les paraules ordenades per inicial i en l'ordre que apareixen en el text.


### Llenguatge

He decidit usar `C++`, ja que la majoria de llenguatges automatitzen i abstrauen el funcionament intern del programa de cara al desenvolupador, de manera que no és necessari un profund coneixement intern d'aquest.
En cas de no haver fet servir `C++` no s'hauria pogut discutir i prendre la majoria de decisions que s'han descrit anteriorment, ja que no hi hauria la capacitat de manipular memòria a tan baix nivell, i, per tant, es perdria eficiència seguint les implementacions estàndard de cada llenguatge.
A més, `C++` és el llenguatge en el qual el desenvolupador se sent més còmode i del que té coneixements més profunds.
