#include "RegisterClient.hpp"

#include "utils/LoggerFactory.hpp"
#include "utils/Logger.hpp"

#include "protocol/SIPMessage.hpp"

using namespace sip0x;
using namespace sip0x::utils;
using namespace sip0x::protocol;

RegisterClient::RegisterClient(UAC* uac, std::string remote_server, int remote_port) :
  listeners::UAListener(),
  _uac(uac), _registrar_server(remote_server), _registrar_port(remote_port)
{
  _logger = LoggerFactory::get_logger("sip0x.RegisterClient");
}

RegisterClient::~RegisterClient(void) {
  // TODO: Pointer will match when this element will be destroied?
  _uac->remove_listener(std::dynamic_pointer_cast<listeners::UAListener>(shared_from_this()));
}

void RegisterClient::start(void) {
  _uac->add_listener(std::dynamic_pointer_cast<listeners::UAListener>(shared_from_this()));
}


//! Set the desired amount of seconds of REGISTER expires. 
void RegisterClient::set_desired_expires(uint32_t e) {
  _desired_expires_secs = e;
}

//! Starts the registration process and keep refresh.
void RegisterClient::on_process(void) {
  std::lock_guard<std::recursive_mutex> guard(_mtx);

  RegisterStatus prevState = _status;
  if (_status == REG_STATUS_NOT_REGISTERED) {
    // RegClient is not registered, so try to register.
    auto request = _uac->create_REGISTER();
    request->uri.hostport.host = _registrar_server;
    request->uri.hostport.port = _registrar_port;
    _uac->handle(request);

    _status = REG_STATUS_REGISTERING;
  }
  else if (_status == REG_STATUS_REGISTERING) {
  }
  else if (_status == REG_STATUS_REGISTERED) {
    // refresh registration if it's time
    auto elapsed_secs = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _last_success_regsitration);

    long long timeout = (long long)std::roundl((float)_remote_expires_secs * 0.85f);
    if (elapsed_secs.count() >= timeout) {
      LOG_INFO(_logger, "Registration near to expiration, expires %lld seconds, elapsed %lld seconds. Initiating registration refresh.", timeout, elapsed_secs.count());

      // TODO: Update registration, don't create a new one.
      auto request = _uac->create_REGISTER();
      request->uri.hostport.host = _registrar_server;
      request->uri.hostport.port = _registrar_port;

      _uac->handle(request);
      _status = REG_STATUS_REGISTERING;
    }
  }
  else if (_status == REG_STATUS_REGISTER_FAILED) {
  }

  if (_last_unporcessed_response != nullptr) {
    // _last_unporcessed_response.reset(response->clone());
    // Get expires timeout 
    if (_last_unporcessed_response->is_success()) {
      // The expires could be placed in different places.
      int expires = -1;
      // - Get from contact
      std::shared_ptr<SIPMessageHeaderContact> contact = _last_unporcessed_response->get_first<SIPMessageHeaderContact>();
      if (contact != nullptr) {
        for (auto p : contact->params) {
          if (p.first.compare("expires") == 0) {
            // TODO: Add sanity check or implement sanity check in parsing phase.
            expires = std::atoi(p.second.c_str());
            LOG_DEBUG(_logger, "Extracted expires timeout of %d seconds from contact header line.", expires);
            //break;
          }
        }
      }
      // - Get from header line expires
      if (expires == -1) {
        std::shared_ptr<SIPMessageHeaderExpires> expires_line = _last_unporcessed_response->get_first<SIPMessageHeaderExpires>();
        if (expires_line != nullptr) {
          unsigned long ex = expires_line->expires;
          if (ex >= INT_MAX) {
            LOG_WARN(_logger, "Received a expires timeout of %lu seconds, excised max value from RFC 3261, truncating value to %d seconds.", ex, INT_MAX - 1);
            ex = INT_MAX - 1;
          }
          expires = ex;
          LOG_DEBUG(_logger, "Extracted expires timeout of %d seconds from Expires header line.", expires);
        }
      }

      if (expires > 0) {
        _last_success_regsitration = std::chrono::steady_clock::now();
        _remote_expires_secs = expires;
        _status = REG_STATUS_REGISTERED;
      }
      else {
        _status = REG_STATUS_NOT_REGISTERED;
        LOG_INFO(_logger, "Registration rejected, registrar responded with an invalid or 0 expires timeout.");
      }
    }
    else if (!_last_unporcessed_response->is_provisional()) {
      // TODO: logs
      // TODO: redirect and other steps should be handled in the correct way.
      _status = REG_STATUS_REGISTER_FAILED;
    }

    _last_unporcessed_response.reset();
  }

  if (prevState != _status) {
    LOG_DEBUG(_logger, "RegisterClient has changed status %s -> %s ", to_string(prevState), to_string(_status));
  }
}

std::string RegisterClient::describe_status(void) {
  return to_string(_status);
}


void RegisterClient::on_response(const std::shared_ptr<Transaction>& tran, const std::shared_ptr<SIPResponse const>& response) {
  // Save the last response for future handling in on_process.
  _mtx.lock();
  _last_unporcessed_response.reset((SIPResponse*)response->clone());
  _mtx.unlock();
}

char const* RegisterClient::to_string(RegisterStatus status) {
  if (status == RegisterStatus::REG_STATUS_NOT_REGISTERED)        return "REG_STATUS_NOT_REGISTERED";
  else if (status == RegisterStatus::REG_STATUS_REGISTERED)       return "REG_STATUS_REGISTERED";
  else if (status == RegisterStatus::REG_STATUS_REGISTERING)      return "REG_STATUS_REGISTERING";
  else if (status == RegisterStatus::REG_STATUS_REGISTER_FAILED)  return "REG_STATUS_REGISTER_FAILED";
        
  return "???";
}
