#pragma once
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>
#include <string>
#include <functional>
#include "nlohmann/json.hpp"
#include "utils/GlobalData.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using std::string;

class AsyncDriver {
private:
	client m_endpoint;
	std::weak_ptr<websocketpp::connection<websocketpp::config::asio_client>> m_hdl;
	std::mutex m_mutex;
	std::thread m_thread;
	std::function<void(bool success)> m_on_connect_complete;

	std::vector<std::function<void(string, nlohmann::json)>> callbacks;
public:
	string msg;
public:
	AsyncDriver() {
		// Initialize ASIO
		m_endpoint.init_asio();
		m_endpoint.set_access_channels(websocketpp::log::alevel::none);
		m_endpoint.clear_access_channels(websocketpp::log::alevel::none);
		// Register handlers
		m_endpoint.set_open_handler(bind(&AsyncDriver::on_open, this, ::_1));
		m_endpoint.set_close_handler(bind(&AsyncDriver::on_close, this, ::_1));
		m_endpoint.set_fail_handler(bind(&AsyncDriver::on_fail, this, ::_1));
		m_endpoint.set_message_handler(bind(&AsyncDriver::on_message, this, ::_1, ::_2));
	}

	~AsyncDriver() {
		// Stop the ASIO io_service run loop
		//m_endpoint.stop_perpetual(); //¿‡À∆‘›Õ£
		m_endpoint.stop(); //”¿æ√Õ£÷π
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}

	void registerCallback(std::function<void(string, nlohmann::json)> cb) {
		callbacks.push_back(cb);
	}

	//private
	void on_open(websocketpp::connection_hdl hdl) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_hdl = std::weak_ptr<websocketpp::connection<websocketpp::config::asio_client>>(
			m_endpoint.get_con_from_hdl(hdl)
		);
		// Notify the caller that the connection was successful
		if (m_on_connect_complete) {
			m_on_connect_complete(true);
			m_on_connect_complete = nullptr; // Reset the callback after use
		}
	}

	void on_close(websocketpp::connection_hdl hdl) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_hdl.reset(); // Reset the connection handle
	}

	void on_fail(websocketpp::connection_hdl hdl) {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_hdl.reset(); // Reset the connection handle

		// Notify the caller that the connection failed (if a callback was set)
		if (m_on_connect_complete) {
			m_on_connect_complete(false);
			m_on_connect_complete = nullptr; // Reset the callback after use
		}
	}

	void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg) {
		std::lock_guard<std::mutex> lock(m_mutex);
		nlohmann::json obj = nlohmann::json::parse(msg->get_payload());
		//std::cout << obj << std::endl;
		if (obj.contains("method")) { // Events
			for (const auto& callback : callbacks) {
				string method = obj["method"];
				callback(method, obj["params"]);
			}
		}
		else if (obj.contains("result") && obj.at("result").is_object()) {
			GlobalData::getResult()[obj["id"]] = obj["result"];
		}
		else {
			// nothing
		}
	}

	// public
	void connect(const std::string& uri, std::function<void(bool success)> on_connect_complete) {
		websocketpp::lib::error_code ec;
		client::connection_ptr con = m_endpoint.get_connection(uri, ec);

		if (ec) {
			std::cout << "Could not create connection because: " << ec.message() << std::endl;
			on_connect_complete(false);
			return;
		}

		// Store the on_connect_complete callback for later use
		m_on_connect_complete = on_connect_complete;

		m_endpoint.connect(con);

		//m_endpoint.run();
		// Start the ASIO io_service run loop in a separate thread
		if (!m_thread.joinable()) {
			m_thread = std::thread(&client::run, &m_endpoint);
		}
	}

	void send_message(const std::string& message) {
		// Ensure we have a valid connection handle
		if (!m_hdl.lock()) {
			std::cout << "No valid connection handle" << std::endl;
			return;
		}

		//m_on_message_complete = on_message_complete;

		websocketpp::lib::error_code ec;
		m_endpoint.send(m_hdl.lock(), message, websocketpp::frame::opcode::text, ec);

		if (ec) {
			std::cout << "Send failed because: " << ec.message() << std::endl;
		}
	}

	void stop() {
		//m_endpoint.stop_perpetual();
		m_endpoint.stop();
	}
};

