#ifndef SIO_CLIENT_BASE_H
#define SIO_CLIENT_BASE_H

#include <asio/io_service.hpp>

namespace sio
{
    class socket;

    class client_base {
    protected:
        client_base() = default;
        virtual ~client_base() = default;

        virtual bool opened() const = 0;

        virtual void send(packet& p) = 0;

        virtual void remove_socket(std::string const& nsp) = 0;

        virtual asio::io_service& get_io_service() = 0;

        virtual void on_socket_closed(std::string const& nsp) = 0;

        virtual void on_socket_opened(std::string const& nsp) = 0;

        friend class sio::socket;
    };
}
#endif // SIO_CLIENT_BASE_H
