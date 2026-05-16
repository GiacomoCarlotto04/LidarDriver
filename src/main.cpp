#include "LidarDriver.h"

int main() {

    //Dichiarazione di due Lidar con risoluzione angolare differente
    LidarDriver Lidar1(1);
    LidarDriver Lidar2(0.5);

    //Dichiarazione di due Vector di grandezza differente
    std::vector<double> Vector1 = {0,1,2,3,4,5,6,7,8,9,10,11,12};
    std::vector<double> Vector2;
    for (int i = 0; i < 200; i++) {
        Vector2.push_back(i);
    }

    //Verifico le dimensioni dei due Vector
    std::cout << "====================== VECTOR ====================== \n" << std::endl;
    std::cout << "Dimensione Vector1: " << Vector1.size() << std::endl;
    std::cout << "Dimensione Vector2: " << Vector2.size() << "\n" << std::endl;

    //new_scan
    std::cout << "Aggiungo i due Vector, in ordine, nei due rispetti Lidar \n" << std::endl;
    Lidar1.new_scan(Vector1);
    Lidar1.new_scan(Vector2);
    Lidar2.new_scan(Vector1);
    Lidar2.new_scan(Vector2);
    
    //Verifico le varie funzioni nel 1° Lidar
    std::cout << "====================== LIDAR 1 - RISOL. ANGOL. = 1.0 ====================== \n" << std::endl;
    
        //Dimensione Corretta
        std::cout << "Dimensione Lidar1[0]: " << Lidar1.get_buffer()[0].size() << std::endl;
        std::cout << "Dimensione Lidar1[1]: " << Lidar1.get_buffer()[1].size() << "\n" <<std::endl;
        
        //Operator <<
        std::cout << "Operator <<: " << Lidar1 << "\n";
        
        //get_scan
        std::cout << "Primo utilizzo di get_scan(): ";
            std::vector<double> primaScansione = Lidar1.get_scan();
            for(int i = 0; i<primaScansione.size(); i++) {
                std::cout << primaScansione[i] << " ";
            }
            std::cout << "\n" <<std::endl;
        std::cout << "Secondo utilizzo di get_scan(): ";
            std::vector<double> secondaScansione = Lidar1.get_scan();
            for(int i = 0; i<secondaScansione.size(); i++) {
                std::cout << secondaScansione[i] << " ";
            }
            std::cout << "\n" <<std::endl;
        
        //Operator << con buffer vuoto
        std::cout << "Operator <<: " << Lidar1 << "\n" << std::endl;
        
        //get_distance
        std::cout << "Effettuo un new_scan(Vector2)." << std::endl;
        Lidar1.new_scan(Vector2);
        std::cout << "Lettura ad angolo 60: " << Lidar1.get_distance(60) << "\n" << std::endl;
        

    //Verifico le varie funzioni nel 2° Lidar
    std::cout << "====================== LIDAR 2 - RISOL. ANGOL. = 0.5 ====================== \n" << std::endl;
        
        //Dimensione Corretta
        std::cout << "Dimensione Lidar2[0]: " << Lidar2.get_buffer()[0].size() << std::endl;
        std::cout << "Dimensione Lidar2[1]: " << Lidar2.get_buffer()[1].size() << "\n" << std::endl;
        
        //Operator <<
        std::cout << "Operator <<: " << Lidar2 << std::endl;
        
        //get_distance (mi aspetto sia il doppio del 1° Lidar)
        std::cout << "Lettura ad angolo 60: " << Lidar2.get_distance(60) << "\n" << std::endl;

        //clear_buffer
        std::cout << "Effettuo un clear_buffer." << std::endl;
        Lidar2.clear_buffer();
        std::cout << "Dimensione Lidar2: " << Lidar2.get_buffer().size() << std::endl;
        std::cout << Lidar2 << "\n" <<std::endl;
    
        //circolarità del buffer
        std::cout << "Aggiungo 11 vettori a Lidar2. Mi aspetto che Lidar2[1] (che contiene Vector2) abbia il nuovo oldest_index." << std::endl;
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector2);       //UNICO DIVERSO -> verifico con get_scan() se effettivamente la circolarità funziona
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
            Lidar2.new_scan(Vector1);
    std::cout << "Utilizzo di get_scan(): ";
        std::vector<double> CheckCircularity = Lidar2.get_scan();
        for(int i = 0; i<CheckCircularity.size(); i++) {
            std::cout << CheckCircularity[i] << " ";
        }
        std::cout << "\n" <<std::endl;

    //Costruttore di copy:
    LidarDriver Lidar3 = Lidar2;
    std::cout << "Stampa di Lidar 2: " << std::endl;
    std::cout << Lidar2 << std::endl;
    std::cout << "Stampa di Lidar2.get_angular_res(): " << Lidar2.get_angular_res() << std::endl;
    std::cout << "\n" <<std::endl;

    std::cout << "Stampa di Lidar 3: " << std::endl;
    std::cout << Lidar3 << std::endl;
    std::cout << "Stampa di Lidar3.get_angular_res(): " << Lidar3.get_angular_res() << std::endl;
    std::cout << "\n" <<std::endl;

    Lidar2.new_scan(Vector2);

    Lidar1 = Lidar2;
    std::cout << "Stampa di Lidar 1: " << std::endl;
    std::cout << Lidar1 << std::endl;
    std::cout << "Stampa di Lidar1.get_angular_res(): " << Lidar1.get_angular_res() << std::endl;
    std::cout << "\n" <<std::endl;



    //TUTTO FUNZIONA CORRETTAMENTE
    std::cout << "====================== TUTTO FUNZIONA CORRETTAMENTE. COMPLIMENTI! ====================== \n" << std::endl;
}