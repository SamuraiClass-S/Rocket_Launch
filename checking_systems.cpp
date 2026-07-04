#include <iostream>
#include <exception>

#include <krpc/client.hpp>
#include <krpc/services/space_center.hpp>
using namespace std;
int main() {

    cout << "[SYSTEM] Tryong connect to server kRPC..." << endl;

    try {
        // Створюємо клієнт (назва_клієнта, IP, RPC_порт, Stream_порт)
        krpc::Client client("Autopilot Test", "127.0.0.1", 50000, 50001);
        cout << "[SYSTEM] Connect has been succefully!" << endl;

        // Отримуємо доступ до об'єктів гри через сервіс SpaceCenter
        krpc::services::SpaceCenter space_center(&client);

        // Беремо корабель, яким ти зараз керуєш
        auto vessel = space_center.active_vessel();

        // Виводимо базову телеметрію
        cout << "-----------------------------------" << endl;
        cout << "🚀 Active vessel: " << vessel.name() << endl;
        
        // Отримуємо точку відліку для поверхні планети, на якій ми знаходимось
        auto ref_frame = vessel.orbit().body().reference_frame();
        auto flight_info = vessel.flight(ref_frame);

        
       
        while (flight_info.mean_altitude() < 100000) { 
           cout << "🌍 Altitude in sea level: " << flight_info.mean_altitude() << "meters " << endl;
        }
        
       
        
        
         
    } catch (const exception& e) {
        cerr << "[ERROR] Error to connect: " << e.what() << std::endl;
        cerr << "[TIP] Check, launch KSP or you in launding place?/in flight, and or server kRPC is shone green." << std::endl;
    }

    return 0;
}