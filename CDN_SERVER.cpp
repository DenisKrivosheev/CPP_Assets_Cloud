#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include </httplib.h>

using namespace std;
using namespace httplib;

int main() {
    Server server;

    server.Get("/imgs/(.*)", [&](const Request& req, Response& res) {
        string filename = req.matches[1];
        string filepath = filename; // No need for "imgs/" prefix

        ifstream ifs(filepath, ios::binary);
        if (!ifs) {
            res.status = 404;
            res.set_content("Image not found", "text/plain");
            return;
        }

        stringstream buffer;
        buffer << ifs.rdbuf();
        string content = buffer.str();

        res.set_content(content, "image/jpeg"); // Change content type as needed
        });

    cout << "Server is running on port 8080" << endl;
    server.listen("localhost", 8080);

    return 0;
}
