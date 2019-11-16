#include <iostream>
#include <string>

#include "uv.h"
#include "uv_ssl/client.h"
#include "uv_ssl/http.h"


auto request =
    "GET / HTTP/1.1\r\n"
    "User-Agent: curl/7.51.0\r\n"
    "Host: example.org\r\n\r\n";
void fetch(uv_loop_t* loop) {
    uv_ssl::http_client client("example.org");
    client.on_read([loop](uv_ssl::http_response r) {
        std::cout << std::string(r.buf, r.len) << std::endl;
        uv_stop(loop);
    });
    client.connect(loop);
    client.write(request);
}
int main() {
    auto loop = uv_loop_new();
    
    fetch(loop);
    
    uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}
