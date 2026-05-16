#include "LidarDriver.h"
#include <cmath>
using namespace std;

/*COSTANTI*/
    //BUFFER_DIM
    const int LidarDriver::BUFFER_DIM = 10;

/*COSTRUTTORI*/

    //Costruttore di default
    LidarDriver::LidarDriver()
        : angular_res{1}, oldest_index{0}, logical_size{0}, scanner_size{181}, buffer{BUFFER_DIM} {}

    //Costruttore parametrico
    LidarDriver::LidarDriver(double res)
        : angular_res{res}, oldest_index{0}, logical_size{0}, buffer{BUFFER_DIM}
    {
        if(res < 0.1 || res > 1)
            throw invalid_argument("Angular resolution must be between 0.1 and 1.0");
        
        //Imposto la scanner size che dipende dalla risoluzione angolare
        scanner_size = round(180/angular_res) + 1;

    }

    //Costruttore di Move
    LidarDriver::LidarDriver(const LidarDriver& obj)
        : angular_res{obj.angular_res}, 
          scanner_size{obj.scanner_size},
          buffer{obj.buffer},                   //Gestito automaticamente da std::vector<>
          oldest_index{obj.oldest_index},
          logical_size{obj.logical_size}
    {}

    //Costruttore di Copy
    LidarDriver::LidarDriver(LidarDriver&& obj)
        : angular_res{obj.angular_res}, 
          scanner_size{obj.scanner_size},
          buffer{obj.buffer},                   //Gestito automaticamente da std::vector<>
          oldest_index{obj.oldest_index},
          logical_size{obj.logical_size}
    {
        obj.angular_res = 0;
        obj.scanner_size = 0;
        obj.oldest_index = 0;
        obj.logical_size = 0;
    }


/*FUNZIONI MEMBRO*/

    //Getter
    double LidarDriver::get_angular_res() const {return angular_res;}
    int LidarDriver::get_scanner_size() const {return scanner_size;}
    vector<vector<double>> LidarDriver::get_buffer() const {return buffer;}
    int LidarDriver::get_oldest_index() const {return oldest_index;}
    int LidarDriver::get_logical_size() const {return logical_size;}

    //new_scan
    void LidarDriver::new_scan(const vector<double>& scan) {
        //Funzione che memorizza nel buffer una scansione
        
        if(logical_size == BUFFER_DIM) {
            //Il buffer è pieno --> imposto il nuovo scan in posizione oldest_index e la incremento
            buffer[oldest_index] = check_dim(scan, scanner_size);
            oldest_index = (oldest_index + 1) % BUFFER_DIM;
        } else {
            //Posiziono lo scan nella prima posizione libera e incremento la logical size
            buffer[(oldest_index+logical_size)%BUFFER_DIM] = check_dim(scan, scanner_size);       //N.B: (oldest_index+logical_size)%BUFFER_DIM è la formula per calcolare l'indice più recente
            logical_size++;
        }
    }

    //get_scan
    vector<double> LidarDriver::get_scan(){
        //Funzione che restituisce il buffer più vecchio
        
        if(logical_size > 0) {
            //Salvo oldest_index in variabile d'appoggio
            int index = oldest_index;
            
            //Incremento oldest_index
            oldest_index = (oldest_index + 1) % BUFFER_DIM;
            
            //Diminuisco dimensione logica buffer
            logical_size--;
            
            return buffer[index];

        } else throw out_of_range("Buffer is empty");

    }

    //clear_buffer
    void LidarDriver::clear_buffer() {
        
        get_buffer().clear();

        logical_size = 0;
        oldest_index = 0;
    }


    //get_distance
    double LidarDriver::get_distance(double angle) const {
        //Funzione che ritorna la lettura dato un certo angolo

        if(angle < 0 || angle > 180)
        {
            throw invalid_argument("Angle must be between 0 and 180");
        }

        //Prendo la scansione più recente
        int newest_index = (oldest_index + logical_size -1) % BUFFER_DIM;

        //Cerco nella scansione più recente l'angolo più vicino
        int angle_index = round(angle/angular_res);

        return get_buffer()[newest_index][angle_index];
    }

    //OVERLOADING COPY ASSIGNMENT
    LidarDriver& LidarDriver::operator=(const LidarDriver& obj)
    {
        if (this != &obj) { // Evita l'auto-assegnazione
            angular_res = obj.angular_res;
            scanner_size = obj.scanner_size;
            buffer = obj.buffer; // std::vector gestisce automaticamente la copia profonda
            oldest_index = obj.oldest_index;
            logical_size = obj.logical_size;
        }
        return *this;
    }

    //OVERLOADING MOVE ASSIGNMENT
    LidarDriver& LidarDriver::operator=(LidarDriver&& obj)
    {
        if (this != &obj) { // Evita l'auto-assegnazione
            angular_res = obj.angular_res;
            scanner_size = obj.scanner_size;
            buffer = std::move(obj.buffer); //Attraverso il move vengono già spostati gli oggetti da obj.buffer to this, quindi rubati ad obj
            oldest_index = obj.oldest_index;
            logical_size = obj.logical_size;
            
            obj.angular_res = 0;
            obj.scanner_size = 0;
            obj.oldest_index = 0;
            obj.logical_size = 0;
        }
        return *this;
    }


/*HELPER FUNCTION*/
    //check_dim
    vector<double> check_dim(const vector<double>& v, int sc_size) {
        //Funzione che controlla se la dimensione dell'array passato come parametro è uguale alla taglia dello scanner
        
        vector<double> auxiliary_vector = v;
        
        //MINORE: riempio gli spazi mancanti a zero
        if(v.size() < sc_size) {
            auxiliary_vector.resize(sc_size, 0);
        } 
        //MAGGIORE: taglio l'array
        else if(v.size() > sc_size) {
            auxiliary_vector.resize(sc_size);
        }
        
        return auxiliary_vector;
    }

    //Overloading operatore <<
    ostream& operator<<(std::ostream& os, const LidarDriver& obj) {
        
        if(obj.get_logical_size() == 0) {
            os << "Buffer is empty";
        } else {
            //Stampo l'ultima scansione salvata
            int newest_index = (obj.get_oldest_index()+obj.get_logical_size()-1)%obj.BUFFER_DIM;
            
            os << "Latest scan: ";
            for(int i = 0; i<obj.get_scanner_size(); i++) {
                os << obj.get_buffer()[newest_index][i] << " ";
            }
            os << "\n";
        }

        return os;
    }