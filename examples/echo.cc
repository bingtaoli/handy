#include <handy/handy.h>
using namespace handy;

int main(int argc, const char* argv[]) {
    setloglevel(handy::Logger::LTRACE);
    EventBase base;
    Signal::signal(SIGINT, [&]{ base.exit(); });
    TcpServerPtr svr = TcpServer::startServer(&base, "", 99);
    exitif(svr == NULL, "start tcp server failed");
    svr->onConnRead([](const TcpConnPtr& con) {
        con->send(con->getInput());
    });
    base.loop();
}