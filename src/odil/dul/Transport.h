/*************************************************************************
 * odil - Copyright (C) Universite de Strasbourg
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
#include <boost/date_time.hpp>

namespace odil
{

namespace dul
{

/**
 * @brief TCP transport for the DICOM Upper Layer.
 *
 * The behavior of connect, receive, read and write is governed by the timeout
 * value: if the timeout expires before the operation is completed, an exception
 * will be raised.
 */
struct Transport
{
    /// @brief Socket type.
    typedef boost::asio::ip::tcp::socket Socket;

    /// @brief Duration of the timeout.
    typedef boost::asio::deadline_timer::duration_type duration_type;

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

    /// @brief Return the timeout, default to infinity.
    duration_type get_timeout() const;

    /// @brief Set the timeout.
    void set_timeout(duration_type timeout);

    /// @brief Test whether the transport is open.
    bool is_open() const;

    /// @brief Connect to the specified endpoint, raise an exception upon error.
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
    duration_type _timeout;
    boost::asio::deadline_timer _deadline;

    std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;

    enum class Source
    {
        NONE,
        TIMER,
        OPERATION,
    };

    void _start_deadline(Source & source, boost::system::error_code & error);
    void _stop_deadline();

    void _run(Source & source, boost::system::error_code & error);
};

}

}

#endif // _1619bae8_acba_4bf8_8205_aa8dd0085c66
