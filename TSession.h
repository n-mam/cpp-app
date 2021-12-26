#ifndef TSESSION_HPP
#define TSESSION_HPP

#include <npl.hpp>

struct TSession
{
  wxString m_host;
  wxString m_port;
  wxString m_user;
  wxString m_pass;
  wxString m_prot;

  // FTPS
  npl::TLS m_ccTls;
  npl::TLS m_dcTls;

  // SSH

  virtual void StartSession() {};
  virtual void StopSession() {};
};

#endif