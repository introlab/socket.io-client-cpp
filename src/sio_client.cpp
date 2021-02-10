//
//  sio_client.h
//
//  Created by Melo Yao on 3/25/15.
//

#include "sio_client.h"
#include "internal/sio_client_impl.h"
#include "internal/sio_client_tls_impl.h"

using namespace websocketpp;
using std::stringstream;

namespace sio
{
    bool is_tls(const std::string& uri)
    {
        return uri.rfind("wss://", 0) == 0 || uri.rfind("https://", 0) == 0;
    }

    client::client():
        m_impl(new client_impl()), m_impl_tls(new client_tls_impl())
    {
    }

    client::~client()
    {
        delete m_impl;
        delete m_impl_tls;
    }

    void client::set_open_listener(con_listener const& l)
    {
        m_impl->set_open_listener(l);
        m_impl_tls->set_open_listener(l);
    }

    void client::set_fail_listener(con_listener const& l)
    {
        m_impl->set_fail_listener(l);
        m_impl_tls->set_fail_listener(l);
    }

    void client::set_close_listener(close_listener const& l)
    {
        m_impl->set_close_listener(l);
        m_impl_tls->set_close_listener(l);
    }

    void client::set_socket_open_listener(socket_listener const& l)
    {
        m_impl->set_socket_open_listener(l);
        m_impl_tls->set_socket_open_listener(l);
    }

    void client::set_reconnect_listener(reconnect_listener const& l)
    {
        m_impl->set_reconnect_listener(l);
        m_impl_tls->set_reconnect_listener(l);
    }

    void client::set_reconnecting_listener(con_listener const& l)
    {
        m_impl->set_reconnecting_listener(l);
        m_impl_tls->set_reconnecting_listener(l);
    }

    void client::set_socket_close_listener(socket_listener const& l)
    {
        m_impl->set_socket_close_listener(l);
        m_impl_tls->set_socket_close_listener(l);
    }

    void client::clear_con_listeners()
    {
        m_impl->clear_con_listeners();
        m_impl_tls->clear_con_listeners();
    }

    void client::clear_socket_listeners()
    {
        m_impl->clear_socket_listeners();
        m_impl_tls->clear_socket_listeners();
    }

    void client::connect(const std::string& uri)
    {
        m_is_tls = is_tls(uri);
        if (m_is_tls)
        {
            m_impl_tls->connect(uri, {}, {});
        }
        else
        {
            m_impl->connect(uri, {}, {});
        }
    }

    void client::connect(const std::string& uri, const std::map<string,string>& query)
    {
        m_is_tls = is_tls(uri);
        if (m_is_tls)
        {
            m_impl_tls->connect(uri, query, {});
        }
        else
        {
            m_impl->connect(uri, query, {});
        }
    }

    void client::connect(const std::string& uri, const std::map<std::string,std::string>& query,
                         const std::map<std::string,std::string>& http_extra_headers)
    {
        m_is_tls = is_tls(uri);
        if (m_is_tls)
        {
            m_impl_tls->connect(uri, query, http_extra_headers);
        }
        else
        {
            m_impl->connect(uri, query, http_extra_headers);
        }
    }

    socket::ptr const& client::socket(const std::string& nsp)
    {
        if (m_is_tls)
        {
            return m_impl_tls->socket(nsp);
        }
        else
        {
            return m_impl->socket(nsp);
        }
    }

    // Closes the connection
    void client::close()
    {
        if (m_is_tls)
        {
            m_impl_tls->close();
        }
        else
        {
            m_impl->close();
        }
    }

    void client::sync_close()
    {
        if (m_is_tls)
        {
            m_impl_tls->sync_close();
        }
        else
        {
            m_impl->sync_close();
        }
    }

    bool client::opened() const
    {
        if (m_is_tls)
        {
            return m_impl_tls->opened();
        }
        else
        {
            return m_impl->opened();
        }
    }

    std::string const& client::get_sessionid() const
    {
        if (m_is_tls)
        {
            return m_impl_tls->get_sessionid();
        }
        else
        {
            return m_impl->get_sessionid();
        }
    }

    void client::set_reconnect_attempts(int attempts)
    {
        m_impl->set_reconnect_attempts(attempts);
        m_impl_tls->set_reconnect_attempts(attempts);
    }

    void client::set_reconnect_delay(unsigned millis)
    {
        m_impl->set_reconnect_delay(millis);
        m_impl_tls->set_reconnect_delay(millis);
    }

    void client::set_reconnect_delay_max(unsigned millis)
    {
        m_impl->set_reconnect_delay_max(millis);
        m_impl_tls->set_reconnect_delay_max(millis);
    }

}
