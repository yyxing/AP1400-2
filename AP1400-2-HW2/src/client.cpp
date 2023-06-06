#include "client.h"
#include <random>
#include <utility>
#include "crypto.h"


std::string Client::get_id() {
    return this->id;
}

Client::Client(std::string id, const Server &server):id(std::move(id)),server(&server) {
    crypto::generate_key(this->public_key, this->private_key);
}

double Client::get_wallet() const {
    return server->get_wallet(this->id);
}

std::string Client::get_publickey() const {
    return this->public_key;
}

std::string Client::sign(std::string txt) const {
    return crypto::signMessage(private_key, std::move(txt));
}

size_t Client::generate_nonce() {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution u(0, INT32_MAX);
    return u(e);
}

bool Client::transfer_money(std::string receiver, double value) const {
    std::string trx = this->id + "-" + receiver + "-" + std::to_string(value);
    std::string sign = this->sign(trx);
    return this->server->add_pending_trx(trx, sign);
}
