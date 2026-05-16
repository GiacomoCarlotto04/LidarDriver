#ifndef LIDAR_DRIVER_h
#define LIDAR_DRIVER_h

#include <iostream>
#include <vector>

class LidarDriver {
    public:
        //Costanti
        static const int BUFFER_DIM;
        
        //Costruttori
        LidarDriver();
        LidarDriver(double res);
        LidarDriver(const LidarDriver& obj);                                    //copy constructor
        LidarDriver(LidarDriver&& obj);                                         //move constructor

        //Getter
        double get_angular_res() const;
        int get_scanner_size() const;
        std::vector<std::vector<double>> get_buffer() const;
        int get_oldest_index() const;
        int get_logical_size() const;

        //Member Function
        void new_scan(const std::vector<double>& scan);                         //memorizzazione nuova scansione
        std::vector<double> get_scan();                                         //resituzione scansione più vecchia
        void clear_buffer();                                                    //eliminazione scansioni salvate
        double get_distance(double angle) const;                                //restituzione distanza dato un angolo nella scansione più recente
        
        //Overloading tramite member function
        LidarDriver& operator=(const LidarDriver& obj);
        LidarDriver& operator=(LidarDriver&& obj);
    
    private:
        //Variabili
        double angular_res;                                                     //risoluzione angolare
        int scanner_size;                                                       //n° di letture per scansione
        std::vector<std::vector<double>> buffer;                                //buffer delle scansioni
        int oldest_index;                                                       //indice scansione più vecchia
        int logical_size;                                                       //scansioni memorizzate

};

//Helper Function
std::ostream& operator<<(std::ostream& os, const LidarDriver& obj);             //overloading dell'operatore di stampa
std::vector<double> check_dim(const std::vector<double>& v, int sc_size);       //controllo dimensione di argomento

#endif