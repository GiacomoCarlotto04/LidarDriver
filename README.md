# LIDAR DRIVER

Progetto implementato in **C++** per gestire dati acquisiti tramite un sensore **LIDAR**.

---

### Indice

- Descrizione
- Struttura del progetto
- Costruttori
- Funzioni
- Utilizzo

### **Autori**

Il progetto è stato realizzato da:

- **David Francesco Padovan** (matr. 2101813)
- **Giacomo Carlotto** (matr. 2101830)
- **Alberto Bortoletto** (matr. 2101761)

---

## **Descrizione**

Le operazioni consentite sono:

- **Ricevere scansioni di dati** e memorizzarle in un **buffer circolare** di dimensione fissa.
- **Accedere alle scansioni** salvate.
- **Recuperare la lettura di una distanza** dato un determinato **angolo**.
- **Pulire il buffer circolare**.

---

## **Struttura del progetto**

Il progetto è strutturato come segue:


    LidarDriver
    ├── build                 # File eseguibili (es: .exe)
    ├── include               # File di interfaccia (es: .h o .hpp)
    │   └── LidarDriver.h
    ├── README.txt            # Questo file
    └── src                   # File sorgente (es: .cpp)
        ├── main.cpp
        └── LidarDriver.cpp
---
## **Costruttori**

I **costruttori** implementati sono:

- **Costruttore di default** `LidarDriver()`
  -  **Autore**: _David F. Padovan_

- **Costruttore parametrico** `LidarDriver(double res)`
  -  **Descrizione**: Richiede la risoluzione angolare come parametro `double`.
  -  **Autore**: _David F. Padovan_

- **Costruttore di Copy**
  -  **Descrizione**: Richiede una costante reference ad un oggetto di tipo `LidarDriver`. Permette di creare un oggetto `LidarDriver` copiando i dati da un altro oggetto dello stesso tipo.
  -  **Autore**: _Alberto Bortoletto_

- **Costruttore di Move**
  -  **Descrizione**: Richiede una rvalue di un oggetto `LidarDriver`. Permette di trasferire il contenuto da un oggetto `LidarDriver` ad un altro oggetto di tipo `LidarDriver` al momento della sua creazione.
  -  **Autore**: _Alberto Bortoletto_

---

## **Funzioni**

Le **funzioni membro** implementate sono le seguenti:
```cpp
void new_scan(const std::vector<double>& scan)
std::vector<double> get_scan()
void clear_buffer()
double get_distance(double angle) const
```

Le **getter function** implementate sono le seguenti:

```cpp
double get_angular_res() const
int get_scanner_size() const
std::vector<std::vector<double>> get_buffer() const
int get_oldest_index() const
int get_logical_size() const
```

Le **funzioni di assegnamento** implementate sono:

```cpp
LidarDriver& LidarDriver::operator=(const LidarDriver& obj)
LidarDriver& LidarDriver::operator=(LidarDriver&& obj)
```

Le **funzioni ausiliarie** implementate sono le seguenti:

```cpp
ostream& operator<<(std::ostream& os, const LidarDriver& obj)
vector<double> check_dim(const vector<double>& v, int sc_size)
```
---

### Dettaglio Funzioni

#### `new_scan`

- **Descrizione**: Questa funzione richiede un riferimento costante ad un vettore di tipo `double` che rappresenta una scansione. La funzione memorizza la scansione nel buffer, verificando la sua dimensione tramite la funzione ausiliaria `check_dim`.
-  **Autore**: _David F. Padovan_

#### `get_scan`

- **Descrizione**: Restituisce la scansione più vecchia presente nel buffer e la rimuove. Se il buffer è vuoto, lancia l'eccezione `out_of_range("Buffer is empty")`.
-  **Autore**: _Giacomo Carlotto_

#### `clear_buffer`

- **Descrizione**: Azzera il contenuto del buffer senza restituire nulla.
-  **Autore**: _Giacomo Carlotto_

#### `get_distance`

- **Descrizione**: Questa funzione richiede come parametro un angolo di tipo `double` compreso tra 0 e 180 e restituisce la distanza corrispondente all'angolo nella scansione più recente. Se l'angolo non è disponibile, la funzione restituisce la distanza relativa al valore di angolo più vicino. Se l'angolo non è valido, lancia l'eccezione `invalid_argument("Angle must be between 0 and 180")`.
-  **Autore**: _Alberto Bortoletto_

---

### Operator `<<`

L'**overload dell'operatore** `<<` permette di stampare a schermo l'ultima scansione salvata nel buffer senza eliminarla.
-  **Autore**: _Alberto Bortoletto_

---

### **Copy Assignment Operator** `=`

Questo operatore membro accetta una **costante reference** ad un oggetto `LidarDriver`. Permette di copiare il contenuto di un oggetto `LidarDriver` in un altro oggetto dello stesso tipo.
-  **Autore**: _Alberto Bortoletto_

---

### **Move Assignment Operator** `=`

Questo operatore membro accetta una **rvalue** di un oggetto `LidarDriver`. Permette di spostare il contenuto da un oggetto `LidarDriver` ad un altro oggetto dello stesso tipo, evitando una copia costosa.
-  **Autore**: _Alberto Bortoletto_

---

### `check_dim`

- **Descrizione**: Funzione ausiliaria che verifica la dimensione di un vettore passato come parametro:
  - Se la dimensione è inferiore a quella prevista per ogni scansione, la funzione completa il vettore con zeri.
  - Se la dimensione è superiore, il vettore viene troncato.
  - Viene utilizzata nel metodo `new_scan` per garantire che le scansioni abbiano la dimensione corretta.
-  **Autore**: _David F. Padovan_

---

## **Utilizzo**

### Compilazione

Il programma è compilabile utilizzando il comando seguente:

```bash
g++ -Iinclude -o build/main src/main.cpp src/LidarDriver.cpp
```
---

### Esecuzione
```bash
build/main
```