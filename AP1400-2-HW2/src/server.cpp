#include "server.h"
#include "client.h"
#include <sstream>
#include <stdexcept>
#include <random>

std::vector<std::string> pending_trxs;

Server::Server() = default;

std::shared_ptr<Client> Server::add_client(std::string id) {
    for (auto &c: this->clients) {
        if (c.first->get_id() == id) {
            std::random_device rd;
            std::default_random_engine e(rd());
            std::uniform_int_distribution u;
            for (int i = 0; i < 4; ++i) {
                id += std::to_string(u(e));
            }
        }
    }
    auto client = std::make_shared<Client>(id, *this);
    this->clients.insert(std::pair(client, 5.0));
    return client;
}

std::shared_ptr<Client> Server::get_client(std::string id) const {
    for (auto &c: this->clients) {
        if (c.first->get_id() == id) {
            return c.first;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id) const {
    for (auto &c: this->clients) {
        if (c.first->get_id() == id) {
            return c.second;
        }
    }
    return 0.0;
}

std::map<std::shared_ptr<Client>, double> Server::get_clients() const {
    return this->clients;
}

bool Server::add_pending_trx(std::string trx, std::string signature) const {
    std::string sender{}, receiver{};
    double value;
    parse_trx(trx, sender, receiver, value);
    auto p_sender = get_client(sender);
    auto p_receiver = get_client(receiver);
    if (!p_sender || !p_receiver) {
        return false;
    }
    if (crypto::verifySignature(p_sender->get_publickey(), trx, signature) &&
        p_sender->get_wallet() >= value) {
        pending_trxs.push_back(trx);
        return true;
    }
    return false;
}

bool Server::parse_trx(const std::string &trx, std::string &sender, std::string &receiver, double &value) {
    std::istringstream is(trx);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(is, token, '-')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 3) {
        throw std::runtime_error("trx doesn't match format");
    }
    sender = tokens[0];
    receiver = tokens[1];
    value = std::stod(tokens[2]);
    return true;
}

size_t Server::mine() {
    std::string mempool{};
    for (const auto &trx: pending_trxs)
        mempool += trx;
    while (true) {
        for (auto &item: this->clients) {
            size_t nonce = item.first->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(nonce));
            if (hash.substr(0, 10).find("000") != std::string::npos) {
                item.second += 6.25;
                for (const auto &trx: pending_trxs) {
                    std::string sender{}, receiver{};
                    double value;
                    parse_trx(trx, sender, receiver, value);
                    this->clients[get_client(sender)] -= value;
                    this->clients[get_client(receiver)] += value;
                }
                pending_trxs.clear();
                return nonce;
            }
        }
    }
}


