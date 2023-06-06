#ifndef SERVER_H
#define SERVER_H
#include "client.h"
#include <vector>
#include <memory>
#include <map>
#include <iostream>

extern std::vector<std::string> pending_trxs;
class Client;

class Server
{
public:
    Server();
    std::shared_ptr<Client> add_client(std::string id);
    [[nodiscard]] std::shared_ptr<Client> get_client(std::string id) const;
    [[nodiscard]] double get_wallet(std::string id) const;
    [[nodiscard]] std::map<std::shared_ptr<Client>, double> get_clients() const;
    static bool parse_trx(const std::string& trx, std::string& sender, std::string& receiver, double& value);
    bool add_pending_trx(std::string trx, std::string signature) const;
    size_t mine();
private:
    std::map<std::shared_ptr<Client>, double> clients;
};

#endif //SERVER_H