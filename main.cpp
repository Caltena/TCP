#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("hostname", "23"); // Port 23 für Telnet

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        std::string request = "Ihr Telnet-Befehl\r\n";
        boost::asio::write(socket, boost::asio::buffer(request));

        char reply[1024];
        size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply, request.size()));
        std::cout << "Antwort: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    } catch (std::exception& e) {
        std::cerr << "Fehler: " << e.what() << "\n";
    }

    return 0;
}
