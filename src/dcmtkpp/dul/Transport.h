/*************************************************************************
 * dcmtkpp - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1619bae8_acba_4bf8_8205_aa8dd0085c66
#define _1619bae8_acba_4bf8_8205_aa8dd0085c66

#include <memory>
#include <string>

#include <boost/asio.hpp>

namespace dcmtkpp
{

namespace dul
{

/// @brief TCP transport for the DICOM Upper Layer.
struct Transport
{
    /// @brief Socket type.
    typedef boost::asio::ip::tcp::socket Socket;

    /// @brief Constructor.
    Transport();

    /// @brief Destructor.
    ~Transport();

    /// @brief Return the io_service.
    boost::asio::io_service const & get_service() const;

    /// @brief Return the io_service.
    boost::asio::io_service & get_service();

    /// @brief Return the socket.
    std::shared_ptr<Socket const> get_socket() const;

    /// @brief Return the socket.
    std::shared_ptr<Socket> get_socket();

    /// @brief Test whether the transport is open.
    bool is_open() const;

    /**
     * @brief Connect to the specified endpoint, raise an exception upon error.
     */
    void connect(Socket::endpoint_type const & peer_endpoint);

    /**
     * @brief Receive a connection on the specified endpoint, raise an
     * exception upon error.
     */
    void receive(Socket::endpoint_type const & endpoint);

    /// @brief Close the connection.
    void close();

    /// @brief Read data, raise an exception on error.
    std::string read(std::size_t length);

    /// @brief Write data, raise an exception on error.
    void write(std::string const & data);

private:
    boost::asio::io_service _service;
    std::shared_ptr<Socket> _socket;
};

}

}

#endif // _1619bae8_acba_4bf8_8205_aa8dd0085c66
