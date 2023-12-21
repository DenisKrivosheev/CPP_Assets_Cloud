#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include </httplib.h>
#include <nlohmann/json.hpp>


using namespace std;
using namespace httplib;
using json = nlohmann::json;

int main() {
    Server server;
    
    server.Get("/img/(.*)", [&](const Request& req, Response& res) {
        string filename = req.matches[1];
        string filepath = filename; 

        ifstream ifs(filepath, ios::binary);
        if (!ifs) {
            res.status = 404;
            res.set_content("Image not found", "text/plain");
            return;
        }

        stringstream buffer;
        buffer << ifs.rdbuf();
        string content = buffer.str();
        std::cout << "called file: " + filename << endl;
        res.set_content(content, "image/jpeg"); 
        });

    server.Get("/img/assets/(.*)", [&](const Request& req, Response& res) {
        string filename = req.matches[1];
        string filepath = filename; 

        ifstream ifs(filepath, ios::binary);
        if (!ifs) {
            res.status = 404;
            res.set_content("Image not found", "text/plain");
            return;
        }

        stringstream buffer;
        buffer << ifs.rdbuf();
        string content = buffer.str();
        std::cout << "called file: " + filename << endl;
        res.set_content(content, "image/jpeg"); 
        });

    server.Post("/save_file", [&](const Request& req, Response& res) {
        ///cout << "Recived Post Data:" << req.body << endl;
        json data = json::parse(req.body);
        std::string filename = data["img"]["originalname"];
        std::string mimetype = data["img"]["mimetype"];
        


        std::cout << filename << endl;
        
        try{
            if (data["img"].find("buffer") != data["img"].end()) {
                const json& buffer_data = data["img"]["buffer"]["data"];

                if (buffer_data.is_array()) {
                    // Convert the array of integers to a string
                    std::string buffer_str;
                    for (const auto& elem : buffer_data) {
                        if (elem.is_number()) {
                            buffer_str += static_cast<char>(elem.get<int>());
                        }
                        else {
                            
                            std::cout << "Non-numeric element in buffer array." << endl;
                        }
                    }

                    
                    std::cout << "Buffer size : " << buffer_str.size() << endl;

                    std::ofstream outfile(filename, std::ios::binary);
                    if (outfile.is_open()) {
                        outfile.write(buffer_str.c_str(), buffer_str.size());
                        outfile.close();
                        std::cout << "File saved:" << filename << endl;
                        json response = {
                            {"status","200"},
                            {"url", "http://localhost:8080/img/" + filename}
                        };
                        res.set_content(response.dump(), "application/json");
                    }
                    else {
                        std::cout << "err to write a file" << endl;
                    }

                }
                else {
                    std::cout << "Invalid buffer data format." << endl;
                }
            }
            else {
                std::cout << "Buffer property not found." << endl;
                res.set_content(req.body, "application/json");
            }

        

        }
        catch (const json::exception& e) {
            std::cout << "Exception caught: " << e.what() << endl;
        }
        });
      

    /*
    
      server.Post("/save_file", [&](const Request& req, Response& res) {
        try {
            ///cout << "Recived Post Data:" << req.body << endl;
            json data = json::parse(req.body);
            std::string filename = data["img"]["originalname"];
            std::string mimetype = data["img"]["mimetype"];
            cout << filename << endl;
            cout << mimetype<< endl;

            // Attempt to access the buffer property
          

       // std:string decoded_buffer = base64_decode(buffer_str);


            res.set_content(req.body, "application/json");
        }
        catch (const json::parse_error&  e) {
            json err = {
                {"message", e.what()}
            };
            cout << err << endl;
            res.set_content(err.dump(), "application/json");
            
        }

        });


    */

    cout << "Server is running on port 8080" << endl;
    server.listen("localhost", 8080);

    return 0;
}
