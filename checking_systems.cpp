#include <iostream>
#include <exception>

#include <krpc/client.hpp>
#include <krpc/services/space_center.hpp>

 int main() {    

    setlocale(LC_ALL,"Ukr");
    std::cout << "[SYSTEM] Trying connect to server kRPC..." << std::endl;

    try { 
        // Creating client (name, IP, RPC_port, Stream_port)
        krpc::Client client("Autopilot Test", "127.0.0.1", 50000, 50001);
        /*std::cout << "[SYSTEM] Connect has been succefully!" << std::endl;*/

        // Getting access to game's objs via SpaceCenter's
        krpc::services::SpaceCenter space_center(&client);

        // Беремо корабель, яким ти зараз керуєш

       /* auto vessel = space_center.active_vessel();

        // Виводимо базову телеметрію
        std::cout << "-----------------------------------" <<std:: endl;
        std::cout << "🚀 Active vessel: " << vessel.name() <<std:: endl;
        
        // Отримуємо точку відліку для поверхні планети, на якій ми знаходимось
        auto ref_frame = vessel.orbit().body().reference_frame();
        auto flight_info = vessel.flight(ref_frame);

        
       
        while (flight_info.mean_altitude() < 100000) { 
           std::cout << "🌍 Altitude in sea level: " << flight_info.mean_altitude() << " meters " << std::endl;
        }   
        */
         
    } catch (const std::exception& e) {
       std:: cerr << "[ERROR] Error to connect: " << e.what() << std::endl;
        std::cerr << "[TIP] Check, launch KSP or you in launding place?/in flight, and or server kRPC is shone green." << std::endl;
    }

    return 0;
}

/*
#include <string>
#include <vector>

int main() {
    setlocale(LC_ALL,"");

    try
    {
        krpc::Client client("AutoPilot_Test1","127.0.0.1",50000,50001);
        std::cout<<"connect has been succefully"<<std::endl;
        krpc::services::SpaceCenter space_center(&client);
        auto vessel = space_center.active_vessel();

        

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    auto key = 10.9123;
    float key2 = 10;



}*/